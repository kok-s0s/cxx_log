#include <ctime>
#include <fstream>
#include <iostream>

class Logger {
public:
  static Logger &getInstance(const std::string &filename) {
    static Logger instance(filename);
    return instance;
  }

  template <typename T> Logger &operator<<(const T &value) {
    if (logFile.is_open()) {
      logFile << value << std::endl;
    } else {
      std::cerr << "Log file is not open." << std::endl;
    }
    return *this;
  }

  void log(const std::string &message) {
    if (logFile.is_open()) {
      std::time_t now = std::time(0);
      std::tm *timeInfo = std::localtime(&now);

      logFile << "[" << std::put_time(timeInfo, "%Y-%m-%d %X") << "] "
              << message << std::endl;
    } else {
      std::cerr << "Log file is not open." << std::endl;
    }
  }

private:
  Logger(const std::string &filename) {
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
      std::cerr << "Error opening file: " << filename << std::endl;
    }
  }

  ~Logger() {
    if (logFile.is_open()) {
      logFile.close();
    }
  }

  std::ofstream logFile;
};

int main() {
  Logger &logger = Logger::getInstance("example.log");
  logger << "This is a sample log message using << operator.";

  return 0;
}
