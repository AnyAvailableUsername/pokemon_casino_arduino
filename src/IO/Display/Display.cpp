#include "./Display.h"

const char* const Display::U8G_FONT_SIZES[4] = {
  u8g2_font_5x7_tr,
  u8g2_font_6x10_tr,
  u8g2_font_7x13_tr,
  u8g2_font_8x13_tr
};

Display::Display()
  : _display(U8G2_R0) {}

bool Display::begin() {
  Wire.begin();
  Wire.setClock(400000);

  _display.begin();

  _display.firstPage();
  do {
    _display.setFont(u8g2_font_6x10_tr);
    _display.drawStr(0, 12, "SH1107 OK");
  } while (_display.nextPage());

  return true;
}

void Display::clear() {
  _display.clearBuffer();
}

void Display::print(
  const String& str,
  int size,
  int x, int y
) {
  int fidx = constrain(size, 0, 3);
  const char* font = U8G_FONT_SIZES[fidx];

  _display.setFont(font);
  _display.drawStr(x, y, str.c_str());
}

void Display::point(int x, int y) {
  x = constrain(x, 0, SCREEN_WIDTH-1);
  y = constrain(y, 0, SCREEN_HEIGHT-1);

  _display.drawPixel(x, y);
}

void Display::present() {
  _display.sendBuffer();
}

void Display::firstPage() {
  _display.firstPage();
}

bool Display::nextPage() {
  return _display.nextPage();
}

void Display::draw(Symbol& symbol, int atX, int atY) {
  _display.drawXBM(
    atX, atY,
    symbol.width, symbol.height,
    symbol.bitmap
  );
}

void Display::draw(Wheel& wheel, int atX, int atY) {
  Symbol* symbols = wheel.symbols;
  float pos = wheel.wheelPosition();
  int index = int(pos);
  float offset = pos - index;

  for (int i=index-1; i < index+2; i++) {
    draw(symbols[i], atX, atY);
  }
}
