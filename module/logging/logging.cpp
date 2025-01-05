#include "logging.hpp"
#include <cstdio>
#include <cstring>
#include <vector>

// Static method to get the single instance
Logger &Logger::getInstance() 
{
    static Logger instance;
    return instance;
}

void Logger::setLoggingLevel(int level) 
{
    if (level >= 0 && level <= 3) {
        loggingLevel = level;
    } else {
        printf("Invalid logging level: %d\n", level);
    }
}

void Logger::printMessage(const std::string &message, int level) 
{
    static const std::vector<std::string> messageList = {ERROR, WARNING, INFO, SUCCESS};
    if (level <= loggingLevel) {
        std::string fullMessage = messageList[level - 1] + message + "\n";
        printf("%s", fullMessage.c_str());
    }
}

void Logger::errorMessage(const std::string &message) 
{
    printMessage(message, 1);
}

void Logger::warningMessage(const std::string &message) 
{
    printMessage(message, 2);
}

void Logger::infoMessage(const std::string &message) 
{
    printMessage(message, 3);
}

void Logger::rainbowMessage(const std::string &message) 
{
    static const std::vector<std::string> colourList = {RED, YEL, GRN, CYN, BLU, MAG};
    if (loggingLevel == 3) {
        std::string buf;

        for (size_t i = 0; i < message.length(); ++i) {
            buf += colourList[i % colourList.size()];
            buf += message[i];
            buf += END;
        }

        printf("%s\n", buf.c_str());
    }
}

void Logger::testFunction() 
{
    errorMessage("This is a test error");
    warningMessage("This is a test warning");
    infoMessage("This is a test info");
    rainbowMessage("Hello World!");
}
