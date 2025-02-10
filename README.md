# Blue Pill MPU6050
This is a simple library for interfacing the MPU-6050 Inertial Measurement Unit (typically via the GY-521 breakout board) with STM32F103Cx - series microcontrollers,
chiefly the small development board commonly known as the Blue Pill, via the STM HAL API. While only some features are implemented, this would be enough for most hobbyist projects, for
which this library is primarily intended.

Tested on an STM32F103C8T6, will almost certainly work with STM32F013C6T6, will probably work with other STM32 controllers but I have no way to check.

## Instructions
A HAL I2C interface must be established first. Use STM32Cube, refer to: https://wiki.st.com/stm32mcu/wiki/Getting_started_with_I2C#Configure_I-

Each MPU-6050 must be separately awakened using the MPU6050_Init function. Only two can exist on the same I2C bus.

The default range is +-2g for the accelerometer and +-250deg/s for the gyro.

Reading from each of the axes you need should be done with the least possible delay because the IMU might get a new reading between reads from different registers.

It is not strictly necessary to check the status of each register read. If you don't want to do that, passing in NULL as the status pointer will avoid writing it.
