#include <Arduino.h>
#include <Wire.h>

#define INA219_ADDR 0x40
/// INA219 address is 0x80 
/// Arduino Wire library shifts the adddress left
/// and adds 0 or 1 to LSB for read or write 

#define INA219_CONF_REG           0x00
#define INA219_SHUNT_VOLTAGE_REG  0x01
#define INA219_BUS_VOLTAGE_REG    0x02
#define INA219_POWER_REG          0x03
#define INA219_CURRENT_REG        0x04
#define INA219_CALIBRATION_REG    0x05
#define CALIBRATION               6711

/// max current 2A
float current_LSB = 0.000061035;

float getCurrent(){ 
  int16_t register_value = readRegister(INA219_CURRENT_REG);
  return register_value*current_LSB;
}


float getBusVoltage(){ 
  /// result is in mV
  /// no overflow check, LSB = 4mV
  /// result = (register_val >> 3)* LSB
  uint16_t busVoltage = readRegister(INA219_BUS_VOLTAGE_REG);
  busVoltage = (busVoltage>>3);
  return busVoltage*0.004;
}


void setCalibration(int16_t value){ 
  writeRegister(INA219_CALIBRATION_REG, value);
}

void setVoltageRange(uint8_t range){
  uint16_t register_val = readRegister(INA219_CONF_REG);
  if (16 == range){
    register_val &= ~0x2000; 
  }
  else if (32 == range){
    register_val |= 0x2000;
  }
  writeRegister(INA219_CONF_REG, register_val);
}

void setShuntVoltageRange(uint8_t value){
  /// Set PGA range - 1-4 (40, 80, 160, 320mV)
  uint16_t register_val = readRegister(INA219_CONF_REG);
  switch(value){
    case 1:
      /// 40 mV
      register_val &= ~0x1800;
    case 2:
      /// 80 mV
      register_val &= ~0x1000;
      register_val |= 0x0800;
    case 3:
      /// 160 mV
      register_val |= 0x1000;
      register_val &= ~0x0800;
    case 4:
      /// 320 mV
      register_val |= 0x1800;
  }
}

uint16_t readConfiguration(){
  return readRegister(INA219_CONF_REG);
}

void reset(){
  uint16_t register_val = readRegister(INA219_CONF_REG);
  register_val |= 0x8000;
  writeRegister(INA219_CONF_REG, register_val);
}


uint16_t readRegister(uint8_t reg){
  uint8_t MSB, LSB;
  Wire.beginTransmission(INA219_ADDR);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(INA219_ADDR, 2);
  if(Wire.available())
  {
    MSB = Wire.read();
    LSB = Wire.read();
  }
  return ((MSB<<8) + LSB);
}


byte writeRegister(uint8_t reg, uint16_t val){
  Wire.beginTransmission(INA219_ADDR);
  Wire.write(reg);
  Wire.write((val >> 8) & 0xFF);
  Wire.write(val & 0xFF);
  return Wire.endTransmission();
}


void setup(){
  Wire.begin();
  Serial.begin(115200);
  setCalibration(CALIBRATION);
  delay(100);
  Serial.println("Starting");
  reset();
  Serial.print("CONFIGURATION BEFORE: ");
  Serial.println(readConfiguration());
  delay(10);
  setVoltageRange(16);
  delay(10);
  Serial.print("CONFIGURATION After: ");
  Serial.println(readConfiguration());
}

void loop()
{ 
  delay(1000);
  Serial.print("CURRENT: ");
  Serial.println(getCurrent());
  Serial.print("VOLTAGE: ");
  Serial.println(getBusVoltage());
}
