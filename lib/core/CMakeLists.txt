file(GLOB_RECURSE CORE_SRC "src/*.cpp")
add_library(core_lib STATIC ${CORE_SRC})
target_include_directories(core_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(core_lib PUBLIC
        sfml-window
        sfml-system
        infra_lib
        model_lib
        view_lib
        control_lib
)