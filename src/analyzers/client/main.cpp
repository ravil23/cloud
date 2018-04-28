#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include <grpc++/grpc++.h>

#include "analyzer_service.grpc.pb.h"


namespace cfa {

class AnalyzerClient {
public:
  explicit AnalyzerClient(const std::string& server_address)
    : stub_(Analyzer::NewStub(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()))) {}

  Result analyze(const Fact& fact) {
    std::cout << "start  AnalyzerClient::analyze " << fact.id() << std::endl;
    Result result;

    grpc::ClientContext context;
    grpc::Status status = stub_->analyze(&context, fact, &result);

    if (not status.ok()) {
      std::stringstream message;
      message << status.error_code() << ": " << status.error_message();
      throw std::runtime_error(message.str());
    }
    std::cout << "finish AnalyzerClient::analyze " << fact.id() << std::endl;
    return result;
  };

private:
  std::unique_ptr<Analyzer::Stub> stub_;
};

} // namespace cfa

int main(int argc, char** argv) {
  if (argc <= 2) {
    std::cerr << "Usage: <CLIENT_BINARY> <SERVER_ADDRESS:PORT> <ID1> <ID2> ..." << std::endl;
    return EXIT_FAILURE;
  }

  cfa::AnalyzerClient client(argv[1]);

  for (auto i = 2; i < argc; ++i) {
    cfa::Fact fact;
    fact.set_id(argv[i]);
    try {
      auto result = client.analyze(fact);
      std::cout << "Categories count: " << result.categories().size() << std::endl;
    } catch (const std::runtime_error& e) {
      std::cerr << "Error on fact " << fact.id() << ": " << e.what() << std::endl;
    }
  }
  return EXIT_SUCCESS;
}