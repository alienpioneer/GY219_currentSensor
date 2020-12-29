#include "GY219.h"

GY219 gy219;

void setup(){
  gy219.init();
  Serial.begin(115200);
  Serial.print("CONFIGURATION Before: ");
  Serial.println(gy219.getConfiguration());
  delay(10);
  gy219.setVoltageRange(16);
  delay(10);
  gy219.setCurrentRange(1600);
  Serial.print("CONFIGURATION After: "); 
  Serial.println(gy219.getConfiguration());
  Serial.print("CALIB: ");
  Serial.println(gy219.getCalibration());
}

void loop()
{ 
  delay(1000);
  Serial.print("CURRENT: ");
  Serial.println(gy219.getCurrent_mA());
  Serial.print("VOLTAGE: ");
  Serial.println(gy219.getBusVoltage());
}
