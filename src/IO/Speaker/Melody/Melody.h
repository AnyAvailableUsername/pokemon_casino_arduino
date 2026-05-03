#pragma once
#include <Arduino.h>
#include "../Note/Note.h"

class Melody {
private:
    const Note* content;
    int currentIndex=0;
    int size;
    unsigned long pauseTillNext=0;

public:
    Melody(const Note* melody, int size);
    Note next();
    bool isPausing(unsigned long timePassedMs);

};