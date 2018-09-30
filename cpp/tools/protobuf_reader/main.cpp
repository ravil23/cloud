#include <iostream>
#include <sstream>
#include <string>

#include "AnalyzerService.pb.h"

#include "utils/protobuf_formatter.h"
#include "utils/protobuf_stream.h"


namespace {

/**
 * \brief Formatter for analyzer input.
 */
class AnalyzerInputFormatter : public cloud::utils::ProtobufFormatter {
public:
  /**
   * \brief Convert message to csv format.
   * \param[in]  message    Input protobuf message.
   * \param[in]  delimiter  Separator symbol.
   * \return  Formatted string.
   */
  static const std::string csv(const pb::AnalyzerInput& analyzer_input, char delimiter) {
    std::stringstream ss;
    ss << analyzer_input.id() << delimiter << analyzer_input.timestamp();
    return ss.str();
  }

  /**
   * \brief Convert message to tsv format.
   * \param[in]  message    Input protobuf message.
   * \return  Formatted string.
   */
  static const std::string tsv(const pb::AnalyzerInput& analyzer_input) {
    return AnalyzerInputFormatter::csv(analyzer_input, '\t');
  }
};

/**
 * \brief Formatter for analyzer output.
 */
class AnalyzerOutputFormatter : public cloud::utils::ProtobufFormatter {
public:
  /**
   * \brief Convert message to csv format.
   * \param[in]  message    Input protobuf message.
   * \param[in]  delimiter  Separator symbol.
   * \return  Formatted string.
   */
  static const std::string csv(const pb::AnalyzerOutput& analyzer_output, char delimiter) {
    std::stringstream ss;
    ss << "[";
    auto is_first = true;
    for (const auto& category : analyzer_output.categories()) {
      if (not is_first) {
        ss << ", ";
      } else {
        is_first = false;
      }
      ss << category.name();
    }
    ss << "]" << delimiter << "[";
    is_first = true;
    for (const auto& category : analyzer_output.categories()) {
      if (not is_first) {
        ss << ", ";
      } else {
        is_first = false;
      }
      ss << category.score();
    }
    ss << "]" << delimiter << "[";
    is_first = true;
    for (const auto& category : analyzer_output.categories()) {
      if (not is_first) {
        ss << ", ";
      } else {
        is_first = false;
      }
      ss << category.normed_score();
    }
    ss << "]";
    return ss.str();
  }

  /**
   * \brief Convert message to tsv format.
   * \param[in]  message    Input protobuf message.
   * \return  Formatted string.
   */
  static const std::string tsv(const pb::AnalyzerOutput& analyzer_output) {
    return AnalyzerOutputFormatter::csv(analyzer_output, '\t');
  }
};

} // anonymous namespace

int main(int argc, char** argv) {
  const std::string usage = std::string(argv[0]) +
    " <MESSAGE_TYPE: {AnalyzerInput, AnalyzerOutput}>"
    " <FORMAT: {tsv, text, json}>";

  // Print help if requested
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

  // Validate arguments
  if (argc != 3) {
    std::cerr << "Usage: " << usage << std::endl;
    return EXIT_FAILURE;
  }

  const std::string program(argv[0]);
  const std::string message_type(argv[1]);
  const std::string format(argv[2]);

  if (message_type != "AnalyzerInput" and message_type != "AnalyzerOutput") {
    throw std::invalid_argument("Invalid message type: " + message_type);
  }

  if (format != "tsv" and format != "text" and format != "json") {
    throw std::invalid_argument("Invalid format: " + format);
  }

  // Process messages from input stream and write results to output stream
  cloud::utils::InputProtobufStream pbin("/dev/stdin");
  if (message_type == "AnalyzerInput") {
    pb::AnalyzerInput analyzer_input;
    while (pbin.read(analyzer_input)) {
      if (format == "tsv") {
        std::cout << AnalyzerInputFormatter::tsv(analyzer_input) << std::endl;
      } else if (format == "text") {
        std::cout << AnalyzerInputFormatter::text(analyzer_input) << std::endl;
      } else if (format == "json") {
        std::cout << AnalyzerInputFormatter::json(analyzer_input) << std::endl;
      }
    }
  } else if (message_type == "AnalyzerOutput") {
    pb::AnalyzerOutput analyzer_output;
    while (pbin.read(analyzer_output)) {
      if (format == "tsv") {
        std::cout << AnalyzerOutputFormatter::tsv(analyzer_output) << std::endl;
      } else if (format == "text") {
        std::cout << AnalyzerOutputFormatter::text(analyzer_output) << std::endl;
      } else if (format == "json") {
        std::cout << AnalyzerOutputFormatter::json(analyzer_output) << std::endl;
      }
    }
  }
}
