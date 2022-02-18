//
// Created by Colin.Wang on 2022/2/14.
//

#include <iostream>

#include "scc/compiler.h"

using namespace scc;

int main(int argc, char* argv[]) {

  if (argc < 2) {
    std::cerr << "[SCC] ERROR => at least provide one source file." << std::endl;
    exit(42);
  }

  Compiler compiler(argv[1]);

  compiler.compile();


  return 0;
}