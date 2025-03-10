#ifndef MOTORS_H
#define MOTORS_H

#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PWM 0
#define MAX_PWM 4095

// PWM channels của PCA9685 (0-16)
#define PWM_CHANNEL1 8
#define PWM_CHANNEL2 9
#define PWM_CHANNEL3 10
#define PWM_CHANNEL4 11

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

bool isInverted = true;

void setPWMMotors(int c1, int c2, int c3, int c4) {
  char dbg_str[50];
  sprintf(dbg_str, "setPWMMotors - C1: %d, C2: %d, C3: %d, C4: %d", c1, c2, c3, c4);
  Serial.println(dbg_str);

  pwm.setPin(PWM_CHANNEL1, c1, isInverted);
  pwm.setPin(PWM_CHANNEL2, c2, isInverted);
  pwm.setPin(PWM_CHANNEL3, c3, isInverted);
  pwm.setPin(PWM_CHANNEL4, c4, isInverted);
}

void initMotors() {
  Serial.println("initMotors - Starting initialization...");
  Wire.begin();
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1600);
  Wire.setClock(400000);

  setPWMMotors(0, 0, 0, 0);
  Serial.println("initMotors - Motors set to 0.");
}

#endif
