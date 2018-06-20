#ifndef TESTROBOTCONTROLLER_H
#define TESTROBOTCONTROLLER_H

#include "../robot_control/RobotController.h"
#include <stdio.h>

void testRobotController() {
    RobotController* robotController = new RobotController();
    char* writeBuffer = "hello";
    char* readBuffer  = new char[40];

    robotController.writePort(writeBuffer);

    robotController.readPort(readBuffer);

    printf("%s", readBuffer);

    robotController.closePort();
}

#endif // TESTROBOTCONTROLLER_H