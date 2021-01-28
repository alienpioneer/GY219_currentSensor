# GY219 Current Sensor
Current sensor based on INA219, with a 0.1 ohms shunt resistor

# I2C Address
The device I2C address is 0x80, but the arduino wire library shifts the address to the left by one bit to add the read/write bit at the LSB.
So, if using the Arduino Wire library the address must be 0x40, since 0x40 << 1 = 0x80.

# Current Calculation
The current is calculated the based on the calibration value into the calibration register. 
