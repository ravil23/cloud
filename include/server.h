#pragma once

#include <memory>

#include <glog/logging.h>
#include <grpc++/grpc++.h>

#include "utils/lexical_cast.h"


namespace cloud {

/**
 * \brief Template server class.
 * \tparam  Service  GRPC service for running.
 */
template <class Service>
class Server {
public:
  /**
   * \brief Constructor.
   * \throw   std::runtime_error  If environment variables are not valid.
   * \eparam  SERVER_NAME  Name of server instance.
   * \eparam  SERVER_PORT  Port of server instance.
   */
  Server() {
    auto env_name = std::getenv("SERVER_NAME");
    if (not env_name) {
      throw std::runtime_error("Environment variable 'SERVER_NAME' not found.");
    }

    auto env_port = std::getenv("SERVER_PORT");
    if (not env_port) {
      throw std::runtime_error("Environment variable 'SERVER_PORT' not found.");
    }

    FLAGS_alsologtostderr = 1;
    google::InitGoogleLogging(env_name);
    name_ = env_name;
    port_ = utils::lexical_cast<unsigned int>(env_port);
  }

  /**
   * \brief Run server and listen port on localhost.
   */
  void run() {
    DLOG(INFO) << "Run server " << name_ << " on port " << port_ << "...";

    Service service;
    grpc::ServerBuilder builder;
    auto address = "0.0.0.0:" + std::to_string(port_);

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    LOG(INFO) << "Server " << name_ << " listening on " << address;
    server->Wait();
  }

private:
  std::string name_;
  unsigned int port_;
};

} // namespace cloud