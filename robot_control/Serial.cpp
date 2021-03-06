
#include "Serial.h"
#include "../log/Logger.h"
#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */
#include <errno.h>  /* ERROR Number Definitions          */
#include <stdio.h>

void Serial::openPort(const char* port) {
	this->fd = 10000;
    this->fd = open(port, O_RDWR | O_NOCTTY);
    if (this->fd < 0) {
        Logger::error("Serial Port open failed!");
        //fprintf(stderr, "errno is %d\n", errno);
        exit(1);
    }
    else {
		Logger::info("Serial Port opened success!");
    }
    // bind fd with termios
    tcgetattr(fd, &(this->SerialPortSettings));

    // set Baudrate
    cfsetispeed(&(this->SerialPortSettings), B9600);
    cfsetospeed(&(this->SerialPortSettings), B9600);

    // configure data format, start/stop bits, parity
    this->SerialPortSettings.c_cflag &= ~PARENB; // no parity
    this->SerialPortSettings.c_cflag &= ~CSTOPB; // stop bits = 1
    this->SerialPortSettings.c_cflag &= ~CSIZE;  // clear the mask
    this->SerialPortSettings.c_cflag |= CS8;     // set data bits = 8

    // configure other options
    /* turn off hardware based flow control (RTS/CTS) */
    this->SerialPortSettings.c_cflag &= ~CRTSCTS;
    /* turn on the receiver of serial port(CREAD), otherwise cannot read from serial */
    this->SerialPortSettings.c_cflag |= CREAD | CLOCAL; 
    /* turn off software based on flow control (XON/XOFF) */
    this->SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
    /* set to NON Canonical mode */
    this->SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    // configure read options
    this->SerialPortSettings.c_cc[VMIN] = 10; // read 10 characters
    this->SerialPortSettings.c_cc[VTIME] = 0; // wait indefinitely

    // commit configurations
    tcsetattr(this->fd, TCSANOW, &(this->SerialPortSettings));
}

void Serial::closePort() {
    close(this->fd);
    Logger::info("Serial Port closed");
}

void Serial::writePort(const char* writeBuffer) {
    if (writeBuffer == nullptr) {
        Logger::error("write buffer null pointer error!");
        exit(0);
    }

    // system call write()
    int bytesWritten = 0;
    bytesWritten = write(this->fd, writeBuffer, sizeof(writeBuffer));
    Logger::info(to_string(bytesWritten) + " bytes written: " + string(writeBuffer));
}

void Serial::readPort(char* readBuffer) {
    if (readBuffer == nullptr) {
        Logger::error("read buffer null pointer error!");
        exit(0);
    }
    // TODO: check size of readBuffer is at least 32 

    // system call read()
    int bytesRead = 0;
    bytesRead = read(this->fd, readBuffer, 30);
    Logger::info(to_string(bytesRead) + " bytes read: " + string(readBuffer));
}
