#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

// Pin mapping
#define ENCODER_CLK 18
#define ENCODER_DT  13
#define ENCODER_SW  12

volatile int encoderPos = 0;
volatile bool buttonPressed = false;
volatile bool buttonLatched = false;

volatile int lastEncoded = 0;

// ISR for encoder rotation
void IRAM_ATTR updateEncoder() {
  int MSB = digitalRead(ENCODER_CLK); // A
  int LSB = digitalRead(ENCODER_DT);  // B

  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderPos++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderPos--;

  lastEncoded = encoded;
  // REMOVED: encoderMoved = true; (no longer needed)
}

// ISR for button
void IRAM_ATTR handleButton() {
  int state = digitalRead(ENCODER_SW);

  if (state == LOW && !buttonLatched) {
    buttonPressed = true;
    buttonLatched = true;
  } else if (state == HIGH) {
    buttonLatched = false;
  }
}

inline void encoderInit() {
  pinMode(ENCODER_CLK, INPUT_PULLUP);
  pinMode(ENCODER_DT, INPUT_PULLUP);
  pinMode(ENCODER_SW, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_DT), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_SW), handleButton, CHANGE);
}

#endif