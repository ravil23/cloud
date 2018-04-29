#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include <grpc++/grpc++.h>

#include "AnalyzerService.grpc.pb.h"


namespace cfa {

class AnalyzerClient {
public:
  explicit AnalyzerClient(const std::string& server_address)
    : stub_(Analyzer::NewStub(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()))) {}

  AnalyzerOutput analyze(const AnalyzerInput& input) {
    std::cout << "start  AnalyzerClient::analyze " << input.id() << std::endl;
    AnalyzerOutput output;

    grpc::ClientContext context;
    grpc::Status status = stub_->analyze(&context, input, &output);

    if (not status.ok()) {
      std::stringstream message;
      message << status.error_code() << ": " << status.error_message();
      throw std::runtime_error(message.str());
    }
    std::cout << "finish AnalyzerClient::analyze " << input.id() << std::endl;
    return output;
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
    cfa::AnalyzerInput input;
    input.set_id(argv[i]);
    try {
      auto output = client.analyze(input);
      std::cout << "Categories count: " << output.categories().size() << std::endl;
      for (const auto& category : output.categories()) {
        std::cout << category.name() << '\t' << category.score() << '\t' << category.normed_score() << std::endl;
      }
    } catch (const std::runtime_error& e) {
      std::cerr << "Error on input " << input.id() << ": " << e.what() << std::endl;
    }
  }
  return EXIT_SUCCESS;
}