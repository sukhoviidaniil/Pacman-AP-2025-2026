file(GLOB_RECURSE LOGIC_SRC "src/*.cpp")
add_library(logic_lib STATIC ${LOGIC_SRC})
target_include_directories(logic_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(logic_lib PUBLIC math_lib)