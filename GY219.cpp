#include "GY219.h"


float GY219::getCurrent(){ 
  int16_t register_value = readRegister(INA219_CURRENT_REG);
  return register_value*current_LSB;
}


float GY219::getBusVoltage(){ 
  /// result is in mV
  /// no overflow check, LSB = 4mV
  /// result = (register_val >> 3)* LSB
  uint16_t busVoltage = readRegister(INA219_BUS_VOLTAGE_REG);
  busVoltage = (busVoltage>>3);
  return busVoltage*0.004;
}


void GY219::setCalibration(int16_t value){ 
  writeRegister(INA219_CALIBRATION_REG, value);
}

void GY219::setVoltageRange(uint8_t range){
  uint16_t register_val = readRegister(INA219_CONF_REG);
  if (16 == range){
    register_val &= ~0x2000; 
  }
  else if (32 == range){
    register_val |= 0x2000;
  }
  writeRegister(INA219_CONF_REG, register_val);
}

void GY219::setShuntVoltageRange(uint8_t value){
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

uint16_t GY219::readConfiguration(){
  return readRegister(INA219_CONF_REG);
}

void GY219::reset(){
  uint16_t register_val = readRegister(INA219_CONF_REG);
  register_val |= 0x8000;
  writeRegister(INA219_CONF_REG, register_val);
}


uint16_t GY219::readRegister(uint8_t reg){
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


byte GY219::writeRegister(uint8_t reg, uint16_t val){
  Wire.beginTransmission(INA219_ADDR);
  Wire.write(reg);
  Wire.write((val >> 8) & 0xFF);
  Wire.write(val & 0xFF);
  return Wire.endTransmission();
}
