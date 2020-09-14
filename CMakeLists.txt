# Minimum CMake required
cmake_minimum_required(VERSION 3.5)

# Project
project(zmq-with-proto)

add_subdirectory(protos)
add_subdirectory(src)