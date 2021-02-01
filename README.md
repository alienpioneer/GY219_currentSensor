# GY219 Current Sensor
Current sensor based on INA219, with a 0.1 ohms shunt resistor. The registers are 16 bit registers.Maximum current is 3.2 Ampers for a PGA value of 8x.
<pre>
                 R Shunt
 Supply ----> + /\/\/\/\/\/-> + -----> Load
             |               |
            Vin+            Vin- 
</pre>
V Shunt = Vin+ - Vin-.


# I2C Address
The device I2C address is 0x80, but the arduino wire library shifts the address to the left by one bit to add the read/write bit at the LSB.
So, if using the Arduino Wire library the address must be 0x40, since 0x40 << 1 = 0x80.

# Current Calculation
The current is calculated the based on the calibration value into the calibration register. This register must have a calibration value for the current measurement to be calculted correctly.Current = calibration_value * current_LSB (current least significant byte).
Current_LSB = the smallest current value that can be measured with one bit. Current_LSB = max_expected_current/2^15 (the INA219 registers are 16 bit ).

# The bus voltage
The bus voltage = Bus voltage register value * voltage_LSB. Voltage_LSB = 4mV. The bus voltage has 2 scale ranges: for 16 and 32Volts.

# Shunt voltage
Shunt voltage = shunt voltage register value * shunt_LSB. Shunt_LSB = 10uV (microVolts).

# PGA Function
The PGA function permits to scale the current range from 40 mA to 3.2A, by maintaining the same current resolution. The normal expected shunt voltage is smaller that 40 mv.
R shunt = 0.1 ohms -> i_max = 0.04V/0.1Ohms = 400mA.

The PGA increases the full scale range to x2, x4, x8 times.
40mV x2 =  80mV -> 800mA max current
40mV x4 = 160mV -> 1.6A max current
40mV x8 = 320mV -> 3.2A max current

This library automatically adjusts the measuring scale, depending on the input voltage.just call the autoRange( function).
