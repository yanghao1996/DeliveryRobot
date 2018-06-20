#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H

#include "Serial.h"

class RobotController {
private:
    Serial* serial;
public:
    RobotController();
    ~RobotController();
    void sendCommand(const char* command);
    void readMessage(char* readBuffer);
};

#endif // ROBOTCONTROLLER_H
