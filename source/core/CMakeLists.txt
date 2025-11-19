file(GLOB CORE_SRC "*.cpp")

add_library(core_lib STATIC ${CORE_SRC})

target_include_directories(core_lib PUBLIC
        ${CMAKE_SOURCE_DIR}/source
        ${CMAKE_SOURCE_DIR}/include

)

target_link_libraries(core_lib PUBLIC math_lib logic_lib)