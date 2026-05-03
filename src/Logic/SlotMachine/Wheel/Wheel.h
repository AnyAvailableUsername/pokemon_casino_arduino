#include "../Symbol/Symbol.h"

class Wheel {
public:
    Symbol *symbols;
    int symbolsSize;
    float symbolsPerSecond = 2;
    unsigned long spinningTimeMs = 0;

    Wheel(Symbol *symbols, int size);
    void spin(unsigned long timePassedMs);
    float wheelPosition();
    void start();



};