#include <stdint.h>

enum class Port {
    A = 0x40004000,
    B = 0x40005000,
    C = 0x40006000,
    D = 0x40007000,
    E = 0x40024000,
    F = 0x40025000,
};

enum class Pin {
    _0 = 0x01,
    _1 = 0x02,
    _2 = 0x04,
    _3 = 0x08,
    _4 = 0x10,
    _5 = 0x20,
    _6 = 0x40,
    _7 = 0x80,
};

// use this template to define a port
// each gpio port has an index 0-5
// each gpio port has a base address, either abp or ahp
// currently, abp ignored, ahp used
// somne ports have restrictions on which pins can be used
// template <uint8_t Index, uint32_t gpioPortBase>
class Porty {
public:
    Porty(uint32_t index_, uint32_t gpioPortBase_) : index(index_), gpioPortBase(gpioPortBase_) {}
    // these are for GPIO module
    // other modules may have different registers, CAN, Timer, I2C, ...
    void enableClock() {
        *(volatile uint32_t*)(RCGCGPIO) |= (1 << index);
        // delay 3 system clock cycles
    }
    void disableClock() {
        *(volatile uint32_t*)(RCGCGPIO) &= ~(1 << index);
    }
    void enableHighPerformanceBus() {
        *(volatile uint32_t*)(GPIOHBCTL) |= (1 << index);
    }
    const uint32_t index;
    const uint32_t base = 0x400FE000; // system control base
    const uint32_t gpioPortBase;
    // abp base and ahp base
    const uint32_t RCGCGPIO = base + 0x608; // General-Purpose Input/Output Run Mode Clock Gating Control
    // 0x508 General-Purpose Input/Output Software Reset (SRGPIO)
    // General-Purpose Input/Output Peripheral Present (PPGPIO), offset 0x308
    const uint32_t GPIOHBCTL = base + 0x06C; // GPIO High-Performance Bus Control
};

// define the ports
// Porty<5, 0x4005D000> PortFx;
// using PortFx = Portx<5, 0x4005D000>;

// use this template to define a gpio pin
// template<class port>
class GPIOx {
public:
    GPIOx(Porty &port, Pin _pin) : base(port.gpioPortBase), pin(_pin) {}
    // GPIOx& operator=(uint32_t value) {
    //     *(volatile uint32_t*)(data + (pinNumber() << 2)) = value;
    //     return *this;
    // }
    GPIOx& operator=(bool onOff) {
        *(volatile uint32_t*)(data + (pinNumber() << 2)) = onOff ? 0xff : 0x00;
        return *this;
    }
    // operator uint32_t() const {
    //     return *(volatile uint32_t*)(data + (static_cast<uint32_t>(pin) << 2));
    // }
    operator bool() const {
        return *(volatile uint32_t*)(data + (pinNumber() << 2)) != 0;
    }
private:
    const uint32_t base;
    const Pin pin;
    uint8_t pinNumber() const {
        return static_cast<uint8_t>(pin);
    }
    const uint32_t data = base + 0x000;
    const uint32_t dir = base + 0x400;
    const uint32_t afsel = base + 0x420;
    const uint32_t pur = base + 0x510;
    const uint32_t pdr = base + 0x514;
    const uint32_t den = base + 0x51C;
    const uint32_t lock = base + 0x520;
    const uint32_t cr = base + 0x524;
    const uint32_t amsel = base + 0x528;
    const uint32_t pctl = base + 0x52C;
    const uint32_t dr2r = base + 0x500;
    const uint32_t dr4r = base + 0x504;
    const uint32_t dr8r = base + 0x508;
    const uint32_t odr = base + 0x50C;
};
