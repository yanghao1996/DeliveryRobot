#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H

#include "Serial.h"
#include <string>
using namespace std;

/* struct Command stores the commands sent to motor,
 * there are 2 modes, rotate and driving straight.
 * for rotate, angle can be (-)60 or (-)90,
 * for straight, distance ranges from 1(dm) to 100(dm) (integer)
 * */
struct Command {
    bool isRotate;
    int rotateAngle;
    unsigned int distance; 
};

class RobotController {
private:
    Serial* serial;
    struct Command motorCommand;
public:
    RobotController();
    ~RobotController();
    // set command to rotate mode
    void setRotate(int angle); 
    // set command to straight mode
    void setStraight(unsigned int distance);

    /* compile motorCommand into sequence
     * for rotate, 3 chars are used, e.g. 000
     * - 1st: 0 for rotate, 1 for straight
     * - 2nd: 0 for anticlockwise, 1 for  clockwise
     * - 3rd: angle value, 0 for 60, 1 for 90
     * 
     * for straight 2 chars are used, e.g. 100
     * - 1st: 0 for rotate, 1 for straight
     * - 2nd, 3rd: distance in hex, ranges from 1 to (F)16 
     */
    string compile();
    // send compiled command to serial
    void sendCommand(const char* command);
    // read message from serial
    void readMessage(char* readBuffer);
};

// convert single int value(0 to 15) to char
char intToHexStr(int num);
#endif // ROBOTCONTROLLER_H
