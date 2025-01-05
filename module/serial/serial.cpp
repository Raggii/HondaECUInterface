#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string>
#include <vector>
#include "logging.hpp"
#include "serial.hpp"

Serial::Serial(const std::string& port, unsigned int baud) : serialPort(-1), portName(port), baudRate(baud) {}

Serial::~Serial() {
    closePort();
}

void Serial::setBaudRate(unsigned int baud) {
    baudRate = baud;
}

bool Serial::configurePort() {
    struct termios tty;

    if (tcgetattr(serialPort, &tty) != 0) {
        LOG_ERROR("Unable to get terminal attributes!");
        return false;
    }

    cfsetispeed(&tty, baudRate);
    cfsetospeed(&tty, baudRate);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8 data bits
    tty.c_cflag |= (CLOCAL | CREAD);            // Enable receiver, ignore modem control lines
    tty.c_cflag &= ~(PARENB | PARODD);          // No parity
    tty.c_cflag &= ~CSTOPB;                     // 1 stop bit
    tty.c_cflag &= ~CRTSCTS;                    // Disable hardware flow control

    tty.c_lflag = 0;                            // Raw input mode
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);     // Disable software flow control
    tty.c_iflag &= ~(IGNCR | ICRNL | INLCR);    // Disable carriage return conversions
    tty.c_oflag = 0;                            // Raw output mode

    if (tcsetattr(serialPort, TCSANOW, &tty) != 0) {
        LOG_ERROR("Unable to set terminal attributes!");
        return false;
    }

    return true;
}

bool Serial::openPort() {
    serialPort = open(portName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (serialPort < 0) {
        LOG_ERROR("Unable to open port " + portName + "!");
        return false;
    }

    return configurePort();
}

void Serial::closePort() {
    if (serialPort >= 0) {
        close(serialPort);
        serialPort = -1;
        LOG_INFO("Serial port closed successfully.");
    }
}

std::string Serial::readData(size_t bufferSize) {
    if (serialPort < 0) {
        LOG_ERROR("Port not open!");
        return "";
    }

    std::vector<char> buffer(bufferSize + 1, '\0'); // Dynamically sized buffer initialized to '\0'

    int bytesRead = read(serialPort, buffer.data(), bufferSize);
    if (bytesRead < 0) {
        LOG_ERROR("Failed to read from port!");
        return "";
    }

    LOG_INFO("Data read from port.");
    return std::string(buffer.begin(), buffer.begin() + bytesRead);
}
