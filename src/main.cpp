#include "logger.hpp"

#include <iostream>
#include <mutex>
#include <string>
#include <thread>

void ThreadFoo() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  KLOG << "thread foo";
}

void ThreadBar() {
  // Following code emulates slow initialization.
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  KLOG << "thread bar";
}

int main() {
  klog::Logger &logger = klog::Logger::getInstance("example.log");
  // logger << "This is a sample log message.";
  // logger.log("This is an informational message.", klog::Logger::INFO);
  // logger.log("This is a warning message.", klog::Logger::WARNING);
  // logger.log("This is an error message.", klog::Logger::ERROR);
  KLOG << "KLOG - This is a sample log message.";
  // KLOG << 4;

  std::thread t1(ThreadFoo);
  t1.join();
  std::thread t2(ThreadBar);
  t2.join();

  return 0;
}
