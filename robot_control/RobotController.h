#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H

#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */
#include <errno.h>  /* ERROR Number Definitions          */


class RobotController {
private:
    int fd; // for opening port
    struct termios SerialPortSettings;
public:
    void openPort(const char* port);
    void closePort();
    void writePort(char* writeBuffer);
    void readPort(char* readBuffer);
};

#endif // ROBOTCONTROLLER_H
