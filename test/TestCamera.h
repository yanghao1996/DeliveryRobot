#ifndef TESTCAMERA_H
#define TESTCAMERA_H

#include "../map/Map.h"
#include "../camera/Camera.h"
#include <iostream>
#include <unistd.h>
using namespace std;

void testCamera() {
    Camera* camera = new Camera();
    camera->start();
	
    for (int i=-40; i<=40; i+=5) {
        cout << "angle: " << i << ": " << camera->getDistanceByAngle(i) << "m" << endl;
    }
    
    camera->stop();
}

void testCamera2() {
	rs2::pipeline p;
	p.start();
	
    // Block program until frames arrive
    rs2::frameset frames = p.wait_for_frames(); 
    
    // Try to get a frame of a depth image
    rs2::depth_frame depth = frames.get_depth_frame(); 
    
    // Get the depth frame's dimensions
    float width = depth.get_width();
    float height = depth.get_height();
    
    for(int i=0; i<width; i+=5) {
    	Logger::info(to_string(depth.get_distance(i, height / 2)));
    }
    
    p.stop();
}
#endif // TESTCAMERA_H
