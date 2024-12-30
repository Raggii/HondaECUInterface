#include <cstdio>
#include "logging.h++"
#include "serial.h++"

int main()
{
    Logger::getInstance().setLoggingLevel(3);
    Logger::getInstance().testFunction();

    return 0;
}



