cmake_minimum_required(VERSION 3.10)
project(MyGRPCProject CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(gRPC REQUIRED)
find_package(Protobuf REQUIRED)

# Where to put generated .pb/.grpc.pb files
set(PROTO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)

# Make sure the output directory exists
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})

# Grab all your .proto files
file(GLOB PROTO_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/protos/*.proto
)

find_program(_gRPC_CPP_PLUGIN_EXECUTABLE
  NAMES grpc_cpp_plugin
  HINTS ENV PATH
)

if(NOT _gRPC_CPP_PLUGIN_EXECUTABLE)
  message(FATAL_ERROR "grpc_cpp_plugin not found! Install gRPC C++ plugin or add it to your PATH.")
endif()

# 1) Custom command: run protoc whenever a .proto changes
add_custom_command(
  OUTPUT
    ${PROTO_SRC_DIR}/user_registration.pb.cc
    ${PROTO_SRC_DIR}/user_registration.pb.h
    ${PROTO_SRC_DIR}/user_registration.grpc.pb.cc
    ${PROTO_SRC_DIR}/user_registration.grpc.pb.h
  COMMAND ${Protobuf_PROTOC_EXECUTABLE}
  ARGS
    --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/protos
    --cpp_out=${PROTO_SRC_DIR}
    --grpc_out=${PROTO_SRC_DIR}
    --plugin=protoc-gen-grpc=${_gRPC_CPP_PLUGIN_EXECUTABLE}
    ${PROTO_FILES}
  DEPENDS ${PROTO_FILES}
  COMMENT "Generating C++ protobuf and gRPC bindings"
)

# 2) A custom target that groups all generated artifacts
add_custom_target(
  grpc_gen
  DEPENDS
    ${PROTO_SRC_DIR}/user_registration.pb.cc
    ${PROTO_SRC_DIR}/user_registration.grpc.pb.cc
)

# 3) Include the generated headers
include_directories(${PROTO_SRC_DIR})

# 4) List out the generated source files so CMake can compile them
set(GRPC_SRCS
  ${PROTO_SRC_DIR}/user_registration.pb.cc
  ${PROTO_SRC_DIR}/user_registration.grpc.pb.cc
)

# 5) Your executable: main.cpp + the generated .cc files
add_executable(my_grpc_app
  main.cpp
  ${GRPC_SRCS}
)

# 6) Make sure the code is generated before we try to compile
add_dependencies(my_grpc_app grpc_gen)

# 7) Link to gRPC and Protobuf libraries
target_link_libraries(my_grpc_app
  PRIVATE
    gRPC::grpc++
    protobuf::libprotobuf
)
