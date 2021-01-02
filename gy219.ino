#include "GY219.h"

GY219 gy219;

void setup(){
  gy219.init();
  Serial.begin(115200);
  Serial.print("CONFIGURATION Before: ");
  Serial.println(gy219.getConfiguration());
  Serial.print("CALIB: ");
  Serial.println(gy219.getCalibration());
}

void loop()
{ 
  delay(2000);
  Serial.print("CURRENT: ");
  Serial.println(gy219.getCurrent_mA());
  Serial.print("VOLTAGE: ");
  Serial.println(gy219.getBusVoltage_mV());
  gy219.autoRange();
  Serial.print("CONFIGURATION: "); 
  Serial.println(gy219.getConfiguration());
  Serial.print("CALIBRATION: "); 
  Serial.println(gy219.CALIBRATION);
  Serial.print("Current LSB: "); 
  Serial.println(gy219.current_LSB, 4);
  Serial.print("Current Record: "); 
  Serial.println(gy219.previousCurrentRecord);
  Serial.println("***************************");
}
