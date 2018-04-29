#pragma once

#include <string>
#include <unordered_set>

#include "AnalyzerService.pb.h"


namespace cfa {

class InputsCountModel {
public:
  struct Result {
    bool success_ = false;
    double score_ = 0.;
    double normed_score_ = 0.;
  };

  Result updateAndAnalyze(const AnalyzerInput& input);

private:
  std::unordered_set<std::string> identifiers_;
};

} // namespace cfa