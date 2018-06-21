#include "RobotController.h"
#include "../log/Logger.h"
#include <math.h>

RobotController::RobotController() {
    this->serial = new Serial();
    this->serial->openPort("/dev/ttyUSB0");
}

RobotController::~RobotController() {
    this->serial->closePort();
}

void RobotController::setRotate(int angle) {
    if (abs(angle) != 60 && abs(angle) != 90) {
        Logger::error("invalid angle value!");
        exit(1);
    }
    this->motorCommand.isRotate = true;
    this->motorCommand.rotateAngle = angle;
}

void RobotController::setStraight(unsigned int distance) {
    if (distance > 100) {
        Logger::error("invalid distance value!");
        exit(1);
    }
    this->motorCommand.isRotate = false;
    this->motorCommand.distance = distance;
    Logger::info("1" + to_string(this->motorCommand.distance));
} 

string RobotController::compile() {
    string compiledStr = "100";
    if (this->motorCommand.isRotate == false) {
        int secondNum = this->motorCommand.distance / 16;
        compiledStr[1] = intToHexStr(secondNum);
        int thirdNum = this->motorCommand.distance - 16 * secondNum;
        compiledStr[2] = intToHexStr(thirdNum);
    }
    else {
    	compiledStr[0] = '0';
        if(this->motorCommand.rotateAngle < 0) {
            compiledStr[1] = '1';
        }
        if(abs(this->motorCommand.rotateAngle) == 90) {
            compiledStr[2] = '1';
        }
    }

    return compiledStr;
}

void RobotController::sendCommand(const char* command) {
    this->serial->writePort(command);
}

void RobotController::readMessage(char* readBuffer) {
    this->serial->readPort(readBuffer);
}

char intToHexStr(int num) {
    if (num < 10) {
        return '0' + num;
    }
    else {
        return 'A' + num - 10;
    }
}
