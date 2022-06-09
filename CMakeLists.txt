cmake_minimum_required(VERSION 3.22)
project(httpcode)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -Werror)

find_package(tl-expected CONFIG REQUIRED)

add_executable(httpcode
        src/httpcode/main.cpp
        src/httpcode/util.cpp)
target_link_libraries(httpcode PRIVATE tl::expected)

# Build tests using: `cmake -DBUILD_TESTS=ON`
option(BUILD_TESTS "Build unit tests" OFF)
if (BUILD_TESTS)
    find_package(doctest CONFIG REQUIRED)
    add_executable(httpcode_test
            test/main.cpp
            test/httpcode_test.cpp)
    target_link_libraries(httpcode_test PRIVATE doctest::doctest)
endif()
