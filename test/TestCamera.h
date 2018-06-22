#ifndef TESTCAMERA_H
#define TESTCAMERA_H

#include "../map/Map.h"
#include "../camera/Camera.h"
#include <iostream>
using namespace std;

void testCamera() {
    Camera* camera = new Camera();
    camera->start();
    camera->flash();

    for (int i=-40; i<=40; i+=10) {
        cout << "angle: " << i << ": " << camera->getDistanceByAngle(i) << "m" << endl;
    }

    camera->stop();
}

#endif // TESTCAMERA_H