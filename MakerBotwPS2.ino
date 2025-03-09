#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PS2X_lib.h>
#include "motors.h"
#include "PS2_controller.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Setup starting...");

  initMotors();
  Serial.println("Motors initialized.");


  setupPS2controller();
  Serial.println("PS2 Controller initialized.");
}

void loop() {
  bool active = PS2control();
  Serial.print("PS2 control active: ");
  Serial.println(active);
  delay(50);
}
