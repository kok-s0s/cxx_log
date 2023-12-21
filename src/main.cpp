#include "logger.hpp"

int main() {
  klog::Logger &logger = klog::Logger::getInstance("example.log");
  logger << "This is a sample log message.";
  logger.log("This is an informational message.", klog::Logger::INFO);
  logger.log("This is a warning message.", klog::Logger::WARNING);
  logger.log("This is an error message.", klog::Logger::ERROR);

  return 0;
}
