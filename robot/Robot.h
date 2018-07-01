
#ifndef ROBOT_H
#define ROBOT_H

#include "../robot_control/RobotController.h"
#include "../camera/Camera.h"
#include "../map/Map.h"
#include <list>

class Robot {
private:
    RobotController* robotController;
    Camera* camera;
    Map* worldMap;
public:
    Robot();
    ~Robot();
    void buildMap();
    list<Point> aStarSearch(Point startPoint, Point endPoint);
};

#endif // ROBOT_H