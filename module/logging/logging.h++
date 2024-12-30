#ifndef LOGGING_H
#define LOGGING_H

#include <string>

#define RED "\033[0;31m"
#define GRN "\033[0;32m"
#define YEL "\033[0;33m"
#define BLU "\033[0;34m"
#define MAG "\033[0;35m"
#define CYN "\033[0;36m"
#define END "\033[0m"

#define ERROR "\033[1;31m[ERROR]: \033[0m"
#define WARNING "\033[1;33m[WARNING]: \033[0m"
#define SUCCESS "\033[1;32m[SUCCESS]: \033[0m"
#define INFO "\033[1;34m[INFO]: \033[0m"

// Macros for simplified logging
#define LOG_ERROR(msg) Logger::getInstance().errorMessage(msg)
#define LOG_WARNING(msg) Logger::getInstance().warningMessage(msg)
#define LOG_INFO(msg) Logger::getInstance().infoMessage(msg)
#define LOG_RAINBOW(msg) Logger::getInstance().rainbowMessage(msg)

class Logger {
public:
    static Logger &getInstance();

    void setLoggingLevel(int level);
    void errorMessage(const std::string &message);
    void warningMessage(const std::string &message);
    void infoMessage(const std::string &message);
    void rainbowMessage(const std::string &message);
    void testFunction();

private:
    Logger() = default; // Private constructor for singleton
    void printMessage(const std::string &message, int level);

    int loggingLevel = 1; // Default logging level
};

#endif // LOGGING_H
