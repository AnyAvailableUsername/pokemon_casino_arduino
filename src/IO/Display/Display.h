#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

#include "../../Logic/SlotMachine/Symbol/Symbol.h"
#include "../../Logic/SlotMachine/Wheel/Wheel.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

class Display {
public:
  Display();

  bool begin();
  void clear();
  void print(const String &msg, int size, int x, int y);
  void point(int x, int y);
  void present();
  void firstPage();
  bool nextPage();

  void draw(Symbol& Symbol, int atX, int atY);
  void draw(Wheel& wheel, int atX, int atY);

private:
  U8G2_SH1107_PIMORONI_128X128_2_HW_I2C _display;

  static const char* const U8G_FONT_SIZES[4];
};