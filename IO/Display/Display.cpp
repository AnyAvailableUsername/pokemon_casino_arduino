#include "Display.h"

Display::Display()
  : _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1),
    _n(0) {}

bool Display::begin() {
  // Initialize I²C on GPIO0 (SDA) and GPIO2 (SCL)
  Wire.begin();

  // Initialize SSD1306
  if (!_display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
    return false;

  _display.clearDisplay();
  _display.display();
  return true;
}

void Display::clear() {
  _n = 0;
  _display.clearDisplay();
  _display.display();
}

void Display::printAt(const String &msg, int textSize, int v_offset, int h_offset) {

  _display.setTextSize(textSize);
  _display.setTextColor(SSD1306_WHITE);
  _display.setCursor(h_offset, v_offset);
  _display.println(msg);  
  _display.display();
}

void Display::say(const String &msg, bool clear, int textSize, int h_offset) {
  //return;
  if (clear) _n = 0;

  if (_n < 4) {
    _lines[_n++] = msg;
  } else {
    for (int i = 1; i < 4; ++i) 
      _lines[i - 1] = _lines[i];
    _lines[3] = msg;
  }

  _display.clearDisplay();
  _display.setTextSize(textSize);
  _display.setTextColor(SSD1306_WHITE);

  const int lineHeight = 8 * textSize;
  const int maxLinesOnScreen = SCREEN_HEIGHT / lineHeight; // 32 / (8*textSize)
  int linesToDraw = _n;
  if (linesToDraw > maxLinesOnScreen) linesToDraw = maxLinesOnScreen;

  for (int i = 0; i < linesToDraw; ++i) {
    _display.setCursor(h_offset, i * 8);
    _display.println(_lines[i]);
  }

  _display.display();
}

void Display::point(int x, int y) {
  _display.drawPixel(
    constrain(x, 0, SCREEN_WIDTH-1),
    constrain(y, 0, SCREEN_HEIGHT-1),
    SSD1306_WHITE
  );
  _display.display();

}
