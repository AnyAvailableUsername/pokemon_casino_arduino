#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "../../Logic/Symbol.h"
#include "../../Logic/Wheel.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_ADDR 0x3C

class Display {
public:
  Display();

  // initializes Wire + SSD1306; returns false if failed
  bool begin();

  // print a message; clear==true starts a fresh 4-line buffer
  void say(const String &msg, bool clear = false, int textSize=1, int h_offset=0);
  void clear();
  void printAt(const String &msg, int textSize, int v_offset, int h_offset);
  void point(int x, int y);
  void draw(Symbol& Symbol);
  void draw(Wheel& wheel);

private:
  Adafruit_SSD1306 _display;
  String _lines[4];
  int _n;
};
