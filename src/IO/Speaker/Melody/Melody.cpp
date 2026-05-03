#include "Melody.h"

Melody::Melody(const Note* melody, int size) {
    content = melody;
    size = size;
}

Note Melody::next() {
    currentIndex = (currentIndex + 1) % size;
    pauseTillNext = content[currentIndex].duration;
    return content[currentIndex];
}

bool Melody::isPausing(unsigned long timePassedMs) {
    pauseTillNext -= timePassedMs;
    return pauseTillNext > 0;
}