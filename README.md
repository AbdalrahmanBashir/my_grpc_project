# my_grpc_project  

![gRPC Logo](https://grpc.io/img/grpc-logo.png)  

A simple C++ gRPC service for user registration.  
Implements a **UserRegistration** RPC that accepts a **RegisterRequest** containing a **User** message and returns a **RegisterResponse** indicating success or failure.

---

## Features

- **Unary RPC**: `RegisterUser(RegisterRequest) → RegisterResponse`  
- **Input validation**: rejects empty usernames or passwords  
- **Plain‑text gRPC** (no TLS by default)  

---

## 🚀 Quick Start

### Prerequisites

- C++ compiler with C++11 support (e.g. `g++`, `clang++`)  
- CMake ≥ 3.10  
- gRPC C++ and protobuf runtime & compiler  

_On Ubuntu/Debian:_
```bash
sudo apt update
sudo apt install -y build-essential cmake \
     libgrpc++-dev libprotobuf-dev protobuf-compiler-grpc
```

### Clone & Build

```bash
git clone https://github.com/AbdalrahmanBashir/my_grpc_project.git
cd grpc-user-registration-cpp

mkdir build && cd build
cmake ..
make
```

This generates the executable **`my_grpc_project`** (the gRPC server).

---

## ▶️ Running the Server

```bash
cd build
./my_grpc_project
# Server listening on 0.0.0.0:50051
```

---

## 📝 Testing

### With the C++ Client

```bash
./user_reg_client
# Example outputs errors or success messages
```

### With grpcurl

```bash
grpcurl -plaintext \
  -d '{
    "user": {
      "username": "alice",
      "password": "s3cr3t",
      "email":    "alice@example.com",
      "age":      28
    }
  }' \
  localhost:50051 \
  usersystem.UserRegistration/RegisterUser
```

---

## 🔧 Project Layout

```
.
├── CMakeLists.txt
├── protos/
│   └── user_registration.proto
├── main.cpp          # server implementation
├── client.cpp        # simple sync client
└── build/            # CMake output
```

---

## ✨ Extending This Example

- Enable TLS by switching to `SslServerCredentials()`  
- Switch to async APIs for higher throughput  
- Add database integration in `RegisterUser`  
- Enhance validation with additional fields and checks  

---

## ⚖️ License

Released under the **MIT License**.  
