#ifndef PS2_CONTROLLER_H
#define PS2_CONTROLLER_H

#include <PS2X_lib.h>
#include "motors.h"

PS2X ps2x;

#define X_JOY_CALIB 127
#define Y_JOY_CALIB 128

#define PS2_DAT 12  // MISO
#define PS2_CMD 13  // MOSI
#define PS2_SEL 15  // SS
#define PS2_CLK 14  // SCK

#define TOP_SPEED 4095
#define NORM_SPEED 2048

#define SINGLE_HAND_DRIVING 0
#define TWO_HAND_DRIVING 1

bool driving_mode = SINGLE_HAND_DRIVING;

void setupPS2controller() {
  Serial.println("setupPS2controller - Configuring PS2 Controller...");
  int err = -1;
  while (err != 0) {
    err = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, false);
    Serial.print("setupPS2controller - Config error code: ");
    Serial.println(err);
    delay(100);
  }
  Serial.println("setupPS2controller - PS2 Controller configured successfully.");
  ps2x.readType();
}

bool PS2control() {
  int speed = NORM_SPEED;
  if (ps2x.Button(PSB_R2))
    speed = TOP_SPEED;
  if (ps2x.ButtonPressed(PSB_SELECT)) {
    driving_mode = !driving_mode;
    Serial.print("PS2control - Driving mode changed to: ");
    Serial.println(driving_mode);
  }
  
  int nJoyX = X_JOY_CALIB - ps2x.Analog(PSS_RX);
  int nJoyY = Y_JOY_CALIB - (driving_mode ? ps2x.Analog(PSS_LY) : ps2x.Analog(PSS_RY));
  
  Serial.print("PS2control - Joystick X: ");
  Serial.print(nJoyX);
  Serial.print(" | Joystick Y: ");
  Serial.println(nJoyY);
  
  if (nJoyX == -1 && nJoyY == 0) {
    Serial.println("PS2control - Joystick in default position, stopping motors.");
    setPWMMotors(0, 0, 0, 0);
    return false;
  }
  
  int nMotMixL, nMotMixR;
  bool temp = (nJoyY * nJoyX > 0);
  
  if (nJoyX != 0) {
    nMotMixL = -nJoyX + (nJoyY * temp);
    nMotMixR = nJoyX + (nJoyY * !temp);
  } else {
    nMotMixL = nJoyY;
    nMotMixR = nJoyY;
  }
  
  Serial.print("PS2control - Mixed outputs: L=");
  Serial.print(nMotMixL);
  Serial.print(" | R=");
  Serial.println(nMotMixR);
  
  int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
  
  if (nMotMixR > 0) {
    c3 = map(nMotMixR, 0, 128, 0, speed);
  } else if (nMotMixR < 0) {
    c4 = map(abs(nMotMixR), 0, 128, 0, speed);
  }
  
  if (nMotMixL > 0) {
    c1 = map(nMotMixL, 0, 128, 0, speed);
  } else if (nMotMixL < 0) {
    c2 = map(abs(nMotMixL), 0, 128, 0, speed);
  }
  
  Serial.print("PS2control - PWM values: ");
  Serial.print("C1=");
  Serial.print(c1);
  Serial.print("  C2=");
  Serial.print(c2);
  Serial.print("  C3=");
  Serial.print(c3);
  Serial.print("  C4=");
  Serial.println(c4);
  
  setPWMMotors(c1, c2, c3, c4);
  
  return true;
}

#endif
