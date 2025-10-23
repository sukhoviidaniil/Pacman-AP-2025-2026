cmake_minimum_required(VERSION 3.20)

# -----------------------------------------
# Standards and Compiler Settings
# -----------------------------------------

# We specify the c++ standard
set(CMAKE_CXX_STANDARD 23)
# If the compiler can't support it, it's an error
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# We force the compiler to disable all extensions and strictly follow the standard
set(CMAKE_CXX_EXTENSIONS OFF)
#[[
Add compiler warning options to enforce stricter code checks.
These flags are intended for GCC/Clang and help detect potential issues early.

-Wall
    Enables most of the common compiler warnings.
    This is a general-purpose flag to catch typical mistakes such as unused variables or unreachable code.

-Wextra
    Enables additional warnings not included in -Wall.
    For example, warns about unused function parameters, missing return statements in non-void functions, etc.

-Wpedantic
    Enforces strict compliance with the C++ standard.
    Warns about code that is technically legal for the compiler but non-standard or implementation-specific.

-Wshadow
    Warns when a local variable shadows another variable (e.g., a member variable or a global variable).
    Helps avoid subtle bugs due to variable name collisions.

-Wconversion
    Warns on implicit type conversions that may alter a value.
    For example, converting from float to int or narrowing conversions that may lose data.

-Wsign-conversion
    Warns on implicit conversions between signed and unsigned integers.
    Prevents subtle bugs caused by negative values being converted to large positive numbers.

-Werror
    Treat all warnings as errors
]]#
add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion)

# -----------------------------------------
# Create an executable file/target
# -----------------------------------------

# Specify the name of the project
project(Pacman LANGUAGES CXX)
# We specify the name of the executable file
set(APP_TARGET PacMan)

# -----------------------------------------
# Collect all the logical units of the project
# -----------------------------------------

# Folders with .h and .cpp files
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/source")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# Collecting Core resources
file(GLOB_RECURSE CORE_SOURCES "${SOURCE_DIR}/core/*.cpp")
set(CORE_INCLUDE_DIRS
        ${SOURCE_DIR}/core
        ${INCLUDE_DIR}/core
)

file(GLOB_RECURSE LOGIC_SOURCES "${SOURCE_DIR}/logic/*.cpp")
set(LOGIC_INCLUDE_DIRS
        ${SOURCE_DIR}/logic
        ${INCLUDE_DIR}/logic
)

file(GLOB_RECURSE CONST_SOURCES "${SOURCE_DIR}/const/*.cpp")
set(CONST_INCLUDE_DIRS
        ${SOURCE_DIR}/const
        ${INCLUDE_DIR}/const
)

# Collecting Function Resources
file(GLOB_RECURSE FUNC_SOURCES "${INCLUDE_DIR}/func/*.h")
set(FUNC_INCLUDE_DIRS
        ${INCLUDE_DIR}/func
)

# Collecting additional files that do not fall into general categories
set(RELEASE_SOURCE_FILES
        ${SOURCE_DIR}/main.cpp
)

# -----------------------------------------
# We connect all logical units of the project to the executable file/target
# -----------------------------------------

add_executable(${APP_TARGET}
        ${RELEASE_SOURCE_FILES}
        ${CORE_SOURCES}
        ${CONST_SOURCES}
        ${LOGIC_SOURCES}
        ${FUNC_SOURCES}
)

target_include_directories(${APP_TARGET} PUBLIC
        ${CORE_INCLUDE_DIRS}
        ${CONST_INCLUDE_DIRS}
        ${LOGIC_INCLUDE_DIRS}
        ${FUNC_INCLUDE_DIRS}
)

# -----------------------------------------
# Connecting the executable file/target to SFML
# -----------------------------------------

# Specify the path to the folder containing the ENTIRE SFML (which you downloaded from the website)
set(SFML_ROOT ${CMAKE_SOURCE_DIR}/external/SFML)
# Instruct to find all SFML components
find_package(SFML 3 COMPONENTS Graphics Window System)
# If it has found everything, then further actions will have meaning and power
if (SFML_FOUND)
    # Add SFML directories to the project
    target_include_directories(${APP_TARGET} PRIVATE ${SFML_INCLUDE_DIR})
    # Add SFML libraries to the project
    target_link_libraries(${APP_TARGET} SFML::Graphics SFML::Window SFML::System)
endif()


# -----------------------------------------
# Copying DLLs - Multiple Sources
# Must be placed after the declaration of the executive file/target
# -----------------------------------------

# Check: target must exist
if(NOT TARGET ${APP_TARGET})
    message(FATAL_ERROR "Target ${APP_TARGET} does not exist. Check add_executable(...) name.")
endif()

# All folders containing .dll files
set(DLL_SOURCE_DIRS
        "${CMAKE_SOURCE_DIR}/external/SFML/bin"
        "${CMAKE_SOURCE_DIR}/external/MinGW/bin"
)

# We collect all DLLs from all specified directories
set(ALL_DLL_FILES "")
foreach(DLL_DIR IN LISTS DLL_SOURCE_DIRS)
    # If the folder is found, then collect all .dll files into one collection
    if(EXISTS "${DLL_DIR}")
        file(GLOB DLL_FILES_IN_DIR "${DLL_DIR}/*.dll")
        list(APPEND ALL_DLL_FILES ${DLL_FILES_IN_DIR})
    else()
        message(WARNING "Directory not found: ${DLL_DIR}")
    endif()
endforeach()

# Determine whether the generator is multi-configuration (Visual Studio, Xcode, etc.)
get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(IS_MULTI_CONFIG)
    # --- Visual Studio, Xcode and other multi-configuration generators ---
    foreach(CONFIG_TYPE IN ITEMS Debug Release RelWithDebInfo MinSizeRel)
        add_custom_command(
                # Specify your executable file/target
                TARGET ${APP_TARGET}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E echo "Copying DLLs for ${CONFIG_TYPE}"
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${ALL_DLL_FILES}
                "$<TARGET_FILE_DIR:${APP_TARGET}>"
                COMMENT "Copying all .dll files (${CONFIG_TYPE})"
                CONFIGURATIONS ${CONFIG_TYPE}
        )
    endforeach()
else()
    # --- Ninja, Makefiles, and other single-config generators ---
    add_custom_command(
            # Specify your executable file/target
            TARGET ${APP_TARGET}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "Copying DLLs..."
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${ALL_DLL_FILES}
            "$<TARGET_FILE_DIR:${APP_TARGET}>"
            COMMENT "Copying all .dll files (single-config generator)"
    )
endif()
