# my_grpc_project


A simple C++ gRPC service for user registration.
Implements a UserRegistration RPC that accepts a RegisterRequest containing a User message and returns a RegisterResponse indicating success or failure.

Features:
- Unary RPC: RegisterUser(RegisterRequest) -> RegisterResponse
- Input validation: rejects empty usernames or passwords
- Plain-text gRPC no TLS by default

Quick Start:
Prerequisites:
- C++ compiler with C++11 support (e.g. g++, clang++)
- CMake >= 3.10
- gRPC C++ and protobuf runtime & compiler

On Ubuntu/Debian:
sudo apt update
sudo apt install -y build-essential cmake \\
     libgrpc++-dev libprotobuf-dev protobuf-compiler-grpc

Clone & Build:
git clone https://github.com/abdalrahmanbashir/grpc-user-registration-cpp.git
cd grpc-user-registration-cpp

mkdir build && cd build
cmake ..
make

This generates executable my_grpc_project – the gRPC server

Running the Server:
cd build
./user_reg_server
# Server listening on 0.0.0.0:50051

Testing with the C++ Client:
./user_reg_client
# Example outputs errors or success messages

Testing with grpcurl:
grpcurl -plaintext -d '{"user":{"username":"alice","password":"s3cr3t","email":"alice@example.com","age":28}}' localhost:50051 usersystem.UserRegistration/RegisterUser

Extending This Example:
- Enable TLS by switching to SslServerCredentials()
- Switch to async APIs for higher throughput
- Add database integration in RegisterUser
- Enhance validation with additional fields and checks

License:
MIT License