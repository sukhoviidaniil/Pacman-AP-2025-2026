file(GLOB_RECURSE MATH_SRC "src/*.cpp")
add_library(math_lib STATIC ${MATH_SRC})
target_include_directories(math_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)