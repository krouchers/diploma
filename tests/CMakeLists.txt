include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(googletest)

message(STATUS "Creating tests...")

add_executable(math_test math_tests.cpp)
add_executable(halfedge_test halfedge_tests.cpp)

target_link_libraries(math_test gtest_main math)
target_link_libraries(halfedge_test gtest_main math geometry)

enable_testing()

add_test(NAME math_test COMMAND math_test)
add_test(NAME halfedge_test COMMAND halfedge_test)

file(COPY_FILE ${PROJECT_SOURCE_DIR}/bin/glad.dll ${PROJECT_BINARY_DIR}/tests/glad.dll)

# Mark the test as failed if any gtest test fails
set_tests_properties(math_test PROPERTIES FAIL_REGULAR_EXPRESSION ".*\\[  FAILED  \\].*")
set_tests_properties(halfedge_test PROPERTIES FAIL_REGULAR_EXPRESSION ".*\\[  FAILED  \\].*")