#include "./Display.h"

const char* const U8G_FONT_SIZES[4] = {
  u8g2_font_5x7_tr,   // textSize 1 ~ 5x7
  u8g2_font_6x10_tr,  // textSize 2 ~ 6x10
  u8g2_font_7x13_tr,  // textSize 3 ~ 7x13
  u8g2_font_8x13_tr   // textSize 4 ~ 8x13
};

const int U8G_FONT_HEIGHT[4] = {
  10,  // textSize 1 approx
  13,  // textSize 2 approx
  16,  // textSize 3 approx
  18   // textSize 4 approx
};

Display::Display()
  : _display(U8G2_R0),  // rotation 0; init is done in begin()
    _n(0) {}

bool Display::begin() {
  Wire.begin();
  Wire.setClock(100000);

  // init u8g2 (no explicit address for this constructor)
  _display.begin();

  // clear screen, setup
  _display.firstPage();
  do {
    _display.setFont(u8g2_font_6x10_tr);
    _display.drawStr(0, 12, "SH1107 OK");
  } while (_display.nextPage());

  _n = 0;
  return true;
}

void Display::clear() {
  _n = 0;
  _display.clearBuffer();
  _display.sendBuffer();
}

void Display::u8g_println(const String& str, int size) {
  int fidx = (size <= 1) ? 0 : (size - 1);
  if (fidx >= 4) fidx = 3;
  const char* font = U8G_FONT_SIZES[fidx];
  int h = U8G_FONT_HEIGHT[fidx];

  _display.setFont(font);
  _display.drawStr(0, h, str.c_str());
}

void Display::u8g_print(const String& str, int size) {
  int fidx = (size <= 1) ? 0 : (size - 1);
  if (fidx >= 4) fidx = 3;
  const char* font = U8G_FONT_SIZES[fidx];

  _display.setFont(font);
  _display.drawStr(0, 0, str.c_str());
}

void Display::printAt(const String &msg, int textSize, int v_offset, int h_offset) {
  int fidx = (textSize <= 1) ? 0 : (textSize - 1);
  if (fidx >= 4) fidx = 3;
  const char* font = U8G_FONT_SIZES[fidx];

  _display.clearBuffer();
  _display.setFont(font);
  _display.setFontMode(1);   // transparent mode (pixels directly written)
  _display.setDrawColor(1);  // white

  int h = U8G_FONT_HEIGHT[fidx];
  _display.setDrawColor(1);
  _display.setFont(font);
  _display.drawStr(h_offset, v_offset + h, msg.c_str());  // baseline at v_offset + h

  _display.sendBuffer();
}

void Display::say(const String &msg, bool clear, int textSize, int h_offset) {
  if (clear) _n = 0;

  if (_n < 4) {
    _lines[_n++] = msg;
  } else {
    for (int i = 1; i < 4; ++i)
      _lines[i - 1] = _lines[i];
    _lines[3] = msg;
  }

  int fidx = (textSize <= 1) ? 0 : (textSize - 1);
  if (fidx >= 4) fidx = 3;
  const char* font = U8G_FONT_SIZES[fidx];
  int h = U8G_FONT_HEIGHT[fidx];
  int lineHeight = h;  // approximate 8*textSize behavior
  int maxLinesOnScreen = SCREEN_HEIGHT / lineHeight;

  int linesToDraw = _n;
  if (linesToDraw > maxLinesOnScreen) linesToDraw = maxLinesOnScreen;

  _display.clearBuffer();
  _display.setFont(font);
  _display.setFontMode(1);
  _display.setDrawColor(1);

  for (int i = 0; i < linesToDraw; ++i) {
    int y = i * lineHeight + h;  // baseline at line bottom
    _display.drawStr(h_offset, y, _lines[i].c_str());
  }

  _display.sendBuffer();
}

void Display::point(int x, int y) {
  x = constrain(x, 0, SCREEN_WIDTH-1);
  y = constrain(y, 0, SCREEN_HEIGHT-1);

  _display.drawPixel(x, y);  // foreground color is 1 by default
  _display.sendBuffer();     // full‑buffer model
}

void Display::draw(Symbol& symbol, int atX, int atY) {
  // u8g2’s drawXBM/	drawXBMP expects 1‑bit XBM layout
  // If your symbol.bitmap is already in Adafruit‑style byte‑oriented bitmaps, keep that format.
  // If not, you may need to reinterpret the bits, but the API is the same:
  _display.clearBuffer();
  _display.drawXBMP(
    atX, atY,
    symbol.width, symbol.height,
    symbol.bitmap
  );
  _display.sendBuffer();
}

void Display::draw(Wheel& wheel, int atX, int atY) {
  Symbol* symbols = wheel.symbols;
  float pos = wheel.wheelPosition();
  int index = int(pos);
  float offset = pos - index;

  _display.clearBuffer();

  for (int i=index-1; i < index+2; i++) {
    draw(symbols[i], atX, atY);
  }

  _display.sendBuffer();
}