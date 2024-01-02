#include "GPIO.h"

// based one exaple outline in the datasheet
// it sets up the PWM module 0 block 0
// PF1 (red) would be M1PWM5 module 1 generator 2
// M0PW0 (4) would be PB6
int mainy() {
	// pwm divide by 2
	const uint32_t RCC = 0x400FE000 + 0x060;
	uint32_t USEPWMDIV = (1 << 20);
	uint32_t PWMDIV = (0 << 17);
	RegisterAccess::write(RCC, USEPWMDIV | PWMDIV);

	// enable pwm clock
	// write RCC first
	// legacy, but use what?
	const uint32_t RCGC0 = 0x400fe000 + 0x100;;
	const uint32_t PWM0 = (1 << 20);
	RegisterAccess::write(RCGC0, PWM0);
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");


	// enable gpio clock
	// EXAMPLE IS OUT OF DATE, use Port::enableClock
	// const uint32_t RCGC2 = 0;
	// RegisterAccess::write(RCGC2, 0x00100000);


	// enable gpio alternate function
	// Port PortFx(5, 0x4005D000);
	Port PortFx(1, 0x40059000); // PB
	PortFx.enableHighPerformanceBus();
	// rcc_sysclk_config(OSCSRC_MOSC, XTAL_16M, PLL_DIV_80MHZ);
	PortFx.enableClock();

    DigitalPin redLed(PortFx, PinIndex::_1);

	// unlock PB6 for alternate function
	// OMMITTED FROM EXAMPLE
	// GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN
	// GPIOLOCK, GPIOCR
	*(volatile uint32_t*)(0x40059000 + 0x520) = 0x4C4F434b; // unlock
	*(volatile uint32_t*)(0x40059000 + 0x524) = (1 << 6);

	redLed.enableAlternateFunction = true;
	// GPIOAFSEL

	// assign function to appropriate gpio pin
	// GPIOPCTL
	const uint8_t M1PWM5 = 5; // module 1 generator 2 connect to PF1
	const uint8_t M0PWM0 = 4; // module 0 generator 0 connect to PB6
	redLed.portControl = M0PWM0;

	// pwm countdown with immediate updates
	const uint32_t PWM0BASE =  0x40028000; // module 0, 4 blocks
	// const uint32_t PWM0BASE =  0x40029000; // module 1
	const uint32_t PWM0CTL = PWM0BASE + 0x040; // 040, 080, 0c0, 100
	// RegisterAccess::write(PWM0CTL, 0x00000000); 
	const uint32_t PWM0GENA = PWM0BASE + 0x060; // 060, 0a0 0e0 120
	RegisterAccess::write(PWM0GENA, 0x0000008C);
	const uint32_t PWM0GENB = PWM0BASE + 0x064; // 064, 0a4, 0e4, 124
	RegisterAccess::write(PWM0GENB, 0x0000080C);

	// set the period
	const uint32_t PWM0LOAD = PWM0BASE + 0x050; // 050 090 0d0 110
	RegisterAccess::write(PWM0LOAD, 0x0000018F);

	// set the pulse width
	const uint32_t PWM0CMPA = PWM0BASE + 0x058; // 058, 098, 0d8, 118
	RegisterAccess::write(PWM0CMPA, 0x0000012B); // 25% duty
	const uint32_t PWM0CMPB = PWM0BASE + 0x05c; // 05c 09c 0dc, 11c
	RegisterAccess::write(PWM0CMPB, 0x00000063); // 75% duty

	// start timers
	// maybe first rest via SRPWM?
	// const uint32_t PWM0CTL = PWM0BASE + 0x040; // 040 080 0c0 100 duplicate
	RegisterAccess::write(PWM0CTL, 0x00000001);

	// enable outputs
	const uint32_t PWMENABLE = PWM0BASE + 0x008; // per module
	RegisterAccess::write(PWMENABLE, 0x00000003);

	while (true) {

	}
	return 0;
}