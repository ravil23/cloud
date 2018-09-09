#include <algorithm>
#include <iostream>
#include <random>
#include <string>

#include "AnalyzerService.pb.h"

#include "utils/protobuf_stream.h"


namespace {

const auto INPUT_ID_LENGTH = 16;
const auto RANDOM_STRING_CHARSET = "0123456789abcdefghijklmnopqrstuvwxyz";

/**
 * \brief Generate random string.
 * \throw      std::invalid_argument  If charset is empty.
 * \param[in]  length   Output string length.
 * \param[in]  charset  String with supported symbols.
 * \return Generated string.
 */
std::string random_string(size_t length, const std::string& charset) {
  if (charset.empty()) {
    throw std::invalid_argument("Random string charset is empty.");
  }
  const size_t max_index = charset.size() - 1;
  std::string result(length, 0);
  std::generate_n(result.begin(), length, [&charset, &max_index]() -> char {
    return charset[std::rand() % max_index];
  });
  return result;
}

} // anonymous namespace

int main(int argc, char** argv) {
  const std::string usage = std::string(argv[0]) +
    " <MESSAGE_TYPE: {AnalyzerInput}>"
    " <COUNT>";

  // Print help if requested
  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]) == "-h" or std::string(argv[i]) == "--help") {
      std::cerr << "Protobuf Generator Tool" << std::endl
        << "Output:" << std::endl
        << " - Messages to STDOUT stream" << std::endl
        << "Usage:" << std::endl << usage << std::endl;
      return EXIT_SUCCESS;
    }
  }

  // Validate arguments
  if (argc != 3) {
    std::cerr << usage << std::endl;
    return EXIT_FAILURE;
  }

  const std::string message_type(argv[1]);
  const int count = std::atoi(argv[2]);

  if (message_type != "AnalyzerInput") {
    throw std::invalid_argument("Invalid message type: " + message_type);
  }

  // Randomize initilizer
  std::srand(unsigned(std::time(0)));

  // Generate messages and write its to output stream
  cloud::utils::OutputProtobufStream pbout("/dev/stdout");
  if (message_type == "AnalyzerInput") {
    pb::AnalyzerInput data;
    for (auto i = 1; i <= count; ++i) {
      data.set_id(random_string(INPUT_ID_LENGTH, RANDOM_STRING_CHARSET));
      data.set_timestamp(i);
      pbout << data;
    }
  }
}
