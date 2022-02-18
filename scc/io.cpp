//
// Created by Colin.Wang on 2022/2/18.
//

#include <fstream>

#include "io.h"

namespace scc {

std::string read_file_string(std::string_view filename) {
  std::string ret;
  std::ifstream fin(filename, std::ios::ate);
  auto size = fin.tellg();
  fin.seekg(0);
  ret.resize(size, 0);
  fin.read(ret.data(), size);
  return ret;
}

}
