#include "Joystick.h"

// Constructor
Joystick::Joystick(int vrxPin, int vryPin, int swPin)
    : VRxPin(vrxPin), VRyPin(vryPin), SWPin(swPin) {}

// Initialize joystick
void Joystick::begin() {
    pinMode(VRxPin, INPUT);
    pinMode(VRyPin, INPUT);
    pinMode(SWPin, INPUT_PULLUP); // Use pull-up resistor for the button
}

float Joystick::normalize(int readValue) {
    int centered = readValue - 512;
    int antiDrift = 16;
    int sign = centered >= 0 ? 1 : -1;
    centered = sign * centered > antiDrift ? centered - sign * antiDrift: 0;
    return (centered) / (512.0 - antiDrift);
}

// Read joystick X-axis value
float Joystick::readX() {
    return normalize(analogRead(VRxPin));
}

// Read joystick Y-axis value
float Joystick::readY() {
    return normalize(analogRead(VRyPin));
}

// Read joystick button state
bool Joystick::isButtonPressed() {
    return digitalRead(SWPin) == LOW; // Button pressed is LOW
}

// Debug output
void Joystick::print() {
    float x = readX();
    float y = readY();
    bool buttonPressed = isButtonPressed();

    // Debug output
    Serial.print("Joystick X: ");
    Serial.print(x);
    Serial.print(" Y: ");
    Serial.print(y);
    Serial.print(" Button: ");
    Serial.println(buttonPressed ? "Pressed" : "Released");
}