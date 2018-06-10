#pragma once

#include <google/protobuf/message_lite.h>


namespace cloud {
namespace utils {

class ProtobufFormatter {
public:
  static const std::string text(const google::protobuf::MessageLite& message) {
    throw std::runtime_error("Fomatter is not implemented.");
    return "";
  }

  static const std::string jsom(const google::protobuf::MessageLite& message) {
    throw std::runtime_error("Fomatter is not implemented.");
    return "";
  }
};

} // namespace utils
} // namespace cloud