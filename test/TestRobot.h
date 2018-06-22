#ifndef CAMERA_H
#define CAMERA_H

#include "../map/Map.h"
#include "../camera/Camera.h"

void testBuildMapWithoutRotate() {
    Map* worldMap = new Map();
    Camera* camera = new Camera();

    double distance = 0;
    int x, y = 0;
    for (int i=-40; i<=40; i+=2) {
        distance = camera->getDistanceByAngle(i);
        if (distance > 0) {
            x = distance * cos(i * pi / 180) * 10;
            y = distance * sin(i * pi / 180) * 10;

            worldMap->insertPoint(pair<int, int>(x, y));
        }
    }
    worldMap->savePGM();
}

#endif // CAMERA_H