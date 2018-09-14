#pragma once

#include <string>

#include <google/protobuf/message.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/util/json_util.h>


namespace cloud {
namespace utils {

/**
 * \brief Class for converting protobuf messages to different format.
 */
class ProtobufFormatter {
public:
  /**
   * \brief Convert message to text format.
   * \param[in]  message  Input protobuf message.
   * \return  Formatted string.
   */
  static const std::string text(const google::protobuf::Message& message) {
    std::string text;
    google::protobuf::TextFormat::PrintToString(message, &text);
    return text;
  }

  /**
   * \brief Convert message to json format.
   * \param[in]  message  Input protobuf message.
   * \return  Formatted string.
   */
  static const std::string json(const google::protobuf::Message& message) {
    std::string json;
    google::protobuf::util::MessageToJsonString(message, &json);
    return json;
  }
};

} // namespace utils
} // namespace cloud
