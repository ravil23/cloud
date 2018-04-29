#pragma once

#include <iostream>

#include <grpc++/grpc++.h>

#include "analyzer_service.h"
#include "inputs_count_model.h"

#include "AnalyzerService.grpc.pb.h"


namespace cfa {

class InputsCountAnalyzer final : public AnalyzerService {
private:
  grpc::Status analyzeImpl(const AnalyzerInput& input, AnalyzerOutput& output) override {
    std::cout << "start  InputsCountAnalyzer::analyzeImpl " << input.id() << std::endl;
    auto result = inputs_count_model_.updateAndAnalyze(input);
    if (result.success_) {
      auto add_ptr = output.add_categories();
      add_ptr->set_name("Inputs Count");
      add_ptr->set_score(result.score_);
      add_ptr->set_normed_score(result.normed_score_);
    }
    std::cout << "finish InputsCountAnalyzer::analyzeImpl " << input.id() << std::endl;
    return grpc::Status::OK;
  }

  InputsCountModel inputs_count_model_;
};

} // namespace cfa