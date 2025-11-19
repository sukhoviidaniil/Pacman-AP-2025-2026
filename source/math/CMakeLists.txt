file(GLOB MATH_SRC "*.cpp")

add_library(math_lib STATIC ${MATH_SRC})

target_include_directories(math_lib PUBLIC
        ${CMAKE_SOURCE_DIR}/source
        ${CMAKE_SOURCE_DIR}/include
)