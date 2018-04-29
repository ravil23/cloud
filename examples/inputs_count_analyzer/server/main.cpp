#include <iostream>

#include "server.h"
#include "service.h"


int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: <SERVER_BINARY> <PORT>" << std::endl;
    return EXIT_FAILURE;
  }

  cfa::Server<cfa::InputsCountAnalyzer> server(argv[1]);
  server.run();

  return EXIT_SUCCESS;
}