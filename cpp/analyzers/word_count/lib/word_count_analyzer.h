#pragma once

#include <grpc++/grpc++.h>

#include "analyzer_interface.h"

#include "AnalyzerService.pb.h"


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
