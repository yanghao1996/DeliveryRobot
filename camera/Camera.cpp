#include "Camera.h"
#include "../log/Logger.h"

double cos2sin(double cosVal) {
    return sqrt(1 - pow(cosVal, 2));
}

double Camera::getDistanceByAngle(int angle){
    if (angle < -40 || angle > 40) {
        Logger::error("Invalid angle value.");
        exit(1);
    }

    // Block program until frames arrive
    rs2::frameset frames = p.wait_for_frames(); 
    
    // Try to get a frame of a depth image
    rs2::depth_frame depth = frames.get_depth_frame(); 
    
    // Get the depth frame's dimensions
    float width = depth.get_width();
    float height = depth.get_height();

    int absAngle = abs(angle) * pi / radianConstant;

    double offset = sin(absAngle) / cos(absAngle) * 
                    width / 2 / tanHalfHoriAngle;
                    
    double xVal = 0;
    if (angle < 0) {
        xVal = width / 2 - offset;
    }
    else {
        xVal = width / 2 + offset;
    }

    return depth.get_distance(xVal, height / 2);
}


void Camera::start() {
    this->p.start();
    Logger::info("Camera stream start!");
}

void Camera::stop() {
    this->p.stop();
    Logger::info("Camera stream stop!");
}