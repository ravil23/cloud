#include "inputs_count_model.h"


namespace cfa {

InputsCountModel::Result InputsCountModel::updateAndAnalyze(const AnalyzerInput& input) {
  Result result;
  identifiers_.insert(input.id());
  result.success_ = true;
  result.score_ = identifiers_.size();
  result.normed_score_ = 1. - 1. / result.score_;
  return result;
}

} // namespace cfa