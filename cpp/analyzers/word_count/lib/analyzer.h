#pragma once

#include <grpc++/grpc++.h>

#include "cpp/analyzers/analyzer_interface.h"

#include "protobuf/AnalyzerService.pb.h"


namespace cloud {

/**
 * \brief Word counter for corresponded service.
 */
class WordCountAnalyzer : public AnalyzerInterface {
public:
  /**
   * \brief Process new input.
   * \param[in]  input  Analyzer input.
   * \param[out] output Analyzer output.
   */
  grpc::Status analyze(const pb::AnalyzerInput& input,
                       pb::AnalyzerOutput& output) override final;
};

} // namespace cloud
