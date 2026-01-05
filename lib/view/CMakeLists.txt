# Building the graphics library
file(GLOB_RECURSE VIEW_SRC "src/*.cpp")
add_library(view_lib STATIC ${VIEW_SRC})
# Connecting headers
target_include_directories(view_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(view_lib PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
        infra_lib
        model_lib
)

