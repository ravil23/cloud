#pragma once

#include <iostream>
#include <string>

#include <grpc++/grpc++.h>

#include "AnalyzerService.grpc.pb.h"


namespace cfa {

class AnalyzerService : public Analyzer::Service {
public:
  grpc::Status analyze(grpc::ServerContext* context, const AnalyzerInput* input_ptr, AnalyzerOutput* output_ptr) override final {
    std::cout << "start  AnalyzerService::analyze " << input_ptr->id() << std::endl;
    auto status = analyzeImpl(*input_ptr, *output_ptr);
    std::cout << "finish AnalyzerService::analyze " << input_ptr->id() << std::endl;
    return status;
  }

private:
  virtual grpc::Status analyzeImpl(const AnalyzerInput& input, AnalyzerOutput& output) = 0;
};

} // namespace cfa