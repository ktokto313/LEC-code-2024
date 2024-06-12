#include <stdio.h>
#include <Wire.h>
#include <PCA9685.h>

#define MIN_PWM 0
#define MAX_PWM 4095

// PCA9685 PWM channels 0-16
#define MOTOR_RIGHT_CONTROL 4
#define MOTOR_LEFT_CONTROL 7

// Arduino channel
#define MOTOR_RIGHT_FORWARD 6
#define MOTOR_RIGHT_BACKWARD 7
#define MOTOR_LEFT_FORWARD 4
#define MOTOR_LEFT_BACKWARD 5

PCA9685 pwm;

void setPWMMotors(int c1, int c2)
{
  // char dbg_str[30];
  // sprintf(dbg_str,"C1: %d\tC2: %d",c1,c2);
  // Serial.println(dbg_str);

  //true = 1
  //false = 0
  digitalWrite(MOTOR_RIGHT_FORWARD, c1 > 0);
  digitalWrite(MOTOR_RIGHT_BACKWARD, !(c1 > 0));

  digitalWrite(MOTOR_LEFT_FORWARD, c2 > 0);
  digitalWrite(MOTOR_LEFT_BACKWARD, !(c2 > 0));

  pwm.setChannelPWM(MOTOR_RIGHT_CONTROL, abs(c1));
  pwm.setChannelPWM(MOTOR_LEFT_CONTROL, abs(c2));
}

int getServoPWM(int milisec) {
  return map(milisec, 0, 2, 0, 410);
}

void initMotors()
{
  Serial.println("1");
  Wire.begin();
  Serial.println("2");

  pwm.resetDevices();
  Serial.println("3");

  pwm.init();
  Serial.println("4");

  pwm.setPWMFrequency(50);

  pwm.setAllChannelsPWM(0);
}