class P {
    uint32_t period;
    uint32_t dutyCycle;
public:
    P() {
        // disable
        // configure mode
        // configure prescaler
        // set timer start value
        //set the match value
        // enable timer

        // 10.3
        // GPIOHBCTL set aperture
        // RCGCGPIO enable clock
        // GPIODIR set direction
        // GPIOAFSEL set alternate function
        // GPIODR8R set drive strength
        // GPIOPUR, GPIOPDR, GPIOODR pull up/down, open drain
        // GPIODEN enable digital
        // no interrupts

        const uint32_t port_f_ahb_direction_base = 0x4005D000 + 0x400;
        const uint32_t port_f_ahb_data_base = 0x4005D000 + 0x000;
    }
    void setLed(uint8_t value) {
        // synchronous?
        // GPTMTnMATCHR = dutyCycle;
        // PF0
        const uint32_t port_f_ahb_data_base = 0x4005D000 + 0x000 + 0x0e0;
        *(volatile uint32_t*)port_f_ahb_data_base = value;
    }
};
