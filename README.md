# DeliveryRobot

## Build
mkdir ./cmake-build-debug && cd ./cmake-build-debug
cmake ..
make

## Project Structure
### arduino
Low-level motor control module based on Arduino.
The code should be flashed through serial port.

### camera
A simple wrapper for Realsense Library (librealsense),
where we only care about the depth camera.

### log
A simple logger module for recording and displaying events.

### map
Store the 2D map built with depth camera, as well as some
methods to operate the map.

### robot
An abstraction of delivery robot. It encapsulates all parts
of a robot (e.g. camera, motor controller and a map) and 
provide some macro methods to complete complex operations.

### robot_control
High-level motor control module. It is an interface connected 
with serial port, which is responsible for connecting serial 
port and sending commands through it.

### test
All test functions.