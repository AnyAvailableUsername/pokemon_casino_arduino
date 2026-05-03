#include "Wheel.h"

Wheel::Wheel(Symbol *symbols, int size) {
    this->symbols = symbols;
    this->symbolsSize = size;
}

void Wheel::spin(unsigned long timePassedMs) {
    spinningTimeMs += timePassedMs;
}

void Wheel::start() {
    spinningTimeMs = 0;
}

float Wheel::wheelPosition() {
    float symbolsPassed = spinningTimeMs / 1000 * symbolsPerSecond;
    int floored = int(symbolsPassed);
    int index = floored % symbolsSize;
    return symbolsPassed - floored + index;
}