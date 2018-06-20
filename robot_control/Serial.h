/* This module communicates with wheel-control motor
 * through serial port, please refer to this article: 
 * http://xanthium.in/Serial-Port-Programming-on-Linux
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */
#include <errno.h>  /* ERROR Number Definitions          */


class Serial {
private:
    int fd; // for opening port
    struct termios SerialPortSettings;
public:
    void openPort(const char* port);
    void closePort();
    void writePort(const char* writeBuffer);
    void readPort(char* readBuffer);
};

#endif // SERIAL_H