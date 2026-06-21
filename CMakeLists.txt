cmake_minimum_required(VERSION 3.20)

project(Graphion LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(deps/glfw)

add_subdirectory(deps/fmt)

add_executable(Graphion src/main.cpp)

target_include_directories(Graphion PRIVATE deps)
target_include_directories(Graphion PRIVATE src)

target_compile_options(Graphion PRIVATE
    -Wall
    -Wextra
    -g
)

target_link_libraries(Graphion PRIVATE glfw)
target_link_libraries(Graphion PRIVATE fmt)
