# Building the graphics library

file(GLOB_RECURSE GRAPHICS_SRC "*.cpp")
add_library(graphics_lib STATIC ${GRAPHICS_SRC})

# Connecting headers
target_include_directories(graphics_lib PUBLIC
        ${CMAKE_SOURCE_DIR}/source
        ${CMAKE_SOURCE_DIR}/include
)

# Specify the path to SFML
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/external/SFML-2.6.1")

if(WIN32)
    set(SFML_ROOT "${SFML_ROOT}/windows")
elseif(UNIX)
    set(SFML_ROOT "${SFML_ROOT}/linux")
endif()

set(CMAKE_PREFIX_PATH "${SFML_ROOT}/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

if (SFML_FOUND)
    message(STATUS "SFML found")

    get_cmake_property(_vars VARIABLES)

    message(STATUS "---- SFML variables created by find_package ----")

    foreach(v ${_vars})
        if(v MATCHES "^SFML_")
            message(STATUS "${v} = ${${v}}")
        endif()
    endforeach()

    message(STATUS "-----------------------------------------------")

    set(SFML_INCLUDE_DIR "${SFML_ROOT}/include/")

    message(STATUS "SFML_INCLUDE_DIR = ${SFML_INCLUDE_DIR}")

    target_include_directories(graphics_lib PUBLIC ${SFML_INCLUDE_DIR})
    target_link_libraries(graphics_lib PRIVATE sfml-graphics sfml-window sfml-system)
else()
    message(FATAL_ERROR "SFML not found: check SFML_ROOT and CMAKE_PREFIX_PATH")
endif()