#include "Melody.h"

Melody::Melody(const Note* melody, int size) {
    content = melody;
    size = size;
}

Note Melody::next() {
    currentIndex = (currentIndex + 1) % size;
    return content[currentIndex];
}