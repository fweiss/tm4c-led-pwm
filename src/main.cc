#include <libopencm3/lm4f/rcc.h>
#include <libopencm3/lm4f/gpio.h>

#include "P.h"

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

constexpr uint32_t PortF = 0x4005D000;
template<uint32_t Port>
class GPIOx {
public:
    GPIOx(uint32_t _pin) : pin(_pin) {}
    GPIOx& operator=(uint32_t value) {
        *(volatile uint32_t*)(data + (pin << 2)) = value;
        return *this;
    }
    operator uint32_t() const {
        return *(volatile uint32_t*)(data + (pin << 2));
    }
private:
    const uint32_t pin;
    static constexpr uint32_t base = Port + 0x000;
    static constexpr uint32_t data = base + 0x000;
    static constexpr uint32_t dir = base + 0x400;
    static constexpr uint32_t afsel = base + 0x420;
    static constexpr uint32_t pur = base + 0x510;
    static constexpr uint32_t pdr = base + 0x514;
    static constexpr uint32_t den = base + 0x51C;
    static constexpr uint32_t lock = base + 0x520;
    static constexpr uint32_t cr = base + 0x524;
    static constexpr uint32_t amsel = base + 0x528;
    static constexpr uint32_t pctl = base + 0x52C;
    static constexpr uint32_t dr2r = base + 0x500;
    static constexpr uint32_t dr4r = base + 0x504;
    static constexpr uint32_t dr8r = base + 0x508;
    static constexpr uint32_t odr = base + 0x50C;
};

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

    P p;

    GPIOx<PortF> redLed(0x02);
    GPIOx<PortF> blueLed(0x04);

    while (true) {
        gpio_set(RGB_PORT, LED_B);
        uint8_t blue = blueLed;
        redLed = (blue ? 0 : 0x02);

        // ((volatile uint32_t*)(0x4005D000 + 0x000))[0x02] = 0x02;
        // X.portf.gpio1 = 0xcc;

         // p.setLed(0x01);
		delay(); /* Wait a bit. */


		gpio_clear(RGB_PORT, LED_B);

        uint8_t blue2 = blueLed;
        redLed = (blue2 ? 0 : 0x02);

        // *(volatile uint32_t*)(0x4005D000 + 0x000 + 0x0e0) = 0x00;

        // p.setLed(0x00);
		delay(); /* Wait a bit. */
    }

    return 0;
}
