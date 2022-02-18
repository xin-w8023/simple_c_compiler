//
// Created by Colin.Wang on 2022/2/18.
//

#ifndef SCC_SCC_COMMON_LOGGER_H_
#define SCC_SCC_COMMON_LOGGER_H_

#include <chrono>
#include <string_view>

namespace scc {

enum class LOG_LEVEL {
  DEBUG,
  INFO,
  ERROR
};

class Logger {
 public:

  explicit Logger(LOG_LEVEL log_level) : log_level_(log_level) {

  }

  void info(std::string_view msg);

  static Logger& logger(LOG_LEVEL log_level);

 private:
  LOG_LEVEL log_level_{};
};

}

#endif //SCC_SCC_COMMON_LOGGER_H_
