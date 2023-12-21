#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

class Logger {
public:
  static Logger &getInstance(const std::string &filename) {
    static Logger instance(filename);
    return instance;
  }

  template <typename T> Logger &operator<<(const T &value) {
    if (log_file_.is_open()) {
      log_file_ << value << std::endl;
    } else {
      std::cerr << "Log file is not open." << std::endl;
    }
    return *this;
  }

  void log(const std::string &message) {
    if (log_file_.is_open()) {
      std::time_t now = std::time(0);
      std::tm *timeInfo = std::localtime(&now);

      log_file_ << "[" << std::put_time(timeInfo, "%Y-%m-%d %X") << "] "
                << message << std::endl;
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
};
