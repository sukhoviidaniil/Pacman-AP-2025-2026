# Building the graphics library
file(GLOB_RECURSE CONTROL_SRC "src/*.cpp")
add_library(control_lib STATIC ${CONTROL_SRC})
# Connecting headers
target_include_directories(control_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(control_lib PUBLIC
        infra_lib
        model_lib
)