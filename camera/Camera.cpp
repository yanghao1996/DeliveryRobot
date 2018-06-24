#include "Camera.h"
#include "../log/Logger.h"

double cos2sin(double cosVal) {
    return sqrt(1 - pow(cosVal, 2));
}



void Camera::waitForDepthFrame() {
    // Block program until frames arrive
	this->frames = this->p.wait_for_frames();
	// Try to get a frame of a depth image
    this->depth = new rs2::depth_frame(frames.get_depth_frame());
}


double Camera::getDistanceByAngle(int angle){
    if (angle < -40 || angle > 40) {
        Logger::error("Invalid angle value.");
        exit(1);
    } 
    
    // Get the depth frame's dimensions
    float width = depth->get_width();
    float height = depth->get_height();

    double absAngle = (double)abs(angle) * pi / radianConstant;
    double offset = sin(absAngle) / cos(absAngle) * 
                    width / 2 / tanHalfHoriAngle;
    
    double xVal = 0;
    if (angle < 0) {
        xVal = width / 2 - offset;
    }
    else {
        xVal = width / 2 + offset;
    }

    return depth->get_distance(xVal, height / 2);
}


void Camera::start() {
    this->p.start();
    Logger::info("Camera stream start!");
}

void Camera::stop() {
    this->p.stop();
    Logger::info("Camera stream stop!");
}
