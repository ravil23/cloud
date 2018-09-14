#pragma once

#include <glog/logging.h>
#include <grpc++/grpc++.h>

#include "AnalyzerService.grpc.pb.h"


namespace cloud {

/**
 * \brief Virtual wrapper for grpc analyzer service.
 */
template <class TAnalyzer>
class AnalyzerService : public pb::Analyzer::Service {
public:
  /**
   * \brief Analyze input and produce output.
   * \param[out] context     Pointer to server context.
   * \param[in]  input_ptr   Pointer to input object.
   * \param[out] output_ptr  Pointer to output object.
   * \return  Analyzing status.
   */
  grpc::Status analyze(grpc::ServerContext* context
    , const pb::AnalyzerInput* input_ptr
    , pb::AnalyzerOutput* output_ptr) override final {
    if (not input_ptr or not output_ptr) {
      return grpc::Status::CANCELLED;
    }

    DLOG(INFO) << "start  AnalyzerService::analyze " << input_ptr->id();
    auto status = analyzer_.analyze(*input_ptr, *output_ptr);
    DLOG(INFO) << "finish AnalyzerService::analyze " << input_ptr->id();

    return status;    
  }

private:
  TAnalyzer analyzer_;
};

} // namespace cloud
