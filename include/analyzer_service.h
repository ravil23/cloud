#pragma once

#include <iostream>
#include <string>

#include <grpc++/grpc++.h>

#include "analyzer_service.grpc.pb.h"


namespace cfa {

class AnalyzerService : public Analyzer::Service {
public:
  grpc::Status analyze(grpc::ServerContext* context, const Fact* fact, Result* result) override final {
    std::cout << "start  AnalyzerService::analyze " << fact->id() << std::endl;
    auto status = analyzeImpl(context, fact, result);
    std::cout << "finish AnalyzerService::analyze " << fact->id() << std::endl;
    return status;
  }

private:
  virtual grpc::Status analyzeImpl(grpc::ServerContext* context, const Fact* fact, Result* result) = 0;
};

} // namespace cfa