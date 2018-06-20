#ifndef TESTROBOTCONTROLLER_H
#define TESTROBOTCONTROLLER_H

#include "../robot_control/RobotController.h"
#include <stdio.h>

void testRobotController() {
    RobotController* robotController = new RobotController();
    char* writeBuffer = "hello";
    char* readBuffer  = new char[40];

    robotController->sendCommand(writeBuffer);

    robotController->readMessage(readBuffer);

    printf("%s\n", readBuffer);
}

#endif // TESTROBOTCONTROLLER_H