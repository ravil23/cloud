#pragma once

#include <string>
#include <unordered_set>

#include "AnalyzerService.pb.h"


namespace cloud {

class UniqueInputsCounter {
public:
  struct Result {
    bool new_input_ = false;
    size_t unique_count_ = 0u;
  };

  Result updateAndAnalyze(const pb::AnalyzerInput& input);

private:
  std::unordered_set<std::string> identifiers_;
};

} // namespace cloud