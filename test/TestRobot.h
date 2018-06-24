#ifndef TESTROBOT_H
#define TESTROBOT_H

#include "../map/Map.h"
#include "../camera/Camera.h"
#include "../robot/Robot.h"

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

void testBuildMap() {
    Robot* robot = new Robot();
    Robot->buildMap();
}

#endif // TESTROBOT_H
