#include "Robot.h"
#include "../log/Logger.h"
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
	Logger::info("start building map");
	
    int facingAngle = 0;
    int angle = 0;
    double distance = 0;
    int xVal, yVal = 0;
    
    // start camera
    camera->start();
    Logger::info("camera started");

    /* rotate 60 degree each time, and record the partial map,
     * it will rotate 6 times to finish a round trip */
    for(int i=0; i<6; ++i) {
    	this->camera->waitForDepthFrame();
        facingAngle = i * 60;
        for(int angleOffset=-40; angleOffset<=40; angleOffset += 5) {
            angle = facingAngle + angleOffset;
            distance = this->camera->getDistanceByAngle(angleOffset);
            xVal = distance * cos(angle);
            yVal = distance * sin(angle);

            // insert current point to worldMap
            this->worldMap->insertPoint(Point{yVal, xVal});
        }
        Logger::info("map for angle " + to_string(i*60) + " is built");
        
        // send rotate command to motor
        this->robotController->setRotate(60);
        string command = this->robotController->compile();
        this->robotController->sendCommand(command.c_str());
        
        Logger::info("command sent to motor: " + command);
        
        // sleep for 10 seconds
        sleep(10);
    }

    this->worldMap->savePGM();
}

typedef struct aStarPointStruct aStarPoint;

// struct object to represent point in A* search
typedef struct aStarPointStruct{
  Point point;
  aStarPoint* father;
  int gScore;
  int hScore;
  int fScore; // F Score  = G Score + H Score
} AStarPoint;


bool compareFScore(AStarPoint* lhs, AStarPoint* rhs) {
    return lhs->fScore < rhs->fScore;
}


void Robot::aStarSearch(Point startPoint, Point endPoint) {
    list<Point> pathList;

    cout << "(" << startPoint.x <<", " << startPoint.y << ")"
         << "->"
         << "(" << endPoint.x <<", " << endPoint.y << ")" << endl;

    // the 2 lists are used to store points
    list<aStarPoint*> openList;
    list<aStarPoint*> closeList;

    // the 2 sets are used to check whether
    // a point is in the list in a faster way
    set<Point> openSet;
    set<Point> closeSet;

    // 4 directions
    int directions[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};

    // start point
    AStarPoint* start = new AStarPoint{startPoint, nullptr, 0, 0, 0};

    // push start point into Open List
    openList.push_back(start);
    openSet.insert(startPoint);

    // loop until Open List is empty or end point is found
    int x, y, gScore, hScore, fScore = 0;
    AStarPoint* aStarpoint = nullptr;
    AStarPoint* generatedAStarpoint = nullptr;
    bool endPointReached = false;

    while (!openList.empty()) {
        // sort Open List by F Score in ascending order,
        // we only fetch the front element (with minimum
        // F Score) each iteration
        openList.sort(compareFScore);

        // fetch the front element from Open List,
        // and push it into Close List
        aStarpoint = openList.front();
        openList.pop_front();
        openSet.erase(aStarpoint->point);
        closeList.push_back(aStarpoint);
        closeSet.insert(aStarpoint->point);

        // for the fetched point, traverse all its 4 directions
        for (int i=0; i<4; ++i) {
            x = aStarpoint->point.x + directions[i][0];
            y = aStarpoint->point.y + directions[i][1];

            cout << "evaluating: " << "(" << x <<", " << y << ")" << endl;

            // abandon it, if the new point is not
            // valid, or it's already in Close List
            if (!worldMap->isValid(Point{x, y}) || closeSet.find(Point{x, y})!=closeSet.end()) {
                cout << "(" << x <<", " << y << ")" << "is abandoned" <<endl;
                continue;
            }

            // else, accept it as new point

            // compute scores
            gScore = aStarpoint->gScore + 1;
            hScore = abs(endPoint.x - x) + abs(endPoint.y - y);
            fScore = gScore + hScore;

            // generate a new A* point
            generatedAStarpoint = new AStarPoint{Point{x, y}, aStarpoint,
                                                 gScore, hScore, fScore};

            // if end point is reached
            if (Point{x, y} == endPoint) {
                endPointReached = true;
                break;
            }

            // push the new point into Open List and Open Set
            openList.push_back(generatedAStarpoint);
            openSet.insert(generatedAStarpoint->point);
        }
        if (endPointReached) {
            break;
        }
    }

    if (endPointReached) {
        while (generatedAStarpoint != nullptr) {
            pathList.push_back(generatedAStarpoint);
            cout << "(" << generatedAStarpoint->point.x << ", "
                 << generatedAStarpoint->point.y << ") <- ";
            generatedAStarpoint = generatedAStarpoint->father;
        }
    }
    else {
        cout << "path not found" << endl;
    }
    return pathList;
}