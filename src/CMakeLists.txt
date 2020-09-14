# Minimum CMake required
cmake_minimum_required(VERSION 3.5)

# Project
project(zmq-with-proto-src)

# Load proto support
include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(
	"../build/protos"
	${PROTOBUF_INCLUDE_DIR}
)

if(Protobuf_FOUND)
    message(STATUS "Using Protocol Buffers ${Protobuf_VERSION}")
endif()

# Load zmq support
find_package(PkgConfig)
find_package(ZeroMQ REQUIRED)

# use pkg-config to get hints for 0mq locations
pkg_check_modules(PC_ZeroMQ QUIET zmq)
pkg_search_module(ZMQ libzmq)

if (ZMQ_FOUND)
	message(STATUS "Found ZeroMQ")
else ()
	message(STATUS "ZMQ Not Found")
endif()

# Use the hint from above to find where 'zmq.hpp' is located
find_path(ZeroMQ_INCLUDE_DIR
	NAMES zmq.hpp
	PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
)

# Zmq examples  ---- Not Necessary for ZMQ server
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(proto_add add_person.cpp)
add_executable(proto_list list_people.cpp)
target_link_libraries(proto_add proto ${PROTOBUF_LIBRARY})
target_link_libraries(proto_list proto ${PROTOBUF_LIBRARY})

# generate client exec
set(HEADER_FILES zmq.hpp)
add_executable(proto_client main.cpp ${HEADER_FILES})
target_link_libraries(proto_client proto 
	${ZeroMQ_LIBRARY}
	${PROTOBUF_LIBRARY}
)

# generate server exec
add_executable(proto_server zmqserver.cpp ${HEADER_FILES})
target_link_libraries(proto_server proto 
	${ZeroMQ_LIBRARY}
	${PROTOBUF_LIBRARY}
)
