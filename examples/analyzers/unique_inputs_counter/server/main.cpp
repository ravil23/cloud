#include <string>

#include "server.h"
#include "service.h"


int main(int argc, char** argv) {
  const std::string usage(argv[0]);

  // Print help if requested
  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]) == "-h" or std::string(argv[i]) == "--help") {
      std::cerr << "Analyzer Server: Unique Inputs Counter" << std::endl
        << "Produced categories:" << std::endl
        << " - Unique Inputs Count" << std::endl
        << "Necessary environment variables:" << std::endl
        << " - SERVER_NAME" << std::endl
        << " - SERVER_PORT" << std::endl
        << "Usage:" << std::endl << usage << std::endl;;
      return EXIT_SUCCESS;
    }
  }

  // Validate arguments
  if (argc != 1) {
    std::cerr << usage << std::endl;
    return EXIT_FAILURE;
  }

  // Initialize server
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