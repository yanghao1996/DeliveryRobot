cmake_minimum_required(VERSION 3.8)
project(DeliveryRobot)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp 
                 #camera/Camera.h camera/Camera.cpp
                 robot_control/RobotController.h robot_control/RobotController.cpp
                 log/Logger.h log/Logger.cpp 
                 #map/Map.h map/Map.cpp
                 #robot/Robot.h robot/Robot.cpp
                 test/TestRobotController.h
                 )
add_executable(DeliveryRobot ${SOURCE_FILES})


# # libraries for linux
# include_directories(
#     /usr/local/include
#     /home/horizon/桌面/librealsense/examples
#     /home/horizon/桌面/librealsense/third-party
# )

# link_directories(/usr/local/lib)

# find_library(
#     RS2
#     NAMES realsense2
# )

# find_library(
#     GLFW
#     NAMES glfw
# )

# set(EXTRA_LIBS ${RS2} ${GLFW})

# target_link_libraries(DeliveryRobot ${EXTRA_LIBS})