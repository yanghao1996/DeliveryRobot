/* store the data and operations
 * for the map built by Intel
 * Realsense depth camera */

#ifndef MAP_H
#define MAP_H

#include <map>
#include <string>
using namespace std;

/* The map is 201 * 201 (dm)
 * the origin point is set in the center
 *        ^ y
 * -200   |        200
 * -------|--------> x
 *        |
 *        | 
 */
class Map {
private:
    // store the obstacle points in the map
    map<pair<int, int>, bool> sparseMap;
public:
    // insert obstacle point
    void insertPoint(pair<int, int> point);

    // save map as .pgm format
    void savePGM(string filepath="./map.pgm");
};
#endif // MAP_H