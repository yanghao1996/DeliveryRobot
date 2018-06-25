/* store the data and operations
 * for the map built by Intel
 * Realsense depth camera */

#ifndef MAP_H
#define MAP_H

#include <set>
#include <string>
using namespace std;

/* The map is 201 * 201 (dm)
 * the origin point is set in the center
 *        ^ y
 * -100   |        100
 * -------|--------> x
 *        |
 *        |
 */

static const int mapSize = 200;

typedef struct MapPoint {
  int x;
  int y;
} Point;

bool operator<(const Point& lhs, const Point& rhs);
bool operator==(const Point& lhs, const Point& rhs);


class Map {
private:
    // store the obstacle points in the set
    set<Point> sparseMap;
public:
    // insert obstacle point
    void insertPoint(const Point& point);

    // judge whether a point is in map range
    bool isInRange(const Point& point);

    // judge whether a point is obstacle
    bool isObstacle(const Point& point);

    // judge whether a point is valid
    // (in map range and not obstacle)
    bool isValid(const Point& point);

    // save map as .pgm format
    void savePGM(const string filepath="./map.pgm");
};
#endif // MAP_H