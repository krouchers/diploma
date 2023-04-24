include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(googletest)

message(STATUS "Creating tests...")

add_executable(math_test new_math_tests.cpp)

target_link_libraries(math_test gtest_main math)

enable_testing()
include(GoogleTest)

add_test(NAME math_test COMMAND math_test)

# Mark the test as failed if any gtest test fails
set_tests_properties(math_test PROPERTIES FAIL_REGULAR_EXPRESSION ".*\\[  FAILED  \\].*")