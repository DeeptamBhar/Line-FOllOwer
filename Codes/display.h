#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// SH1106 OLED object
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

inline void displayInit() {
  if (!display.begin(0x3C, true)) {     // 0x3C is default I2C address
    Serial.println("OLED not found!");
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0,0);
  display.println("OLED Ready!");
  display.display();
  delay(500);
}

// clear the display
inline void displayClear() {
  display.clearDisplay();
  display.setCursor(0,0);
}

// print text at (x,y)
inline void displayPrint(int x, int y, const String &text) {
  display.setCursor(x, y);
  display.print(text);
  display.display();
}

// print variable with label
template <typename T>
inline void displayPrintVar(int x, int y, const String &label, T value) {
  display.setCursor(x, y);
  display.print(label);
  display.print(value);
  display.display();
}

#endif


