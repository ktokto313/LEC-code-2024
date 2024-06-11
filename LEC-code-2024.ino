#include "motors.h"
#include "PS2_controller.h"

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting up");
  initMotors();
  setupPS2controller();
  Serial.println("Done setup!");
}
int deg = 0;

void loop()
{
  digitalWrite(13, HIGH);

  ps2x.read_gamepad(0, 0);
  PS2control();
  delay(50);
}