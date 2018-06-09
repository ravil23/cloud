#include "server.h"
#include "service.h"


int main(int argc, char** argv) {
  cloud::Server<cloud::UniqueInputsCountAnalyzer> server;

  try {
    server.run();
  } catch (const std::exception& e) {
    LOG(FATAL) << e.what();
    return EXIT_FAILURE;
  } catch (...) {
    LOG(FATAL) << "unknown error";
    return EXIT_FAILURE;
  }
}