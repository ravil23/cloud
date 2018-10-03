#pragma once

#include <grpc++/grpc++.h>

#include "protobuf/AnalyzerService.pb.h"


namespace cloud {

/**
 * \brief Interface of analyzer implementation.
 */
class AnalyzerInterface {
public:
  /**
   * \brief Process new input.
   * \param[in]  input  Analyzer input.
   * \param[out] output Analyzer output.
   */
  virtual grpc::Status analyze(const pb::AnalyzerInput& input,
  	                           pb::AnalyzerOutput& output) = 0;
};

} // namespace cloud
