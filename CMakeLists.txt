cmake_minimum_required(VERSION 3.6)
project(SimuladorSD)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Processo.h Processo.cpp)
add_executable(SimuladorSD ${SOURCE_FILES})