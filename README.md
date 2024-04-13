# PIO LED PWM
A POC to create an object-oriented HAL/API for the Texas Instruments TM4C123g MCU,
geared toward recreating the sample app.
The app flashes and dims the RGB LEDs on the development board.

## Development environment
Since this is a POC, a bare-bones environment is used.
- Visual Studio Code
- PlatformIO IDE Extension
- C/C++ and C/C++ Extension pack Extensions

Development platform has been  Macbook Pro, but others should work as well.

## Running and testing on hardware
Use the following hardware:
- Texas Instruments TM4C123GXL LaunchPad board

Choose the "lptm4c123gh6pm" PIO environment.
Build, flash and debug using PlatformIO IDE.

> The upload log shows an error.
> Everything seems to work. Will try to clean that up.

## Testing
Currently there are no automated unit tests.
Manual testing via:
- visually verifying the RGB LED blinking patterns
- oscilloscope to check timing of the pulses on the GPIO pins

> There are currently two manual HIL test scenarios which are selected
> via the ``EXPERIMENT_1`` and ``EXPERIMENT_2`` #defines
> in src/main.cc. Each scenario uses a different
> port and timer to verify the code is working correctly.


## Inspecting the compiled code
An important part of this POC is to verify that the compiled code is optimized
and achieves the C++ [zero-overhead principle](https://en.cppreference.com/w/cpp/language/Zero-overhead_principle).

To inspect the compiled code, build the "asm-listing" environemnt.
The compiled Cortex M4 code is written to ``.pio/build/asm-listing/src/main.o``

What you should see is that the C++ code:
```
Port<PortIndex::PortF> port;
port.highPerformanceBusEnable = true;
```
results in the machine code:
```
    ldr	r3, .L10
    ldr	r2, [r3]
    orr	r2, r2, #32
    str	r2, [r3]
...
.L10
	.word	1074782316

```
which is as good as hand-coding and what libopencm3 generates.

> The asm-listing build log shows an error. 
> Haven't figured out what it is or how to clear it.

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
