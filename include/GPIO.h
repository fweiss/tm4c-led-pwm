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

constexpr uint32_t PortF = 0x4005D000;
template<uint32_t Port>
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
