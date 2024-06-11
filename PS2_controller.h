#include <PS2X_lib.h>

PS2X ps2x; // create PS2 Controller Class object

#define PS2_DAT 12 // MISO  19
#define PS2_CMD 11 // MOSI  23
#define PS2_SEL 10 // SS     5
#define PS2_CLK 13 // SLK   18

#define SERVO 6

#define TOP_SPEED 4090
#define NORM_SPEED 2048
#define TURNING_FACTOR 0.7

int speed = NORM_SPEED;

void setupPS2controller()
{
  int err = -1;
  while (err != 0)
  {
    err = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
  }
}

bool PS2control()
{

  if (ps2x.ButtonPressed(PSB_L1)) {
    if (speed = NORM_SPEED) {
      speed = TOP_SPEED;
    } else {
      speed = NORM_SPEED;
    }
  }

  int servo = 0;
  if (ps2x.Button(PSB_GREEN)) {
    // Go up
    Serial.println("Going up");
    servo = 200;
  } else if (ps2x.Button(PSB_BLUE)) {
    // Go down
    Serial.println("Going down");
    servo = 400;
  }
  pwm.setChannelPWM(0, servo);
  pwm.setChannelPWM(1, 600 - servo);

  int nJoyX = 127 - ps2x.Analog(PSS_RY); // read x-joystick
  int nJoyY = 128 - ps2x.Analog(PSS_LX); // read y-joystick
  int nMotMixL;                          // Motor (left) mixed output
  int nMotMixR;                          // Motor (right) mixed output

  bool temp = (nJoyY * nJoyX > 0);
  if (nJoyY > 1 or nJoyY < -1) // Turning
  {
    nMotMixL = -nJoyY * !temp * TURNING_FACTOR;
    nMotMixR = -nJoyY * !temp * TURNING_FACTOR;
  }
  else // Forward or Reverse
  {
    nMotMixL = -nJoyX;
    nMotMixR = nJoyX;
  }

  nMotMixL = map(nMotMixL, -128, 128, -speed, speed);
  nMotMixR = map(nMotMixR, -128, 128, -speed, speed);

  // int test = map(nMotMixL, -128, 128, 100, 500);
  // Serial.println(test);
  // pwm.setChannelPWM(0, test);
  // pwm.setChannelPWM(1, 600 - test);


  setPWMMotors(nMotMixR, nMotMixL);
  return 1;
}

