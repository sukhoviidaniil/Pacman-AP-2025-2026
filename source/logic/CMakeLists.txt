file(GLOB_RECURSE LOGIC_SRC "*.cpp")

add_library(logic_lib STATIC ${LOGIC_SRC})

target_include_directories(logic_lib PUBLIC
        ${CMAKE_SOURCE_DIR}/source
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(logic_lib PUBLIC math_lib)