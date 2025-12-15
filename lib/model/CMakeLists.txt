file(GLOB_RECURSE MODEL_SRC "src/*.cpp")
add_library(model_lib STATIC ${MODEL_SRC})
target_include_directories(model_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(model_lib PRIVATE infra_lib)