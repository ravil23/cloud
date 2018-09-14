#pragma once

#include <fstream>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/message_lite.h>


namespace cloud {
namespace utils {

class InputProtobufStream;
class OutputProtobufStream;

/**
 * \brief Implementation of input protobuf stream.
 */
class InputProtobufStream {
public:
  /**
   * \brief Constructor.
   * \param[in]  path  Path of input stream.
   */
  explicit InputProtobufStream(const std::string& path)
    : std_stream_(path)
    , pb_stream_(&std_stream_) {}

  /**
   * \brief Check if stream is open.
   * \return  Stream status.
   */
  inline bool is_open() {
    return std_stream_.is_open();
  }

  /**
   * \brief Read message from stream.
   * \param[out] message  Readed message.
   * \return  Read status.
   */
  bool read(google::protobuf::MessageLite& message) {
    if (not is_open()) {
      return false;
    }

    // Clear output message.
    message.Clear();

    // We create a new coded stream for each message.  Don't worry, this is fast,
    // and it makes sure the 64MB total size limit is imposed per-message rather
    // than on the whole stream.  (See the CodedInputStream interface for more
    // info on this limit.)
    google::protobuf::io::CodedInputStream input(&pb_stream_);

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

  /**
   * \brief Input stream operator.
   * \throw      std::runtime_error  If message reading status is false.
   * \param[out] message  Readed message.
   * \return  Reference to this object.
   */
  InputProtobufStream& operator>>(google::protobuf::MessageLite& message) {
    if (not read(message)) {
      throw std::runtime_error("Can't read next message.");
    }
    return *this;
  }

private:
  std::ifstream std_stream_;
  google::protobuf::io::IstreamInputStream pb_stream_;
};

/**
 * \brief Implementation of output protobuf stream.
 */
class OutputProtobufStream {
public:
  /**
   * \brief Constructor.
   * \param[out] path  Path of output stream.
   */
  explicit OutputProtobufStream(const std::string& path)
    : std_stream_(path)
    , pb_stream_(&std_stream_) {}

  /**
   * \brief Check if stream is open.
   * \return  Stream status.
   */
  inline bool is_open() {
    return std_stream_.is_open();
  }

  /**
   * \brief Write message from stream.
   * \param[in]  message  Message for writting.
   * \return  Write status.
   */
  bool write(const google::protobuf::MessageLite& message) {
    if (not is_open()) {
      return false;
    }

    // We create a new coded stream for each message. Don't worry, this is fast.
    google::protobuf::io::CodedOutputStream output(&pb_stream_);

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

  /**
   * \brief Output stream operator.
   * \throw      std::runtime_error  If message writting status is false.
   * \param[out] message  Message for writting.
   * \return  Reference to this object.
   */
  OutputProtobufStream& operator<<(const google::protobuf::MessageLite& message) {
    if (not write(message)) {
      throw std::runtime_error("Can't write next message.");
    }
    return *this;
  }

private:
  std::ofstream std_stream_;
  google::protobuf::io::OstreamOutputStream pb_stream_;
};

} // namespace utils
} // namespace cloud
