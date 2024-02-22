scope: 250 ms
master clock: 16 MHz
pll clock: 400 Mhz
pll divisor: 
interval: 65535, 255, 16-bit mode
toal count is 16777216-1
.25 / 16777216 = 1/67.1 MHz

255 * 65536 / 80000000 = 208 ms

in pwm mode, prescaler holds MSB of the count
pwm system clock:

timer
per block
normal 16 bit and wide 32 bit GPTMCFG
can be concatenated 

## RCC2 vs RCC
Following fields in RCC2 override those in RCC
- SYSDIV2
- PWRDN2
- BYPASS2
- OSCSRC2

## System Clock
the system clock comes from a multiplexor
the multiplexor can use SYSDIV or BYPASS

comes through several levels of multiplex
there is also sleep gating

BYPASS selects the input to SYSDIV. 
it can select the PLL or the OSCSRC

crystal value specifies the external? oscillator frequency
4 - 25 MHz
specific values required for USB and when using the PLL

> Write the RCC register prior to writing the RCC2 register, but why?

## SYSDIV2
used to divide PLL when both USESYSDIV and USERCC2 are set

## DIV400
- when clear, 200 MHz PLL and 6 bit SYSDIV2
- when set, 400 MHz PLL and 7-bit divisor including SYSDIV2LSB

Analytically
- clear: (400/2)/(x7/2)
- set: (400)/x7
effectively the same, except clear only allows even divisors

we're setting to 5, which means a divisor of 6
that would be a system clock of 66.67 MHz
however, a setting of 4 would mean a divisor of 5
that would be a system clock of 80 MHz

### Initialization and setup
see [5.3]

### level 1
bypass or sysdiv

### Level 2
DIV400 or OSCSRC

