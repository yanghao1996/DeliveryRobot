#ifndef TESTROBOTCONTROLLER_H
#define TESTROBOTCONTROLLER_H

#include "../robot_control/RobotController.h"
#include <stdio.h>
#include <unistd.h>


void testRobotController() {
    RobotController* robotController = new RobotController();
	char* readBuffer = new char[40];
	
    // test rotate command
    robotController->setRotate(60);
    string rotateCmd = robotController->compile();
    printf("%s\n", rotateCmd.c_str());
    
    for(int i=0; i<12; ++i) {
        robotController->sendCommand(rotateCmd.c_str());
	sleep(5);
    }
    
    //robotController->readMessage(readBuffer);
    //printf("%s\n", readBuffer);
    
    /**
    // test straight command
    robotController->setStraight(20);
    string straightCmd = robotController->compile();
    robotController->sendCommand(straightCmd.c_str());
    robotController->readMessage(readBuffer);

    printf("%s\n", readBuffer);
    **/
    
}

#endif // TESTROBOTCONTROLLER_H
