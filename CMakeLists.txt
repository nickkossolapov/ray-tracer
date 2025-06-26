cmake_minimum_required(VERSION 3.31)
project(ray_tracer)

set(SDL3_DIR "D:/libraries/SDL3")

include_directories(${SDL3_DIR}/include)
link_directories(${SDL3_DIR}/lib)

set(CMAKE_CXX_STANDARD 20)

add_executable(ray_tracer src/main.cpp)

target_link_libraries(ray_tracer SDL3)
