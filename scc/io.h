//
// Created by Colin.Wang on 2022/2/18.
//

#ifndef SCC_SCC_IO_H_
#define SCC_SCC_IO_H_

#include <string>
#include <string_view>

namespace scc {
  std::string read_file_string(std::string_view filename);
}

#endif //SCC_SCC_IO_H_
