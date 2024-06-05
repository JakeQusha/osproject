cmake_minimum_required(VERSION 3.28)
project(osproject)

set(CMAKE_CXX_STANDARD 23)

add_executable(osproject src/main.cpp
        src/schduling/process.hpp
        src/schduling/generator.hpp
        src/schduling/schedulers.hpp
        src/schduling/schedulers.cpp
        src/schduling/simulator.cpp
        src/schduling/simulator.hpp
        src/schduling/generator.cpp
        src/input.cpp
        src/input.hpp)
