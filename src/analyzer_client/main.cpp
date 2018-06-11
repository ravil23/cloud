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
  const std::string usage("bin/analyzer-client"
    " <SERVER_HOST:PORT>");

  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]) == "-h" or std::string(argv[i]) == "--help") {
      std::cerr << "Analyzer Client" << std::endl
        << "Input:" << std::endl
        << " - pb::AnalyzerInput to STDIN stream" << std::endl
        << "Output:" << std::endl
        << " - pb::AnalyzerOutput to STDOUT stream" << std::endl
        << "Usage:" << std::endl << usage << std::endl;
      return EXIT_SUCCESS;
    }
  }

  if (argc != 2) {
    std::cerr << usage << std::endl;
    return EXIT_FAILURE;
  }

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