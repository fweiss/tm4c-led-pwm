#include <stdint.h>

// experiment

template <uint32_t zindex, uint32_t gpioPortBase>
class xPort {
public:
    void enableClock() const {
        *(volatile uint32_t*)(RCGCGPIO) |= (1 << index);
        // delay 3 system clock cycles
    }
    static constexpr uint32_t index = zindex;
    static constexpr uint32_t base = gpioPortBase;
    static constexpr uint32_t systemControlBase = 0x400FE000; // system control base
    static constexpr uint32_t RCGCGPIO = systemControlBase + 0x608; // General-Purpose Input/Output Run Mode Clock Gating Control
};

class zPort {
public:
    zPort(uint32_t zindex, uint32_t gpioPortBase) : index(zindex), base(gpioPortBase) {}
    void enableClock() const {
        *(volatile uint32_t*)(RCGCGPIO) |= (1 << index);
        // delay 3 system clock cycles
    }
    const uint32_t index;
    const uint32_t base;
    const uint32_t systemControlBase = 0x400FE000; // system control base
    const uint32_t RCGCGPIO = systemControlBase + 0x608; // General-Purpose Input/Output Run Mode Clock Gating Control
};

template<class port, uint32_t pin>
class xGPIO {
    static constexpr uint32_t base = port::base;
    static constexpr uint32_t data = base;
public:
    xGPIO & operator=(bool onOff) {
        *(volatile uint32_t*)(data + (pin << 2)) = onOff ? 0xff : 0x00;
        return *this;
    }

};

// template<zPort& port, uint32_t pin>
class zGPIO {
    const uint32_t base;
    const uint32_t pin;
    const uint32_t data = base;
public:
    zGPIO(zPort& port, uint32_t pin) : base(port.base), pin(pin) {}
    zGPIO & operator=(bool onOff) {
        *(volatile uint32_t*)(data + (pin << 2)) = onOff ? 0xff : 0x00;
        return *this;
    }

};

// template<class port, uint32_t pin>
// class yGPIO {
//     static constexpr uint32_t &base = port.base;
// };

void cf() {
    xPort<5, 0x4005D000> xPortF;
    xPortF.enableClock();    
    xGPIO<decltype(xPortF), 0x01> led;
    led = true;

    // using yPortF = xPort<5, 0x4005D000>;
    // yPortF port;
    // port.enableClock();
    // yGPIO<port, 0x01> led2;

}
void cc() {
    zPort zPortF(5, 0x4005D000);
    zPortF.enableClock();
    zGPIO led(zPortF, 0x01);
    led = true;
}

// end experiment

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

constexpr uint32_t PortF = 0x4005D000;
constexpr uint32_t PortFx = 0x4005D000;

class PortInfo {
    public:
    PortInfo(uint32_t gpioPortBase) : gpioBase(gpioPortBase) {}
    const uint32_t gpioBase;
};

// use this template to define a port
// each gpio port has an index 0-5
// each gpio port has a base address, either abp or ahp
// currently, abp ignored, ahp used
// somne ports have restrictions on which pins can be used
template <uint8_t Index, uint32_t gpioPortBase>
class Porty : public PortInfo {
public:
    Porty() : PortInfo(gpioPortBase) {}
    // these are for GPIO module
    // other modules may have different registers, CAN, Timer, I2C, ...
    static void enableClock() {
        *(volatile uint32_t*)(RCGCGPIO) |= (1 << Index);
        // delay 3 system clock cycles
    }
    static void disableClock() {
        *(volatile uint32_t*)(RCGCGPIO) &= ~(1 << Index);
    }
    static constexpr uint32_t base = 0x400FE000; // system control base
    // abp base and ahp base
    static constexpr uint32_t RCGCGPIO = base + 0x608; // General-Purpose Input/Output Run Mode Clock Gating Control
    // 0x508 General-Purpose Input/Output Software Reset (SRGPIO)
    // General-Purpose Input/Output Peripheral Present (PPGPIO), offset 0x308
    // GPIO High-Performance Bus Control (GPIOHBCTL), offset 0x06C
};

// define the ports
// Porty<5, 0x4005D000> PortFx;
// using PortFx = Portx<5, 0x4005D000>;

// use this template to define a gpio pin
// template<class port>
template <uint32_t gpioPortBase>
class GPIOx {
public:
    GPIOx(Pin _pin) : pin(_pin) {}
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
    const Pin pin;
    uint8_t pinNumber() const {
        return static_cast<uint8_t>(pin);
    }
    static constexpr uint32_t base = 0x4005D000 + 0x000;
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
