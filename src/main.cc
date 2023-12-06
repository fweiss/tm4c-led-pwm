#include <libopencm3/lm4f/rcc.h>
#include <libopencm3/lm4f/gpio.h>

#include "GPIO.h"

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
	gpio_enable_ahb_aperture();
	rcc_sysclk_config(OSCSRC_MOSC, XTAL_16M, PLL_DIV_80MHZ);

    periph_clock_enable(RCC_GPIOF);
    // PortFx.enableClock();

	const uint32_t outpins = (LED_R | LED_G | LED_B);
	gpio_mode_setup(RGB_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, outpins);
	gpio_set_output_config(RGB_PORT, GPIO_OTYPE_PP, GPIO_DRIVE_2MA, outpins);

    GPIOx<PortFx> redLed(Pin::_1);
    GPIOx<PortFx> blueLed(Pin::_2);
    GPIOx<PortFx> greenLed(Pin::_3);

    // redLed = true;

    GPIOx<PortF> &mainLed = redLed;

    while (true) {
        mainLed = true;
		delay();
        mainLed = false;
		delay();
    }

    return 0;
}
