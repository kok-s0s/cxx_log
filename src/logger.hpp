#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace klog {

class Logger {
public:
  enum LogLevel { INFO, WARNING, ERROR };

  static Logger &getInstance(const std::string &filename) {
    static Logger instance(filename);
    return instance;
  }

  template <typename T> Logger &operator<<(const T &value) {
    log(value);
    return *this;
  }

  void log(const std::string &message, LogLevel level = INFO) {
    if (log_file_.is_open()) {
      auto now = std::chrono::system_clock::now();
      std::time_t now_c = std::chrono::system_clock::to_time_t(now);
      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                    now.time_since_epoch()) %
                1000;

      std::tm *timeInfo = std::localtime(&now_c);

      // ANSI escape codes for text color
      const char *colorCode = getColorCode(level);

      // Output log to file
      log_file_ << "[" << std::put_time(timeInfo, "%Y-%m-%d %X") << "."
                << std::setw(3) << std::setfill('0') << ms.count() << "] "
                << getLogLevelString(level) << ": " << message << std::endl;

      // Output colored log to console
      std::cout << "[" << std::put_time(timeInfo, "%Y-%m-%d %X") << "."
                << std::setw(3) << std::setfill('0') << ms.count() << "] "
                << colorCode << getLogLevelString(level) << ": " << message
                << "\033[0m" << std::endl;
    } else {
      std::cerr << "Log file is not open." << std::endl;
    }
  }

private:
  Logger(const std::string &filename) {
    log_file_.open(filename, std::ios::app);
    if (!log_file_.is_open()) {
      std::cerr << "Error opening file: " << filename << std::endl;
    }
  }

  ~Logger() {
    if (log_file_.is_open()) {
      log_file_.close();
    }
  }

  std::ofstream log_file_;

  const char *getColorCode(LogLevel level) const {
    switch (level) {
    case INFO:
      return "\033[1;32m"; // Green
    case WARNING:
      return "\033[1;33m"; // Yellow
    case ERROR:
      return "\033[1;31m"; // Red
    default:
      return "\033[0m"; // Default color (reset)
    }
  }

  const char *getLogLevelString(LogLevel level) const {
    switch (level) {
    case INFO:
      return "INFO";
    case WARNING:
      return "WARNING";
    case ERROR:
      return "ERROR";
    default:
      return "";
    }
  }
};

} // namespace klog
