#include "GY219.h"

void GY219::init(){
    i2c.begin();
    /// max 2000mA
    reset();
    setCurrentRange(2000);
}


float GY219::getCurrent_mA(){
    /// result is in mA 
    int16_t register_value = readRegister(INA219_CURRENT_REG);
    return register_value*current_LSB;
}


float GY219::getBusVoltage(){ 
    /// result is in V
    /// no overflow check, LSB = 4mV
    /// result = (register_val >> 3)* LSB
    uint16_t busVoltage = readRegister(INA219_BUS_VOLTAGE_REG);
    busVoltage = (busVoltage>>3);
    return busVoltage*0.004;
}


void GY219::setCalibration(uint16_t value){ 
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


void GY219::setShuntVoltageRange(uint8_t gain){
    /// Set PGA range - 1-4 (40, 80, 160, 320mV)
    uint16_t register_val = readRegister(INA219_CONF_REG);
    switch(gain){
      case 1:
          /// 40 mV
          register_val &= ~(0x1800);
          break;
      case 2:
          /// 80 mV
          register_val &= ~(0x1000);
          register_val |= 0x0800;
          break;
      case 3:
          /// 160 mV
          register_val |= 0x1000;
          register_val &= ~(0x800);
          break;
      case 4:
          /// 320 mV
          register_val |= 0x1800;
          break;
    }
    writeRegister(INA219_CONF_REG, register_val);
}


uint16_t GY219::getConfiguration(){
    return readRegister(INA219_CONF_REG);
}


uint16_t GY219::getCalibration(){
    return readRegister(INA219_CALIBRATION_REG);
}


void GY219::reset(){
    uint16_t register_val = readRegister(INA219_CONF_REG);
    register_val |= 0x8000;
    writeRegister(INA219_CONF_REG, register_val);
}


uint16_t GY219::readRegister(uint8_t reg){
    uint8_t MSB, LSB;
    i2c.beginTransmission(INA219_ADDR);
    i2c.write(reg);
    i2c.endTransmission();
    i2c.requestFrom(INA219_ADDR, 2);
    if(i2c.available())
    {
    MSB = i2c.read();
    LSB = i2c.read();
    }
return ((MSB<<8) + LSB);
}


byte GY219::writeRegister(uint8_t reg, uint16_t val){
    i2c.beginTransmission(INA219_ADDR);
    i2c.write(reg);
    i2c.write((val >> 8) & 0xFF);
    i2c.write(val & 0xFF);
    return i2c.endTransmission();
}


void GY219::setCurrentRange(uint16_t maxCurrent){
    /// set max current in mA
    switch(maxCurrent){
        case 3200:
            current_LSB = 0.09765625;
            CALIBRATION = 4196;
            GAIN = 4;
            break;
        case 2000:
            current_LSB = 0.061035;
            CALIBRATION = 6710;
            GAIN = 4;
            break;
        case 1600:
            current_LSB = 0.04882812;
            CALIBRATION = 8308;
            GAIN = 3;
            break;
        case 800:
            current_LSB = 0.02441406;
            CALIBRATION = 16778;
            GAIN = 2;
            break;
        case 400:
            current_LSB = 0.01220703;
            CALIBRATION = 33554;
            GAIN = 1;
            break;
    }
    setCalibration(CALIBRATION);
    setShuntVoltageRange(GAIN);
}
