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
    posX = constrain(posX, 0, 128-1);
    posY = constrain(posY, 0, 32-1);
}

float Accelerator::positionX() {
    return posX;
}

float Accelerator::positionY() {
    return posY;
}