
#ifndef ROBOT_H
#define ROBOT_H

#include "../robot_control/RobotController.h"
#include "../camera/Camera.h"
#include "../map/Map.h"




class Robot {
private:
    RobotController* robotController;
    Camera* camera;
    Map* worldMap;
public:
    Robot();
    ~Robot();
    void buildMap();
};

#endif // ROBOT_H