#include "Accelerator.h"

void Accelerator::update(
    float accelerationX,
    float accelerationY,
    int passedTimeMs
) {
    accX = accelerationX / mass;
    accY = accelerationY / mass;
    velX += accX * passedTimeMs;
    velY += accY * passedTimeMs;
    velX /= friction;
    velY /= friction;
    posX += velX * passedTimeMs;
    posY += velY * passedTimeMs;
}

float Accelerator::positionX() {
    return posX;
}

float Accelerator::positionY() {
    return posY;
}