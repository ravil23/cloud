#pragma once

#include <string>
#include <unordered_set>

#include "AnalyzerService.pb.h"


namespace cloud {

/**
 * \brief Calculate unique inputs count.
 */
class UniqueInputsCounter {
public:
  struct Result {
    bool new_input_ = false;
    size_t unique_count_ = 0u;
  };

  /**
   * \brief Process new input.
   * \param[in]  input  Analyzer input.
   * \return  Analyzing result.
   */
  Result updateAndAnalyze(const pb::AnalyzerInput& input);

private:
  std::unordered_set<std::string> identifiers_;
};

} // namespace cloud