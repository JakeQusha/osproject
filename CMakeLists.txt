cmake_minimum_required(VERSION 3.28)
project(osproject)

set(CMAKE_CXX_STANDARD 23)

add_executable(osproject src/main.cpp
        src/process.hpp
        src/generator.hpp
        src/schedulers.hpp
        src/schedulers.cpp
        src/simulator.cpp
        src/simulator.hpp
        src/generator.cpp
        src/input.cpp
        src/input.hpp)
