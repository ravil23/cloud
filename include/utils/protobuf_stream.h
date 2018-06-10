#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/message_lite.h>


namespace cloud {
namespace utils {

class InputProtobufStream;
class OutputProtobufStream;

class InputProtobufStream {
public:
  explicit InputProtobufStream(const std::string& path)
    : handle_(open(path.c_str(), O_RDONLY))
    , fin_(handle_) {}

  inline bool is_open() {
    return handle_ != -1;
  }

  bool read(google::protobuf::MessageLite& message) {
    if (not is_open()) {
      return false;
    }

    // We create a new coded stream for each message.  Don't worry, this is fast,
    // and it makes sure the 64MB total size limit is imposed per-message rather
    // than on the whole stream.  (See the CodedInputStream interface for more
    // info on this limit.)
    google::protobuf::io::CodedInputStream input(&fin_);

    // Read the size.
    uint32_t size;
    if (not input.ReadVarint32(&size)) {
      return false;
    }

    // Tell the stream not to read beyond that size.
    google::protobuf::io::CodedInputStream::Limit limit =
        input.PushLimit(size);

    // Parse the message.
    if (not message.MergeFromCodedStream(&input)) {
      return false;
    }
    if (not input.ConsumedEntireMessage()) {
      return false;
    }

    // Release the limit.
    input.PopLimit(limit);

    return true;
  }

  InputProtobufStream& operator>>(google::protobuf::MessageLite& message) {
    if (not read(message)) {
      throw std::runtime_error("Can't read next message.");
    }
    return *this;
  }

  ~InputProtobufStream() {
    if (is_open()) {
      close(handle_);
    }
  }

private:
  int handle_;
  google::protobuf::io::FileInputStream fin_;
};

class OutputProtobufStream {
public:
  explicit OutputProtobufStream(const std::string& path)
    : handle_(open(path.c_str(), O_CREAT | O_WRONLY))
    , fout_(handle_) {}

  inline bool is_open() {
    return handle_ != -1;
  }

  bool write(const google::protobuf::MessageLite& message) {
    if (not is_open()) {
      return false;
    }

    // We create a new coded stream for each message. Don't worry, this is fast.
    google::protobuf::io::CodedOutputStream output(&fout_);

    // Write the size.
    const int size = message.ByteSize();
    output.WriteVarint32(size);

    uint8_t* buffer = output.GetDirectBufferForNBytesAndAdvance(size);
    if (buffer != NULL) {
      // Optimization:  The message fits in one buffer, so use the faster
      // direct-to-array serialization path.
      message.SerializeWithCachedSizesToArray(buffer);
    } else {
      // Slightly-slower path when the message is multiple buffers.
      message.SerializeWithCachedSizes(&output);
      if (output.HadError()) {
        return false;
      }
    }

    return true;
  }

  OutputProtobufStream& operator<<(const google::protobuf::MessageLite& message) {
    if (not write(message)) {
      throw std::runtime_error("Can't write next message.");
    }
    return *this;
  }

  ~OutputProtobufStream() {
    if (is_open()) {
      close(handle_);
    }
  }

private:
  int handle_;
  google::protobuf::io::FileOutputStream fout_;
};

} // namespace utils
} // namespace cloud