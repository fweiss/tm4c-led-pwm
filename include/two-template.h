#include "GPIO.h"

// old register bit class template
template<uint32_t registerAddress, uint8_t pinIndex>
struct RBT : RegisterAccess {
    void operator=(bool onoff) {
        const uint32_t bitmask = (1 << pinIndex);
        if (onoff) {
            setbits(registerAddress, bitmask);
        } else {
            clearbits(registerAddress, bitmask);
        }       
    }
};

// old digital pin class template
template<uint32_t portBase, uint8_t pinIndex>
struct DPT {
    RBT<portBase + 0x400, pinIndex> directionOutput;
};

// using old digital pin class template
// cannot pass digital pin function argument
// would need function template
void w_template() {
    const uint32_t portBase = 0x4003d000;
    const uint8_t pinIndex = 3;

    DPT<portBase, pinIndex> dpt;
    dpt.directionOutput = true;
}

// ====================

// new register bit, but we'd like to use the same template
struct RB : RegisterAccess {
    RB(uint32_t registerAddress_, uint8_t pin_) : registerAddress(registerAddress_), pin(pin_) {}
    const uint32_t registerAddress;
    const uint8_t pin;

    void operator=(bool onoff) {
        const uint32_t bitmask = (1 << pin);
        if (onoff) {
            setbits(registerAddress, bitmask);
        } else {
            clearbits(registerAddress, bitmask);
        }
    }
};

// non-template register bit
struct RB2 : RegisterAccess {
    RB2(const uint32_t registerAddress_, const uint8_t pinIndex) :
        registerAddress(registerAddress_), pin(pinIndex) {}
    const uint32_t registerAddress;
    const uint8_t pin;
    void operator=(bool onoff) {
        const uint32_t bitmask = (1 << pin);
        if (onoff) {
            setbits(registerAddress, bitmask);
        } else {
            clearbits(registerAddress, bitmask);
        }
    }
};

// new port pin that can be passed to a function
struct DP {
    DP(uint32_t port_, uint8_t pin_) : pinIndex(pin_) {
        // this->directionOutput(1, 2);
    }
    const uint32_t x = 0x999;
    const uint8_t pinIndex;
    // a way to get around the "most vexing parse"
    // supposing compiler elides the copy constructor
    RB2 directionOutput = RB2(x, pinIndex);

    // like to use a class template here
    // RBT<portBase + 0x400, 2> directionOutput;
    // RB2 directionOutput(x + 0x400, pinIndex);
    // RB2 &directionOutput = RB2(1, 2);
    // RB2(1, 2) directionOutput;
};

// using a template for digital pin
template<uint32_t portBase, uint8_t pinIndex>
struct DPTT {
    DPTT() : dp(portBase, pinIndex) {}
    DP dp;
    // RegisterBit<portBase + 0x400, pinIndex> directionOutput;
;
};

// this would compose without a function template
void wo_notemplate() {
    const uint32_t port = 0x4003d000;
    const uint8_t pin = 3;
    DP dp(port, pin);

    dp.directionOutput = true;
    // the above is the non-template way
    // dp is an object, while DigitalPin is an enclosed class template
}
