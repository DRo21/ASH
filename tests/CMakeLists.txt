set(TEST_SOURCES
    test_main.cpp
)

add_executable(shell_tests ${TEST_SOURCES})

target_link_libraries(shell_tests
    PRIVATE
        gtest_main
)

add_test(NAME ShellTests COMMAND shell_tests)