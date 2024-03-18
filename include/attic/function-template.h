#include <stdint.h>

namespace X {

template<int P>
class FR {
    public:
    static const int x = P + 10;
};

template<uint32_t registerAddress, uint32_t Q>
class RegisterBit {
    public:
    void operator=(bool onoff) const {
        if (onoff) {
            *(volatile uint32_t*)registerAddress |= Q;
        } else {
            *(volatile uint32_t*)registerAddress &= ~ Q;
        }
    }
};

enum class PortIndex {
    PortA,
};

// would make sense to use uint32_t* here, 
// but spec shows offsets as uint8_t*
template<PortIndex portIndex>
struct Port {
    static constexpr uint32_t origin = 0x400e000;
    static constexpr uint32_t stride = 0x1000;
    static constexpr uint32_t portBaseAddress = origin + (stride * static_cast<uint32_t>(portIndex));

    static constexpr uint32_t GPIODEN = portBaseAddress + 0x404;
};

struct GOO {
    static constexpr uint32_t GPIODEN = 0x404;
};

// digital pin
// has coordinates portIndex and pinIndex
// defines the registers and bitfields that configure and control the GPIO pin
template<PortIndex portIndex, uint8_t pinIndex>
struct DigitalPin {
    static Port<portIndex> P;

    // desired, but GOPIDEN undefined
    // works with base class GOO
    // static FRF<GPIODEN, pinIndex> direction;

    // possible, not too wordy
    static RegisterBit<P.GPIODEN, pinIndex> direction;

    // works, but wordy
    // static FRF<FP<portIndex>::GPIODEN, pinIndex> direction;
};

template<PortIndex portIndex, uint8_t pinIndex>
void setupLed(DigitalPin<portIndex, pinIndex> dp) {
    dp.direction = true;
}

int function_template() {
    const PortIndex portIndex = PortIndex::PortA;
    const uint8_t pinIndex = 3;
    DigitalPin<portIndex, pinIndex> dp99;

    setupLed(dp99);

    return 0;
}

} // namespace
