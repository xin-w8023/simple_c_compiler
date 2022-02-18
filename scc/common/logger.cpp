//
// Created by Colin.Wang on 2022/2/18.
//

#include "logger.h"

using namespace scc;

void Logger::info(std::string_view msg) {
  if (log_level_ > LOG_LEVEL::DEBUG) {
    printf("[INFO] [%s]\n", msg.data());
  }
}

Logger& Logger::logger(LOG_LEVEL log_level) {
  static Logger log(log_level);
  return log;
}