#include "motor_driver.h"
#include "encoder.h"

bool motorState = false; // OFF initially

void setup() {
  Serial.begin(115200);
  motorInit();
  encoderInit();
}

void loop() {
  // Check if button was pressed
  if (buttonPressed) {
    buttonPressed = false;  // reset flag

    motorState = !motorState;  // toggle state

    if (motorState) {
      motorA_forward(255);
      motorB_forward(255);
      Serial.println("Motors ON");
    } else {
      motorA_stop();
      motorB_stop();
      Serial.println("Motors OFF");
    }
  }

  // You can still read encoderPos if needed
  // Serial.println(encoderPos);
}
