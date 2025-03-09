#ifndef MOTORS_H
#define MOTORS_H

#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PWM 0
#define MAX_PWM 4095

// PWM channels of pca9685 0-16
#define PWM_CHANNEL11 8
#define PWM_CHANNEL12 9
#define PWM_CHANNEL21 10
#define PWM_CHANNEL22 11

#define PWM_CHANNEL31 12
#define PWM_CHANNEL32 13
#define PWM_CHANNEL41 14
#define PWM_CHANNEL42 15

#define Servo_1 7

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setPWM(int chan1, int chan2, bool state, uint16_t val)
{
  Serial.println(val);
  if (state)
  {
    Serial.println("Quay lien tuc theo chieu thuan");
    pwm.setPWM(chan1, 0, val);
    pwm.setPWM(chan2, 0, 0);
  }
  else
  {
    Serial.println("Quay lien tuc theo chieu nghich");
    pwm.setPWM(chan2, 0, val);
    pwm.setPWM(chan1, 0, 0);
  }
}

void setPWMMotors_backward(int c1, int c2, int c3, int c4)
{
  char dbg_str[30];
  sprintf(dbg_str,"C1: %d\tC2: %d\tC3: %d\tC4: %d",c1,c2,c3,c4);
  Serial.println("Gia tri dieu khien cho 2 dong co DC 1, 2");
  Serial.println(dbg_str);

  pwm.setPWM(PWM_CHANNEL11, 0, c1);
  pwm.setPWM(PWM_CHANNEL12, 0, c2);
  pwm.setPWM(PWM_CHANNEL21, 0, c3);
  pwm.setPWM(PWM_CHANNEL22, 0, c4);
}
void setPWMMotors_remain(bool motor3, bool motor4, int val3, int val4)
{
  Serial.println("Dieu khien cho 2 dong co DC 3, 4");

  if (motor3){
      pwm.setPWM(PWM_CHANNEL31, 0, val3);
      pwm.setPWM(PWM_CHANNEL32, 0, 0);
  }
  else{
      pwm.setPWM(PWM_CHANNEL31, 0, 0);
      pwm.setPWM(PWM_CHANNEL32, 0, 0);
  }

  if (motor4){
      pwm.setPWM(PWM_CHANNEL41, 0, val4);
      pwm.setPWM(PWM_CHANNEL42, 0, 0);
  }
    else{
      pwm.setPWM(PWM_CHANNEL41, 0, 0);
      pwm.setPWM(PWM_CHANNEL42, 0, 0);
  }
}

void setPWMMotors_servo(bool servo_, int val1, int val2)
{
  Serial.println("Dieu khien dong co Servo");

  if (servo_){
      pwm.setPWM(Servo_1, 0, val1);
  }
  else{
      pwm.setPWM(Servo_1, 0, val2);
  }
}

void initMotors()
{
  Wire.begin(); // SDA, SCL,400000);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  // pwm.setPWMFreq(1600);
  pwm.setPWMFreq(50);
  Wire.setClock(400000);

  setPWMMotors_backward(0, 0, 0, 0);
}

#endif
