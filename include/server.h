#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>


namespace cfa {

template <class Service>
class Server {
public:
  explicit Server(const std::string& port)
    : address_("0.0.0.0:" + port) {}

  void run() {
    Service service;
    grpc::ServerBuilder builder;
    builder.AddListeningPort(address_, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << address_ << std::endl;
    server->Wait();
  }

private:
  std::string address_;
};

} // namespace cfa