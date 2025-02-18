# LIS3DSH for STM32F091

The [LIS3DSH](https://www.st.com/resource/en/datasheet/lis3dsh.pdf) is a three-axis linear accelerometer. The LIS3DH application note can be found [here](https://www.st.com/resource/en/application_note/cd00290365-lis3dh-mems-digital-output-motion-sensor-ultra-low-power-high-performance-3-axis-nano-accelerometer-stmicroelectronics.pdf).

The LIS3DSH sensor is available to the user through an analog-to-digital converter as well as it can be accessed through an I2C/SPI interface.

This library made for STM32F091 microcontroller but it can be applied to other STMt32 families.

This library was taken from [MYaqoobEmbedded](https://github.com/MYaqoobEmbedded/STM32-Tutorials/tree/master/Tutorial%2027%20-%20Motion%203-Axis%20Accelerometer%20LIS3DSH) and applied to this project using I2C protocol.



## Getting Started

**To include this library, add** `#include "LIS3DH_device.h"` **at the begging of the code.**


## License & copyright

Licensed under the [MIT License](LICENSE).
