#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include <grpc++/grpc++.h>

#include "protobuf/AnalyzerService.grpc.pb.h"

#include "cpp/utils/protobuf_stream.h"


namespace cloud {

/**
 * \brief Client for analyzer service.
 */
class AnalyzerClient {
public:
  /**
   * \brief Constructor.
   * \param[in]  server_address  Service address in format <HOST:PORT>.
   */
  explicit AnalyzerClient(const std::string& server_address)
    : stub_(pb::Analyzer::NewStub(grpc::CreateChannel(server_address
      , grpc::InsecureChannelCredentials()))) {}

  /**
   * \brief Analyzing method.
   * \throw      std::runtime_error  If service return error status.
   * \param[in]  input  Analyzer input.
   * \return  Analyzer output.
   */
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
  const std::string usage = std::string(argv[0]) +
    " <SERVER_HOST:PORT>";

  // Print help if requested
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

  // Validate arguments
  if (argc != 2) {
    std::cerr << "Usage: " << usage << std::endl;
    return EXIT_FAILURE;
  }

  // Create analyzer client for passed server address
  const std::string server_address(argv[1]);
  cloud::AnalyzerClient client(server_address);

  // Create protobuf input and output streams
  cloud::utils::InputProtobufStream pbin("/dev/stdin");
  cloud::utils::OutputProtobufStream pbout("/dev/stdout");

  // Process messages from input stream and write results to output stream
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
