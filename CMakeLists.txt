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

add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion)

# -----------------------------------------
# Create an executable file/target
# -----------------------------------------

# Specify the name of the project
project(Pacman LANGUAGES CXX)
# We specify the name of the executable file
set(APP_TARGET PacMan)

# -----------------------------------------
# Specifying global variables
# -----------------------------------------

# Specify the path to SFML
set(SFML_RELATIVE_DIR "external/SFML-2.6.1")
if(WIN32)
    set(SFML_RELATIVE_DIR "${SFML_RELATIVE_DIR}/windows")
elseif(UNIX)
    set(SFML_RELATIVE_DIR "${SFML_RELATIVE_DIR}/linux")
endif()
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/${SFML_RELATIVE_DIR}")
set(CMAKE_PREFIX_PATH "${SFML_ROOT}/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

set(JSON_DIR "${CMAKE_SOURCE_DIR}/external/json")

# -----------------------------------------
# Collect all the logical units of the project
# -----------------------------------------

# Collecting additional files that do not fall into general categories
set(RELEASE_SOURCE_FILES
        main.cpp
)

# Collecting Function Resources
#[[
file(GLOB_RECURSE FUNC_SOURCES "${CMAKE_SOURCE_DIR}/func/*.h")
set(FUNC_INCLUDE_DIRS
        ${CMAKE_SOURCE_DIR}/func
)
#]]

add_subdirectory(lib/math)
add_subdirectory(lib/logic)
add_subdirectory(lib/graphics)
add_subdirectory(lib/core)
add_subdirectory(tests)

# -----------------------------------------
# We connect all logical units of the project to the executable file/target
# -----------------------------------------

add_executable(${APP_TARGET}
        ${RELEASE_SOURCE_FILES}
)

target_link_libraries(${APP_TARGET}
        PRIVATE
        math_lib
        logic_lib
        graphics_lib
        core_lib
)


if(WIN32)
    message("CMAKE_CURRENT_BINARY_DIR - ${CMAKE_CURRENT_BINARY_DIR}")
    get_property(SFML_ABSOLUTE_DIR TARGET graphics_lib PROPERTY INTERFACE_SFML_ABSOLUTE_DIR)
    get_property(SFML_RELATIVE_DIR TARGET graphics_lib PROPERTY INTERFACE_SFML_RELATIVE_DIR)
    message("SFML_ABSOLUTE_DIR - ${SFML_ABSOLUTE_DIR}")
    message("SFML_RELATIVE_DIR - ${SFML_RELATIVE_DIR}")
    set(BAT_FILE "${CMAKE_CURRENT_BINARY_DIR}/run_${APP_TARGET}.bat")
    add_custom_command(
            OUTPUT "${BAT_FILE}"
            COMMAND ${CMAKE_COMMAND} -E echo "@echo off" >  "${BAT_FILE}"
            COMMAND ${CMAKE_COMMAND} -E echo "set PATH=${SFML_ABSOLUTE_DIR}/bin;%PATH%" >> "${BAT_FILE}"
            COMMAND ${CMAKE_COMMAND} -E echo "\"%~dp0\\${APP_TARGET}.exe\"" >> "${BAT_FILE}"
            DEPENDS ${APP_TARGET}
    )
    add_custom_target(run_bat ALL DEPENDS "${BAT_FILE}")
elseif(UNIX)
    # Linux: add RPATH so that ELF searches for .so in SFML/lib
    set_target_properties(${APP_TARGET} PROPERTIES
            BUILD_RPATH "${SFML_ROOT}/lib"
            INSTALL_RPATH "${SFML_ROOT}/lib"
    )
endif()
target_compile_definitions(${APP_TARGET} PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")
