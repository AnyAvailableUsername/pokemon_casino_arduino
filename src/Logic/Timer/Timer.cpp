#include "Timer.h"

unsigned long Timer::passedTime() {
    return millis() - lastFrameTime;
}

void Timer::update() {
    lastFrameTime = millis();
}