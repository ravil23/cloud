#include <iostream>

#include "AnalyzerService.pb.h"

#include "utils/protobuf_stream.h"


int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: protobuf-writer <COUNT>";
    return EXIT_FAILURE;
  }

  auto count = std::atoi(argv[1]);

  cloud::utils::OutputProtobufStream pbout("/dev/stdout");
  pb::AnalyzerInput data;
  for (auto i = 1; i <= count; ++i) {
    data.set_id(std::to_string(i));
    data.set_timestamp(i);
    pbout << data;
  }
}