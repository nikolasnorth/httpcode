cmake_minimum_required(VERSION 3.22)
project(httpcode)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -Werror)

find_package(tl-expected CONFIG REQUIRED)

add_executable(httpcode src/main.cpp)
target_link_libraries(httpcode PRIVATE tl::expected)
