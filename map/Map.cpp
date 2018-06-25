#include "Map.h"
#include <fstream>
#include <vector>
using namespace std;

bool operator<(const Point& lhs, const Point& rhs) {
    return (lhs.x < rhs.x) || ((!(rhs.x < lhs.x)) && (lhs.y < rhs.y));
}

bool operator==(const Point& lhs, const Point& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

void Map::insertPoint(const Point& point) {
    if (point.x >= -mapSize/2 && point.x <= mapSize/2 &&
            point.y >= -mapSize/2 && point.y <= mapSize/2) {
        this->sparseMap.insert(point);
    }
}

bool Map::isInRange(const Point& point) {
    return (point.x >= -mapSize/2 && point.x <= mapSize/2 &&
            point.y >= -mapSize/2 && point.y <= mapSize/2);
}

bool Map::isObstacle(const Point& point) {
    return this->sparseMap.find(point) != this->sparseMap.end();
}

bool Map::isValid(const Point& point) {
    if (!isInRange(point)) {
        return false;
    }
    else if (isObstacle(point)){
        return false;
    }
    else {
        return true;
    }
}

void Map::savePGM(string filepath) {
    fstream pgmFile;
    pgmFile.open(filepath, fstream::out);
    pgmFile << "P1" << endl
            << "201 201" << endl
            << "1" << endl;

    vector<vector<int> > denseMap(201, vector<int>(201, 0));
    for (auto iter = this->sparseMap.begin(); iter != this->sparseMap.end(); ++iter) {
        int xAxis = iter->x + 100;
        int yAxis = iter->y + 100;
        denseMap[xAxis][yAxis] = 1;
    }

    for (int i=0; i<denseMap.size(); ++i) {
        for (int j=0; j<denseMap[0].size(); ++j) {
            pgmFile << denseMap[i][j] << " ";
        }
        pgmFile << endl;
    }
    pgmFile.close();
}

