#include "Camera.h"
#include "../log/Logger.h"
#include <math.h>

double cos2sin(double cosVal) {
    return sqrt(1 - pow(cosVal, 2));
}

double Camera::getDistanceByVal(int xVal) {
    // Block program until frames arrive
    rs2::frameset frames = p.wait_for_frames(); 
    
    // Try to get a frame of a depth image
    rs2::depth_frame depth = frames.get_depth_frame(); 
    
    // Get the depth frame's dimensions
    float width = depth.get_width();
    float height = depth.get_height();

    if (xVal == -1) {
        xVal = width - 1;
    }
    else if (xVal < 0 || xVal >=width) {
        Logger.error("Invalid camera coordinate: " + to_string(xVal));
        exit(0);
    }
    
    // Query the distance from the camera to the object in the center of the image
    double depthDistance = depth.get_distance(xVal, height / 2);

    return depthDistance;    
}

double Camera::getDistanceByRate(double rate) {
    // Block program until frames arrive
    rs2::frameset frames = p.wait_for_frames(); 
    
    // Try to get a frame of a depth image
    rs2::depth_frame depth = frames.get_depth_frame(); 
    
    // Get the depth frame's dimensions
    float width = depth.get_width();
    float height = depth.get_height();

    if (xVal < 0 || xVal >=1) {
        Logger.error("Invalid camera rate: " + to_string(rate));
        exit(0);
    }
    
    // Query the distance from the camera to the object in the center of the image
    double depthDistance = depth.get_distance(rate * width, height / 2);

    return depthDistance;
}

void Camera::flash() {
    // get outerLeftEdge, outerRightEdge
    this->outerLeftEdge = this->getDistanceByVal(0);
    this->outerRightEdge = this->getDistanceByVal(-1);

    // compute oppositeEdge
    this->oppositeEdge = sqrt(pow(this->outerLeftEdge, 2) + pow(this->outerRightEdge, 2)
                              - 2.0 * this->outerLeftEdge * this->outerRightEdge
                                    * cos(horizonalAngle));
    // compute cosLeftAngle
    this->cosLeftAngle = (pow(this->outerRightEdge, 2) + pow(this->oppositeEdge, 2)
                         - pow(this->outerLeftEdge, 2)) / 
                         (2 * this->outerRightEdge * this->oppositeEdge);
    
    // compute cosRightAngle
    this->cosRightAngle = (pow(this->outerLeftEdge, 2) + pow(this->oppositeEdge, 2)
                          - pow(this->outerRightEdge, 2)) / 
                          (2 * this->outerLeftEdge * this->oppositeEdge);

    // compute cosInnerLeftAngle
    this->cosInnerLeftAngle = - cos(horizonalAngle / 2) * this->cosLeftAngle +
                              sin(horizonalAngle / 2) * cos2sin(this->cosInnerLeftAngle);

    // compute midDistance
    this->midDistance = cos2sin(this->cosLeftAngle) * this->outerLeftEdge
                        / this->cosInnerLeftAngle;
    
    // compute midLeftDistance
    this->midLeftDistance =  this->outerLeftEdge * sin(horizonalAngle / 2) 
                             / cos2sin(this->cosInnerLeftAngle);
}

double Camera::getDistanceByAngle(int angle){
    if (angle < -40 || angle > 40) {
        Logger::error("Invalid angle value.");
        exit(1);
    }
    if (angle == 0) {
        return this->midDistance;
    }

    double cosLeftTheta = this->cosInnerLeftAngle;

    if (angle > 0) {
        cosLeftTheta *= -1;
    }

    angle = pi * abs(angle) / radianConstant;
    
    double sinTheta = 0;

    sinTheta = cos2sin(cosLeftTheta) * cos(angle) + 
               this->cosInnerLeftAngle * sin(angle);

    double distance = sin(angle) * this->midDistance / sinTheta;

    double rate = (this->midLeftDistance - distance) / this->oppositeEdge;
    
    return this->getDistanceByRate(rate);
}


void Camera::start() {
    this->p.start();
    Logger::info("Camera stream start!");
}

void Camera::stop() {
    this->p.stop();
    Logger::info("Camera stream stop!");
}