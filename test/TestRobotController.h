#ifndef TESTROBOTCONTROLLER_H
#define TESTROBOTCONTROLLER_H

#include "../robot_control/RobotController.h"
#include <stdio.h>

void testRobotController() {
    RobotController* robotController = new RobotController();
    char* writeBuffer = "hello";
    char* readBuffer  = new char[40];

    // test rotate command
    robotController->setRotate(60);
    const char* rotateCmd = robotController->compile();
    robotController->sendCommand(rotateCmd);
    robotController->readMessage(readBuffer);

    printf("%s\n", readBuffer);

    // test straight command
    robotController->setStraight(20);
    const char* straightCmd = robotController->compile();
    robotController->sendCommand(straightCmd);
    robotController->readMessage(readBuffer);

    printf("%s\n", readBuffer);
}

#endif // TESTROBOTCONTROLLER_H