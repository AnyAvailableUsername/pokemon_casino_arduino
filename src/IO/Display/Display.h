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

  // initializes Wire + u8g2; returns false if failed
  bool begin();

  // print a message; clear==true starts a fresh 4-line buffer
  void say(const String &msg, bool clear = false, int textSize=1, int h_offset=0);
  void clear();
  void printAt(const String &msg, int textSize, int v_offset, int h_offset);
  void point(int x, int y);
  void draw(Symbol& Symbol, int atX, int atY);
  void draw(Wheel& wheel, int atX, int atY);

private:
  U8G2_SH1107_128X128_1_HW_I2C _display;  // u8g2 driver
  String _lines[4];
  int _n;

  void u8g_println(const String& str, int size);     // helper to approximate Adafruit textSize
  void u8g_print(const String& str, int size);       // helper
};