#include "unique_inputs_counter.h"


namespace cloud {

UniqueInputsCounter::Result UniqueInputsCounter::updateAndAnalyze(
  const pb::AnalyzerInput& input) {
  Result result;
  if (identifiers_.find(input.id()) == identifiers_.end()) {
    identifiers_.insert(input.id());
    result.new_input_ = true;
  }
  result.unique_count_ = identifiers_.size();
  return result;
}

} // namespace cloud