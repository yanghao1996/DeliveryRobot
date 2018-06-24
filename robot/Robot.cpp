#include "Robot.h"
#include <math.h>
#include <unistd.h>

Robot::Robot() {
    this->robotController = new RobotController();
    this->camera = new Camera();
    this->worldMap = new Map();
}

Robot::~Robot() {
    delete this->robotController;
    delete this->camera;
    delete this->worldMap;
}

void Robot::buildMap() {
    int facingAngle = 0;
    int angle = 0;
    double distance = 0;
    int xVal, yVal = 0;

    /* rotate 60 degree each time, and record the partial map,
     * it will rotate 6 times to finish a round trip */
    for(int i=0; i<6; ++i) {
        facingAngle = i * 60;
        for(int angleOffset=-40; angleOffset<=40; angleOffset += 5) {
            angle = facingAngle + angleOffset;
            distance = this->camera->getDistanceByAngle(angleOffset);
            xVal = distance * cos(angle);
            yVal = distance * sin(angle);

            // insert current point to worldMap
            this->worldMap->insertPoint(pair<int, int>(xVal, yVal));
        }
        // send rotate command to motor
        this->robotController->setRotate(60);
        string command = this->robotController->compile();
        this->robotController->sendCommand(command.c_str());
        
        // sleep for 3 seconds
        sleep(5);
    }

    this->worldMap->savePGM();
}