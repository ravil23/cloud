#pragma once

#include <iostream>

#include <grpc++/grpc++.h>

#include "analyzer_service.grpc.pb.h"

#include "analyzer_service.h"


namespace cfa {

class ExampleAnalyzer final : public AnalyzerService {
  grpc::Status analyzeImpl(grpc::ServerContext* context, const Fact* fact, Result* result) override {
    std::cout << "start  ExampleAnalyzer::analyzeImpl " << fact->id() << std::endl;
    std::cout << fact->id() << std::endl;
    std::cout << "finish ExampleAnalyzer::analyzeImpl " << fact->id() << std::endl;
    return grpc::Status::OK;
  }
};

} // namespace cfa