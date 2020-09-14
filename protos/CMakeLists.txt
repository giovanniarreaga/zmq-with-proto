# Minimum CMake required
cmake_minimum_required(VERSION 3.5)

# Project
project(proto-generations)

# Find required protobuf package
find_package(Protobuf REQUIRED)

# Print version messages
if(Protobuf_FOUND)
    message(STATUS "Using Protocol Buffers ${Protobuf_VERSION}")
endif()

# Generate header and source files for all the proto files
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER addressbook.proto)
add_library(proto ${PROTO_HEADER} ${PROTO_SRC})

