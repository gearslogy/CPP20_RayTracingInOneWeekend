cmake_minimum_required(VERSION 3.21)
project(one_weekend)
include_directories(D:/plugin_dev/libs/stb)

set(CMAKE_CXX_STANDARD 23)

add_executable(one_weekend main.cpp Vec.hpp Ray.hpp Utils.hpp Camera.hpp Hittable.hpp Kernel.hpp Prims.hpp Sampler.hpp)
