#ifndef TESTROBOT_H
#define TESTROBOT_H

#include "../map/Map.h"
#include "../camera/Camera.h"
#include "../robot/Robot.h"
#include <iostream>
using namespace std;

void testBuildMapWithoutRotate() {
    Map* worldMap = new Map();
    Camera* camera = new Camera();
    camera->start();
    camera->waitForDepthFrame();

    double distance = 0;
    int x, y = 0;
    for (int i=-40; i<=40; i+=1) {
        distance = camera->getDistanceByAngle(i);
        //Logger::info(to_string(distance));
        if (distance > 0) {
            x = distance * cos(i * pi / 180) * 10;
            y = distance * sin(i * pi / 180) * 10;

            worldMap->insertPoint(pair<int, int>(x, y));
        }
    }
    worldMap->savePGM();
    camera->stop();
}

void testBuildMapWithHumanforce() {
    Map* worldMap = new Map();
    Camera* camera = new Camera();
    RobotController* robotController = new RobotController();
    
	Logger::info("start building map");
	
    int facingAngle = 0;
    int angle = 0;
    double distance = 0;
    int xVal, yVal = 0;
    int cinVal = 0;
    
    // start camera
    camera->start();
    Logger::info("camera started");

    /* rotate 60 degree each time, and record the partial map,
     * it will rotate 6 times to finish a round trip */
    for(int i=0; i<6; ++i) {
    	camera->waitForDepthFrame();
        facingAngle = i * 60;
        for(int angleOffset=-40; angleOffset<=40; angleOffset++) {
        
            angle = facingAngle + angleOffset;
            distance = camera->getDistanceByAngle(angleOffset);

            //cout<<distance<<endl;
            xVal = distance * cos(angle * pi / 180) * 10;
            yVal = distance * sin(angle * pi / 180) * 10;

            // insert current point to worldMap
            cout<< xVal << "," << yVal<<endl;
            worldMap->insertPoint(pair<int, int>(yVal, xVal));
        }
        Logger::info("map for angle " + to_string(i*60) + " is built");
        
        // use cin to block the program
        worldMap->savePGM();	
        cin >> cinVal;   
    }

    worldMap->savePGM();	
}

void testBuildMap() {
    Robot* robot = new Robot();
    robot->buildMap();
}

#endif // TESTROBOT_H
