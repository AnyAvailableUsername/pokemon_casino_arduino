#pragma once
#include <Arduino.h>

class Accelerator {
private:
    float posX = 0;
    float posY = 0;
    float velX = 0;
    float velY = 0;
    float accX = 0;
    float accY = 0;
    float mass = 50000;
    float friction = 1.1;

public:
    void update(
        float accelerationX,
        float accelerationY,
        int passedTimeMs
    );

    float positionX();
    float positionY();

};