cmake_minimum_required(VERSION 3.20)
project(renderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_library(raytracer INTERFACE)
target_include_directories(raytracer INTERFACE include)

add_executable(prog src/main.cpp)
target_link_libraries(prog PRIVATE raytracer)
target_compile_options(prog PRIVATE -Wall -Wextra -Wpedantic)

add_executable(tests
    tests/test_main.cpp
    tests/test_tuple.cpp
    tests/test_color.cpp
    tests/test_canvas.cpp
    tests/test_matrix.cpp
)
target_link_libraries(tests PRIVATE raytracer)
target_include_directories(tests PRIVATE third_party)
target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic)
