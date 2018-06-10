#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include <glog/logging.h>
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
    DLOG(INFO) << "start  AnalyzerClient::analyze " << input.id();
    pb::AnalyzerOutput output;

    grpc::ClientContext context;
    grpc::Status status = stub_->analyze(&context, input, &output);

    if (not status.ok()) {
      std::stringstream message;
      message << status.error_code() << ": " << status.error_message();
      throw std::runtime_error(message.str());
    }

    DLOG(INFO) << "finish AnalyzerClient::analyze " << input.id();
    return output;
  };

private:
  std::unique_ptr<pb::Analyzer::Stub> stub_;
};

} // namespace cloud

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: <PROGRAM> <SERVER_ADDRESS:PORT> [<INPUT_STREAM> (default=/dev/stdin)]" << std::endl;
    return EXIT_FAILURE;
  }
  const std::string program(argv[0]);
  const std::string server_address(argv[1]);
  std::string input_stream("/dev/stdin");
  if (argc > 2) {
    input_stream = argv[2];
  }

  FLAGS_alsologtostderr = 1;
  google::InitGoogleLogging(program.c_str());

  cloud::AnalyzerClient client(server_address);

  cloud::utils::InputProtobufStream fin(input_stream);
  pb::AnalyzerInput input;
  while (fin.read(input)) {
    try {
      auto output = client.analyze(input);
      std::stringstream ss;
      ss << "Categories[" << output.categories().size() << "]: {";
      auto is_first = true;
      for (const auto& category : output.categories()) {
        if (not is_first) {
          ss << ", ";
        } else {
          is_first = false;
        }
        ss << category.name() << " : " << category.score() << " : " << category.normed_score();
      }
      LOG(INFO) << ss.str() << "}";
    } catch (const std::exception& e) {
      LOG(ERROR) << "Error on input " << input.id() << ": " << e.what() << std::endl;
    } catch (...) {
      LOG(ERROR) << "Error on input " << input.id() << ": unknown error" << std::endl;
    }
  }
}