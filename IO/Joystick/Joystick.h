#pragma once
#include <Arduino.h>

class Joystick {
private:
    int VRxPin; // Analog pin for VRx
    int VRyPin; // Analog pin for VRy
    int SWPin;  // Digital pin for SW (button)

    float normalize(int readValue);
public:
    // Constructor
    Joystick(int vrxPin, int vryPin, int swPin);

    void begin();
    float readX();
    float readY();
    bool isButtonPressed();
    void print();

    /* todo
    int isPressHorizontal(); -1 if left 1 if right 0 if not with state reset on calling this function until the joystick is back in this position

    
    */
};