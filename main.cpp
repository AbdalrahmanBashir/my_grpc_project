#include <iostream>
#include <grpcpp/grpcpp.h>
#include "user_registration.grpc.pb.h"
#include "user_registration.pb.h"

using grpc::Status;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using usersystem::RegisterRequest;
using usersystem::RegisterResponse;
using usersystem::UserRegistration;
using usersystem::User;

class UserRegistrationService final : public UserRegistration::Service {

    Status RegisterUser(ServerContext* context, const RegisterRequest* request, RegisterResponse* response) override {
        // Implement user registration logic here
        const User& u = request->user();
        if (u.username().empty() || u.password().empty()) {
            return Status(grpc::INVALID_ARGUMENT, "Username and password cannot be empty.");
        }
        response->set_success(true);
        // Here you would typically save the user to a database or perform other logic.
        std::string user_name = u.username();
        response->set_message("User " + user_name + " registered successfully.");
        return Status::OK;
    }
};

int main() {
   
    std::string server_address("0.0.0.0:50051");
    UserRegistrationService service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
    return 0;
}