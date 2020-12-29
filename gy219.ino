#include "GY219.h"

GY219 gy219;

void setup(){
  gy219.init();
  Serial.begin(115200);
  gy219.setCalibration(CALIBRATION);
  delay(100);
  Serial.println("Starting");
  gy219.reset();
  Serial.print("CONFIGURATION BEFORE: ");
  Serial.println(gy219.readConfiguration());
  delay(10);
  gy219.setVoltageRange(16);
  delay(10);
  Serial.print("CONFIGURATION After: ");
  Serial.println(gy219.readConfiguration());
}

void loop()
{ 
  delay(1000);
  Serial.print("CURRENT: ");
  Serial.println(gy219.getCurrent());
  Serial.print("VOLTAGE: ");
  Serial.println(gy219.getBusVoltage());
}
