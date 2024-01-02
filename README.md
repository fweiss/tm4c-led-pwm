# PIO LED PWM
A POC to create an object-oriented HAL/API for the TM4C123g MCU,
geared toward recreating the sample app.

## MCU concepts
- port
- pin
- peripheral
  - gpio
- clock

## PWM notes
- 11.3.2.5 PWM Mode
- 11.4.5 PWM Mode
- 1.3.4.4 CCP Pins
- Table 10-2. GPIO Pins and Alternate Functions (64LQFP)
- GPIOAFSEL (GPIO/peripheral)
- GPIODR2R, GPIODR4R, ... (pin drive mA)
- Figure 10-1. Digital I/O Pads
- Register 22: GPIO Port Control (GPIOPCTL), offset 0x52C
- Table 23-5. GPIO Pins and Alternate Functions

## Links and references
[Simple PWM example using the library](https://www.egr.msu.edu/classes/ece480/capstone/fall15/group09/appnotes/JoshuaLambApplicationNote.pdf)

https://github.com/yuvadm/tiva-c/blob/master/boards/ek-tm4c123gxl/qs-rgb/qs-rgb.c

https://github.com/libopencm3/libopencm3-examples/blob/master/examples/tiva/lm4f/stellaris-ek-lm4f120xl/miniblink/miniblink.c

https://libopencm3.org/docs/latest/stm32l0/html/group__timer__file.html

[Tiva TM4C123G Lanchpad schematic](https://web.eece.maine.edu/~zhu/book/TivaC/EK-TM4C123GXL%20Rev%20A%20Schematic.pdf)

[Good overview guide to the TM4C123G MCU](https://microcontrollerslab.com/introduction-tiva-tm4c123g-launchpad/)

[Datasheet](https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf)

[User Manual with examples](https://www.ti.com/seclit/ml/ssqu015/ssqu015.pdf)
