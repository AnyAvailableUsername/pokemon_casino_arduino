#pragma once
#include <Arduino.h>

class Timer {
private:
    unsigned long lastFrameTime = 0;

public:
    unsigned long passedTime();
    void update();

};