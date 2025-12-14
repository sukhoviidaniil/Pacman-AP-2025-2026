file(GLOB_RECURSE GEN_SRC "src/*.cpp")
add_library(gen_lib STATIC ${GEN_SRC})
target_include_directories(gen_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)