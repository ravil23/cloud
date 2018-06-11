#pragma once

#include <string>

#include <google/protobuf/message.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/util/json_util.h>


namespace cloud {
namespace utils {

class ProtobufFormatter {
public:
  static const std::string text(const google::protobuf::Message& message) {
    std::string text;
    google::protobuf::TextFormat::PrintToString(message, &text);
    return text;
  }

  static const std::string json(const google::protobuf::Message& message) {
    std::string json;
    google::protobuf::util::MessageToJsonString(message, &json);
    return json;
  }
};

} // namespace utils
} // namespace cloud