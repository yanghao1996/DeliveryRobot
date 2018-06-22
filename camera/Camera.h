/* encapsulation of Intel Realsense Library
 * https://github.com/IntelRealSense/librealsense
 * only depth camera module is used
 */
#ifndef CAMERA_H
#define CAMERA_H

#include <librealsense2/rs.hpp>

static const double pi = 3.14159;
static const double radianConstant = 180.0;
static const double horizonalAngle = pi * 85.2 / radianConstant;

// given cos value, compute sin value
double cos2sin(double cosVal);

class Camera {
private:
    double outerLeftEdge;
    double outerRightEdge;
    double oppositeEdge;
    double midDistance;
    double cosLeftAngle;
    double cosRightAngle;
    double cosInnerLeftAngle;
    double midLeftDistance;
    // RealSense library
    rs2::pipeline p;
private:
public:
    // flash left, right edge distance and middle distance
    void flash();

    // angle ranges from -40 to 40
    double getDistanceByAngle(int angle);

    // start receiving frames
    void start();

    // stop receiving frames
    void stop();
};

#endif // CAMERA_H