#ifndef GY219_LIB
#define GY219_LIB

#include <Energia.h>
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

class GY219
{
    public:
        void        setCalibration          (int16_t value);
        void        reset                   ();
        uint16_t    readConfiguration       ();
        void        setVoltageRange         (uint8_t range);
        void        setShuntVoltageRange    (uint8_t value);
        float       getBusVoltage           ();
        float       getCurrent              ();

    private:
        byte        writeRegister           (uint8_t reg, uint16_t val);
        uint16_t    readRegister            (uint8_t reg);
        
    private:
        /// max current 2A
        float current_LSB = 0.000061035;

}


#endif