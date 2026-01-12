#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include <Arduino.h>

// IR sensor pins
// #define IR1 32
// #define IR2 35
// #define IR3 34
// #define IR4 15
// #define IR5 4

#define IR1 27
#define IR2 14
#define IR3 25
#define IR4 26
#define IR5 33


inline void irInit() {
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
}

inline void irReadAll() {
  int v1 = analogRead(IR1);
  int v2 = analogRead(IR2);
  int v3 = analogRead(IR3);
  int v4 = analogRead(IR4);
  int v5 = analogRead(IR5);

  Serial.print("IR1: "); Serial.print(v1);
  Serial.print(" | IR2: "); Serial.print(v2);
  Serial.print(" | IR3: "); Serial.print(v3);
  Serial.print(" | IR4: "); Serial.print(v4);
  Serial.print(" | IR5: "); Serial.println(v5);
}

#endif
