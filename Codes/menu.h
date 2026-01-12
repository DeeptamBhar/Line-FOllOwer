#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "display.h"
#include "encoder.h"
#include "ir_sensor.h"

// ----------------- Menu states -----------------
enum MenuState {
  MENU_MAIN,
  MENU_HOME,
  MENU_CALIBRATE,
  MENU_IR
};

MenuState menuState = MENU_MAIN;
int menuIndex = 0;      // which item is selected
bool timerRunning = false;
unsigned long timerStartMillis = 0;
unsigned long elapsed = 0;


// ----------------- Helper: draw icons -----------------
void drawIconHome(int x, int y) {
  display.fillRect(x, y, 8, 8, SH110X_WHITE); // simple block icon
}
void drawIconCalibrate(int x, int y) {
  display.drawCircle(x+4, y+4, 4, SH110X_WHITE);
}
void drawIconIR(int x, int y) {
  display.drawTriangle(x, y+8, x+8, y+8, x+4, y, SH110X_WHITE);
}

// ----------------- Show main menu -----------------
void showMainMenu() {
  displayClear();
  displayPrint(20, 0, "Main Menu");

  // Home
  drawIconHome(0, 16);
  displayPrint(12, 16, (menuIndex == 0 ? "> Home" : "  Home"));

  // Calibrate
  drawIconCalibrate(0, 26);
  displayPrint(12, 26, (menuIndex == 1 ? "> Calibrate" : "  Calibrate"));

  // IR
  drawIconIR(0, 36);
  displayPrint(12, 36, (menuIndex == 2 ? "> IR" : "  IR"));
}

// ----------------- Home screen -----------------
// ----------------- Home screen -----------------
void showHome() {
  displayClear();
  displayPrint(0, 0, "Home - Timer");

if (timerRunning) {
  elapsed = (millis() - timerStartMillis) / 1000;
  displayPrintVar(0, 16, "Running: ", elapsed);
  } else {
  displayPrint(0, 16, "Stopped");
}


// inside handleEncoder() single click logic
else if (menuState == MENU_HOME) {
  timerRunning = !timerRunning;
  if (timerRunning) {
    timerStartMillis = millis();
  }
}


// ----------------- Calibrate screen -----------------
void showCalibrate() {
  displayClear();
  displayPrint(0, 0, "Calibrate");
  displayPrintVar(0, 16, "Kp:", 0);
  displayPrintVar(0, 26, "Ki:", 0);
  displayPrintVar(0, 36, "Kd:", 0);
}

// ----------------- IR screen -----------------
void showIR() {
  int v1 = analogRead(IR1);
  int v2 = analogRead(IR2);
  int v3 = analogRead(IR3);
  int v4 = analogRead(IR4);
  int v5 = analogRead(IR5);

  displayClear();
  displayPrint(0, 0, "IR Sensors");
  displayPrintVar(0, 16, "IR1:", v1);
  displayPrintVar(0, 26, "IR2:", v2);
  displayPrintVar(0, 36, "IR3:", v3);
  displayPrintVar(0, 46, "IR4:", v4);
  displayPrintVar(64, 16, "IR5:", v5);
}

// ----------------- Handle encoder input -----------------
unsigned long lastClickTime = 0;
int clickCount = 0;

void handleEncoder() {
  // rotation
  if (encoderMoved) {
    encoderMoved = false;
    if (menuState == MENU_MAIN) {
      if (encoderPos > 2) encoderPos = 0;
      if (encoderPos < 0) encoderPos = 2;
      menuIndex = encoderPos;
    }
  }

  // button
  if (buttonPressed) {
    buttonPressed = false;
    unsigned long now = millis();

    if (now - lastClickTime < 400) { // double click
      clickCount++;
    } else {
      clickCount = 1;
    }
    lastClickTime = now;

    if (clickCount == 2) {
      // double click → back to main menu
      menuState = MENU_MAIN;
      clickCount = 0;
    } else if (clickCount == 1) {
      // single click action
      if (menuState == MENU_MAIN) {
        if (menuIndex == 0) menuState = MENU_HOME;
        else if (menuIndex == 1) menuState = MENU_CALIBRATE;
        else if (menuIndex == 2) menuState = MENU_IR;
      } else if (menuState == MENU_HOME) {
      timerRunning = !timerRunning;
      if (timerRunning) timerStartMillis = millis();
}

      }
    }
  }
}

void showIR();   // forward declaration


// ----------------- Update display -----------------
void menuUpdate() {
  handleEncoder();

  switch(menuState) {
    case MENU_MAIN: showMainMenu(); break;
    case MENU_HOME: showHome(); break;
    case MENU_CALIBRATE: showCalibrate(); break;
    case MENU_IR: showIR(); break;
  }
}


#endif
