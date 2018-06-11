#include <iostream>
#include <sstream>
#include <string>

#include "AnalyzerService.pb.h"

#include "utils/protobuf_formatter.h"
#include "utils/protobuf_stream.h"


namespace {

class AnalyzerInputFormatter : public cloud::utils::ProtobufFormatter {
public:
  static const std::string info(const pb::AnalyzerInput& analyzer_input) {
    std::stringstream ss;
    ss << "ID: " << analyzer_input.id()
      << ", Timestamp: " << analyzer_input.timestamp();
    return ss.str();
  }
};

class AnalyzerOutputFormatter : public cloud::utils::ProtobufFormatter {
public:
  static const std::string info(const pb::AnalyzerOutput& analyzer_output) {
    std::stringstream ss;
    ss << "Categories[" << analyzer_output.categories().size() << "]: {";
    auto is_first = true;
    for (const auto& category : analyzer_output.categories()) {
      if (not is_first) {
        ss << ", ";
      } else {
        is_first = false;
      }
      ss << category.name() <<
        " : " << category.score() <<
        " : " << category.normed_score();
    }
    ss << "}";
    return ss.str();
  }
};

} // anonymous namespace

int main(int argc, char** argv) {
  const std::string usage("bin/protobuf-reader"
    " <MESSAGE_TYPE: {AnalyzerInput, AnalyzerOutput}>"
    " <FORMAT: {info, text, json}>");

  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]) == "-h" or std::string(argv[i]) == "--help") {
      std::cerr << "Protobuf Reader Tool" << std::endl
        << "Input:" << std::endl
        << " - Protobuf messages from STDIN stream" << std::endl
        << "Output:" << std::endl
        << " - Formatted messages to STDOUT stream" << std::endl
        << "Usage:" << std::endl << usage << std::endl;
      return EXIT_SUCCESS;
    }
  }

  if (argc != 3) {
    std::cerr << "Usage:" << usage << std::endl;
    return EXIT_FAILURE;
  }

  const std::string program(argv[0]);
  const std::string message_type(argv[1]);
  const std::string format(argv[2]);

  if (message_type != "AnalyzerInput" and message_type != "AnalyzerOutput") {
    throw std::invalid_argument("Invalid message type: " + message_type);
  }

  if (format != "info") {
    throw std::invalid_argument("Invalid format: " + format);
  }

  cloud::utils::InputProtobufStream pbin("/dev/stdin");
  if (message_type == "AnalyzerInput") {
    pb::AnalyzerInput analyzer_input;
    while (pbin.read(analyzer_input)) {
      if (format == "info") {
        std::cout << AnalyzerInputFormatter::info(analyzer_input) << std::endl;
      }
    }
  } else if (message_type == "AnalyzerOutput") {
    pb::AnalyzerOutput analyzer_output;
    while (pbin.read(analyzer_output)) {
      if (format == "info") {
        std::cout << AnalyzerOutputFormatter::info(analyzer_output) << std::endl;
      }
    }
  }
}