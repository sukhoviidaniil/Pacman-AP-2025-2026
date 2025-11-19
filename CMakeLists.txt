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
# Folders with .h and .cpp files
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/source")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# -----------------------------------------
# Collect all the logical units of the project
# -----------------------------------------

# Collecting additional files that do not fall into general categories
set(RELEASE_SOURCE_FILES
        ${SOURCE_DIR}/main.cpp
)

# Collecting Function Resources
file(GLOB_RECURSE FUNC_SOURCES "${INCLUDE_DIR}/func/*.h")
set(FUNC_INCLUDE_DIRS
        ${INCLUDE_DIR}/func
)

add_subdirectory(source/math)
add_subdirectory(source/logic)
add_subdirectory(source/core)
add_subdirectory(source/graphics)
add_subdirectory(tests)

# -----------------------------------------
# We connect all logical units of the project to the executable file/target
# -----------------------------------------

add_executable(${APP_TARGET}
        ${RELEASE_SOURCE_FILES}
        ${FUNC_SOURCES}
)
target_include_directories(${APP_TARGET} PUBLIC
        ${INCLUDE_DIR}/
)
target_link_libraries(${APP_TARGET}
        PRIVATE
        math_lib
        logic_lib
        core_lib
        graphics_lib
)


if(WIN32)
    # Создаём кастомную цель "run", которая запускает exe с нужным PATH
    add_custom_target(run_on_windows
            COMMAND ${CMAKE_COMMAND} -E env "PATH=${SFML_ROOT}/bin;$ENV{PATH}" $<TARGET_FILE:${APP_TARGET}>
            DEPENDS ${APP_TARGET}
            WORKING_DIRECTORY $<TARGET_FILE_DIR:${APP_TARGET}>
            COMMENT "Running ${APP_TARGET} with SFML DLLs in PATH"
    )
elseif(UNIX)
    # Linux: добавляем RPATH, чтобы ELF искал .so в SFML/lib
    set_target_properties(${APP_TARGET} PROPERTIES
            BUILD_RPATH "${SFML_ROOT}/lib"
            INSTALL_RPATH "${SFML_ROOT}/lib"
    )
endif()

target_compile_definitions(${APP_TARGET} PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")
