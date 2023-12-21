#include "logger.hpp"

int main() {
  Logger &logger = Logger::getInstance("example.log");
  logger.log("This is a sample log message.");

  return 0;
}
