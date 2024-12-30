#include <cstdio>
#include "logging/logging.h++"
// #include "serial.h++"

int main()
{
    Logger::getInstance().setLoggingLevel(1);
    Logger::getInstance().testFunction();
    Logger::getInstance().errorMessage("Testing Compilation");
    return 0;
}



