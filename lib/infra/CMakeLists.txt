file(GLOB_RECURSE INFRA_SRC "src/*.cpp")
add_library(infra_lib STATIC ${INFRA_SRC})
target_include_directories(infra_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${JSON_DIR}
)