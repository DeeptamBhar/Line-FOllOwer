#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

#define BUZZER_PIN 23   // GPIO 23 on ESP32

// initialize buzzer
inline void buzzerInit() {
  pinMode(BUZZER_PIN, OUTPUT);
}

// turn buzzer ON
inline void buzzerOn() {
  digitalWrite(BUZZER_PIN, HIGH);
}

// turn buzzer OFF
inline void buzzerOff() {
  digitalWrite(BUZZER_PIN, LOW);
}

// beep buzzer for given duration (ms)
inline void buzzerBeep(int duration) {
  buzzerOn();
  delay(duration);
  buzzerOff();
}

#endif
