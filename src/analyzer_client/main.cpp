#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include <grpc++/grpc++.h>

#include "AnalyzerService.grpc.pb.h"

#include "utils/protobuf_stream.h"


namespace cloud {

class AnalyzerClient {
public:
  explicit AnalyzerClient(const std::string& server_address)
    : stub_(pb::Analyzer::NewStub(grpc::CreateChannel(server_address
      , grpc::InsecureChannelCredentials()))) {}

  pb::AnalyzerOutput analyze(const pb::AnalyzerInput& input) {
    pb::AnalyzerOutput output;

    grpc::ClientContext context;
    grpc::Status status = stub_->analyze(&context, input, &output);

    if (not status.ok()) {
      std::stringstream message;
      message << status.error_code() << ": " << status.error_message();
      throw std::runtime_error(message.str());
    }

    return output;
  };

private:
  std::unique_ptr<pb::Analyzer::Stub> stub_;
};

} // namespace cloud

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: analyzer-client <SERVER_HOST:PORT>" << std::endl;
    return EXIT_FAILURE;
  }

  const std::string program(argv[0]);
  const std::string server_address(argv[1]);

  cloud::AnalyzerClient client(server_address);

  cloud::utils::InputProtobufStream pbin("/dev/stdin");
  cloud::utils::OutputProtobufStream pbout("/dev/stdout");
  pb::AnalyzerInput input;
  while (pbin.read(input)) {
    try {
      pbout << client.analyze(input);
    } catch (const std::exception& e) {
      std::cerr << "Error on input with id=" << input.id()
        << ": " << e.what() << std::endl;
      return EXIT_FAILURE;
    } catch (...) {
      std::cerr << "Error on input with id=" << input.id()
        << ": unknown error" << std::endl;
      return EXIT_FAILURE;
    }
  }
}