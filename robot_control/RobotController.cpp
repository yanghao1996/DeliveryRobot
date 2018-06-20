#include "RobotController.h"

RobotController::RobotController() {
    this->serial = new Serial();
    this->serial->openPort("/dev/ttyUSB0");
}

RobotController::~RobotController() {
    this->serial->closePort();
}

void RobotController::sendCommand(const char* command) {
    this->serial->writePort(command);
}

void RobotController::readMessage(char* readBuffer) {
    this->serial->readPort(readBuffer);
}