#include <libopencm3/lm4f/rcc.h>
#include <libopencm3/lm4f/gpio.h>

#include "GPIO.h"
#include "pwm-timer.h"
// #include "pwm.h"

enum {
	PLL_DIV_80MHZ 	= 5,
	PLL_DIV_57MHZ 	= 7,
	PLL_DIV_40MHZ 	= 10,
	PLL_DIV_20MHZ 	= 20,
	PLL_DIV_16MHZ 	= 25,
};

#define RGB_PORT	GPIOF
enum {
	LED_R	= GPIO1,
	LED_G	= GPIO3,
	LED_B	= GPIO2,
};

const int FLASH_DELAY = 8000000;
__attribute__((noinline))
static void delay(void) {
	for (int i = 0; i < FLASH_DELAY; i++) {
		__asm__("nop");
    }
}

int main(void) {
	Clock clocks;
	// Clock::waitForMasterOscillator();
	// rcc_sysclk_config(OSCSRC_MOSC, XTAL_16M, PLL_DIV_80MHZ);
	clocks.blinkClockSetup();

	Port<PortIndex::PortF> port;

	// maybe move to constructor
    port.highPerformanceBusEnable = true;
    port.clockEnable = true;
	// require 3 system clock delay after peripheral clock enable
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");

	// const uint32_t outpins = (LED_R | LED_G | LED_B);
	const uint32_t outpins = (LED_G | LED_B);
	gpio_mode_setup(RGB_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, outpins);
	gpio_set_output_config(RGB_PORT, GPIO_OTYPE_PP, GPIO_DRIVE_2MA, outpins);
	
	auto redLed = port.pin1;
	auto blueLed = port.pin2;
	auto greenLed = port.pin3;

	// mode output
	// could streamline using or'ed pin bits
	redLed.directionOutput = true;
	redLed.digitalEnable = true;
	redLed.alternateFunctionEnable = false;
	redLed.pullUpEnable = false;
	redLed.pullDownEnable = false;
	// output config
	redLed.openDrainEnable = false;
	redLed.drive2mA = true;

#define EXPERIMENT_2
	// r = PF1 T0CCP1
	// b = PF2 T1CCP0
	// g = PF3 T1CCP1

#ifdef EXPERIMENT_1
	// block 0 and 1, timer B
	// flash blue dim red/green
	auto &mainLed = blueLed;
	auto &pwmLed = greenLed;
 	auto &timerBlock = TimerBlocks::block1;
	auto &timer = timerBlock.timerB;
#endif

#ifdef EXPERIMENT_2
	// block 1 timer 0/1 experiment
	// flash red dim green/blue
    auto &mainLed = redLed;
	auto &pwmLed = greenLed;
	auto &timerBlock = TimerBlocks::block1;
	auto &timer = timerBlock.timerB;
#endif

	timerBlock.clockEnable = true; // todo delay
	// timerBlock.configure = timerBlock.configure.TIMER_16_BIT;
	timerBlock.configuration = 4;
	setupPwm(timer);
	pwmLed.alternateFunctionEnable = true;
	const uint8_t digitalFunctionTimerCCP = 7;
	pwmLed.portMode = digitalFunctionTimerCCP;

    while (true) {
		mainLed = true;
		delay();
		mainLed = false;
		delay();
    }

    return 0;
}
