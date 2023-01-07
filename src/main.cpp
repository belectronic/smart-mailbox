#include <Arduino.h>
#include "mailbox.h"

void setup()
{
  getBatteryVoltage();
  wifiCon();
}

void loop()
{
  // connect and send
  mqttCon();
  mqttRun();
  wifiDiscon();
  enterSleepmode();
}