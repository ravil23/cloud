#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include <glog/logging.h>
#include <grpc++/grpc++.h>

#include "AnalyzerService.grpc.pb.h"


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
  if (argc <= 2) {
    std::cerr << "Usage: <CLIENT_BINARY> <SERVER_ADDRESS:PORT> <ID1> <ID2> ..." << std::endl;
    return EXIT_FAILURE;
  }

  FLAGS_alsologtostderr = 1;
  google::InitGoogleLogging(argv[0]);

  cloud::AnalyzerClient client(argv[1]);

  for (auto i = 2; i < argc; ++i) { // TODO: read from stream
    pb::AnalyzerInput input;
    input.set_id(argv[i]);
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