#include <iostream>
#include <string>

#include "AnalyzerService.pb.h"

#include "utils/protobuf_stream.h"


int main(int argc, char** argv) {
  const std::string usage("bin/protobuf-writer"
    " <MESSAGE_TYPE: {AnalyzerInput}>"
    " <COUNT>");

  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]) == "-h" or std::string(argv[i]) == "--help") {
      std::cerr << "Protobuf Writer Tool" << std::endl
        << "Output:" << std::endl
        << " - Messages to STDOUT stream" << std::endl
        << "Usage:" << std::endl << usage << std::endl;
      return EXIT_SUCCESS;
    }
  }

  if (argc != 3) {
    std::cerr << usage << std::endl;
    return EXIT_FAILURE;
  }

  const std::string message_type(argv[1]);
  const int count = std::atoi(argv[2]);

  if (message_type != "AnalyzerInput") {
    throw std::invalid_argument("Invalid message type: " + message_type);
  }

  cloud::utils::OutputProtobufStream pbout("/dev/stdout");
  if (message_type != "AnalyzerInput") {
    pb::AnalyzerInput data;
    for (auto i = 1; i <= count; ++i) {
      data.set_id(std::to_string(i));
      data.set_timestamp(i);
      pbout << data;
    }
  }
}