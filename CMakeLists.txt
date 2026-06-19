cmake_minimum_required(VERSION 3.20)

project(Graphion LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(GLFW STATIC IMPORTED)

set_target_properties(GLFW PROPERTIES
    IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/deps/GLFW/libglfw3.a
)

add_executable(Graphion src/main.cpp)

target_include_directories(Graphion PRIVATE deps)

target_compile_options(Graphion PRIVATE
    -Wall
    -Wextra
    -g
)

target_link_libraries(Graphion PRIVATE GLFW)
