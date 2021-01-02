#ifndef GY219_LIB
#define GY219_LIB

//#include <Energia.h>
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


class GY219
{
    public:
        void        init                    ();
        void        reset                   ();
        void        setCalibration          (uint16_t value);
        void        setVoltageRange         (uint8_t range);
        void        setShuntVoltageRange    (uint8_t gain);
        void        setCurrentRange         (uint16_t maxCurrent);
        uint16_t    getConfiguration        ();
        uint16_t    getCalibration          ();
        float       getBusVoltage_mV        ();
        float       getCurrent_mA           ();
        void        autoRange               ();

    public:
        float       current_LSB;
        uint16_t    CALIBRATION;
        uint8_t     GAIN;
        float       previousCurrentRecord;
        float       previousVoltageRecord;

    private:
        byte        writeRegister           (uint8_t reg, uint16_t val);
        uint16_t    readRegister            (uint8_t reg);
        
    private:
        TwoWire     i2c;
        
};


#endif
