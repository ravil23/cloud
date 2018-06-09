#pragma once

#include <glog/logging.h>
#include <grpc++/grpc++.h>

#include "AnalyzerService.grpc.pb.h"


namespace cloud {

class AnalyzerService : public pb::Analyzer::Service {
public:
  grpc::Status analyze(grpc::ServerContext* context
    , const pb::AnalyzerInput* input_ptr
    , pb::AnalyzerOutput* output_ptr) override final {
    if (not input_ptr or not output_ptr) {
      return grpc::Status::CANCELLED;
    }

    DLOG(INFO) << "start  AnalyzerService::analyze " << input_ptr->id();
    auto status = analyzeImpl(*input_ptr, *output_ptr);
    DLOG(INFO) << "finish AnalyzerService::analyze " << input_ptr->id();

    return status;    
  }

private:
  virtual grpc::Status analyzeImpl(const pb::AnalyzerInput& input
    , pb::AnalyzerOutput& output) = 0;
};

} // namespace cloud