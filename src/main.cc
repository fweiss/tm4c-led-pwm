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
static void delay(void) {
	for (int i = 0; i < FLASH_DELAY; i++) {
		__asm__("nop");
    }
}

int main(void) {
    struct X {
        struct portf {
            uint32_t *data = (uint32_t*)(0x4005D000 + 0x000);
            volatile uint32_t &gpio1 = data[0x1];
        } portf;
    } X;

	gpio_enable_ahb_aperture();
	rcc_sysclk_config(OSCSRC_MOSC, XTAL_16M, PLL_DIV_80MHZ);

    periph_clock_enable(RCC_GPIOF);
	const uint32_t outpins = (LED_R | LED_G | LED_B);
	gpio_mode_setup(RGB_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, outpins);
	gpio_set_output_config(RGB_PORT, GPIO_OTYPE_PP, GPIO_DRIVE_2MA, outpins);

    GPIOx<PortF> redLed(Pin::_1);
    GPIOx<PortF> blueLed(Pin::_2);
    GPIOx<PortF> greenLed(Pin::_3);

    while (true) {
        gpio_set(RGB_PORT, LED_B);
        uint8_t blue = blueLed;
        greenLed = (blue ? 0 : static_cast<int>(Pin::_3));

        // ((volatile uint32_t*)(0x4005D000 + 0x000))[0x02] = 0x02;
        // X.portf.gpio1 = 0xcc;

         // p.setLed(0x01);
		delay(); /* Wait a bit. */


		gpio_clear(RGB_PORT, LED_B);

        uint8_t blue2 = blueLed;
        greenLed = (blue2 ? 0 : static_cast<int>(Pin::_3));

        // *(volatile uint32_t*)(0x4005D000 + 0x000 + 0x0e0) = 0x00;

        // p.setLed(0x00);
		delay(); /* Wait a bit. */
    }

    return 0;
}
