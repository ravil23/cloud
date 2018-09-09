#pragma once

#include <glog/logging.h>
#include <grpc++/grpc++.h>

#include "analyzer_service.h"
#include "unique_inputs_counter.h"

#include "AnalyzerService.grpc.pb.h"


namespace cloud {

/**
 * \brief Implementation of unique inputs count service.
 */
class UniqueInputsCountAnalyzer final : public AnalyzerService {
private:
  /**
   * \brief Analyzing implementation.
   * \param[in]  input   Input object.
   * \param[out] output  Output object.
   * \return  Analyzing status.
   */
  grpc::Status analyzeImpl(const pb::AnalyzerInput& input
    , pb::AnalyzerOutput& output) override final {
    DLOG(INFO) << "start  InputsCountAnalyzer::analyzeImpl " << input.id();

    auto result = unique_inputs_counter_.updateAndAnalyze(input);
    if (result.new_input_) {
      auto add_ptr = output.add_categories();
      add_ptr->set_name("Unique Inputs Count");
      add_ptr->set_score(result.unique_count_);
      add_ptr->set_normed_score(1. - 1. / result.unique_count_);
    }

    DLOG(INFO) << "finish InputsCountAnalyzer::analyzeImpl " << input.id();
    return grpc::Status::OK;
  }

  UniqueInputsCounter unique_inputs_counter_;
};

} // namespace cloud