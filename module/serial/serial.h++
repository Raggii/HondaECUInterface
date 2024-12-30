#ifndef SERIAL_H
#define SERIAL_H

#include <string>
#include <vector>

class Serial {
public:
    Serial(const std::string& port, unsigned int baud);
    ~Serial();

    void setBaudRate(unsigned int baud);
    bool configurePort();
    bool openPort();
    void closePort();
    std::string readData(size_t bufferSize);

private:
    int serialPort;
    std::string portName;
    unsigned int baudRate;

    void resetPort();
};

#endif // SERIAL_H
