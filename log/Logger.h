// Logger log important informations
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <vector>
using namespace std;

enum LogLevel {
    ERROR,
    INFO
};

const vector<string> logStrMap{"ERROR", "INFO"};

class Logger {
public:
    static void info(string message) {
        Logger::printLog(INFO, message);
    }
    static void error(string message) {
        Logger::printLog(ERROR, message);
    }
private:
    static void printLog(LogLevel level, string message) {
        auto now = chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        cout << put_time(std::localtime(&now_c), "%c") 
             << " [" << logStrMap[level] << "]: " << message << endl;
    }
};


# endif //LOGGER_H