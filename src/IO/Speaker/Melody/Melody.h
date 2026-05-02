#pragma once
#include <Arduino.h>
#include "../Note/Note.h"

class Melody {
private:
    const Note* content;
    int currentIndex=0;
    int size;

public:
    Melody(const Note* melody, int size);
    Note next();

};