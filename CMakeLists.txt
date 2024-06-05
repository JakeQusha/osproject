cmake_minimum_required(VERSION 3.28)
project(osproject)

set(CMAKE_CXX_STANDARD 23)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(COMPILE_FLAGS -Wall -Wextra -Wpedantic -Wconversion)
endif()

add_executable(osproject src/main.cpp
        src/scheduling/process.hpp
        src/generator.hpp
        src/scheduling/schedulers.hpp
        src/scheduling/schedulers.cpp
        src/scheduling/simulator.cpp
        src/scheduling/simulator.hpp
        src/generator.cpp
        src/input.cpp
        src/input.hpp
        src/paging/fakemain.cpp
        src/paging/fakemain.h)
