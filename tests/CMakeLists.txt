include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(googletest)

message(STATUS "Creating tests...")

add_executable(math_test math_tests.cpp)

target_link_libraries(math_test gtest math)

enable_testing()
include(GoogleTest)
gtest_discover_tests(math_test)