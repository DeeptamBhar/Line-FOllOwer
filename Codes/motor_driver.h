#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>

// -----------------------------
// Define motor control pins
// -----------------------------
// Motor A
#define AIN1 16
#define AIN2 17

// Motor B
#define BIN1 5
#define BIN2 19

// -----------------------------
// Define PWM channels for ESP32
// -----------------------------
#define PWM_CH_A1 0
#define PWM_CH_A2 1
#define PWM_CH_B1 2
#define PWM_CH_B2 3

#define PWM_FREQ 1000   // 1 kHz
#define PWM_RES 8       // 8-bit (0–255)

// -----------------------------
// Initialize motor driver pins
// -----------------------------
inline void motorInit() {
  // Setup PWM channels
  ledcSetup(PWM_CH_A1, PWM_FREQ, PWM_RES);
  ledcSetup(PWM_CH_A2, PWM_FREQ, PWM_RES);
  ledcSetup(PWM_CH_B1, PWM_FREQ, PWM_RES);
  ledcSetup(PWM_CH_B2, PWM_FREQ, PWM_RES);

  // Attach pins to channels
  ledcAttachPin(AIN1, PWM_CH_A1);
  ledcAttachPin(AIN2, PWM_CH_A2);
  ledcAttachPin(BIN1, PWM_CH_B1);
  ledcAttachPin(BIN2, PWM_CH_B2);

  // Stop motors initially
  ledcWrite(PWM_CH_A1, 0);
  ledcWrite(PWM_CH_A2, 0);
  ledcWrite(PWM_CH_B1, 0);
  ledcWrite(PWM_CH_B2, 0);
}

// -----------------------------
// Motor A control with PWM
// -----------------------------
inline void motorA_forward(int speed) {
  ledcWrite(PWM_CH_A1, speed);  // 0–255
  ledcWrite(PWM_CH_A2, 0);
}

inline void motorA_backward(int speed) {
  ledcWrite(PWM_CH_A1, 0);
  ledcWrite(PWM_CH_A2, speed);
}

inline void motorA_stop() {
  ledcWrite(PWM_CH_A1, 0);
  ledcWrite(PWM_CH_A2, 0);
}

// -----------------------------
// Motor B control with PWM
// -----------------------------
inline void motorB_forward(int speed) {
  ledcWrite(PWM_CH_B1, speed);
  ledcWrite(PWM_CH_B2, 0);
}

inline void motorB_backward(int speed) {
  ledcWrite(PWM_CH_B1, 0);
  ledcWrite(PWM_CH_B2, speed);
}

inline void motorB_stop() {
  ledcWrite(PWM_CH_B1, 0);
  ledcWrite(PWM_CH_B2, 0);
}

#endif
