
set(GTEST_ROOT "${CMAKE_SOURCE_DIR}/external/GTest")

if(WIN32)
    set(GTEST_INCLUDE_DIR "${GTEST_ROOT}/windows/include")
    set(GTEST_LIB_DIR "${GTEST_ROOT}/windows/lib")
elseif(UNIX)
    set(GTEST_INCLUDE_DIR "${GTEST_ROOT}/linux/include")
    set(GTEST_LIB_DIR "${GTEST_ROOT}/linux/lib")
endif()

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(run_tests ${TEST_SOURCES})

target_include_directories(run_tests
        PRIVATE
        ${GTEST_INCLUDE_DIR}
)

# Подключаем статические .lib/.a вручную
target_link_directories(run_tests PRIVATE ${GTEST_LIB_DIR})
target_link_libraries(run_tests
        PRIVATE
        gtest
        gtest_main
        math_lib
        logic_lib
        core_lib
)

add_test(NAME AllTests COMMAND run_tests)