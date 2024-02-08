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

// non-template register bit
struct RBit : RegisterAccess {
    RBit(const uint32_t registerAddress_, const uint8_t pinIndex) :
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

// register field
struct RField : RegisterAccess {
    RField(uint32_t registerAddress, uint8_t offset, uint32_t width) :
        registerAddress_(registerAddress),
        width_(width),
        offset_(offset) {}
    const uint32_t registerAddress_;
    const uint32_t width_;
    const uint8_t offset_;

    // looks wordy, but optimized is just four instructions
    // LDR, AND, ORR, STR
    void operator=(uint32_t value) {
        const uint32_t mask = (1 << width_) - 1; // eg 2 -> 0x003
        uint32_t tmp = read(registerAddress_);
        tmp &= ~(mask << offset_);
        tmp |= (value & mask) << offset_;
        write(registerAddress_, tmp);
    }
};
// RB(x, y) = RField(x, y, 1)

// digital pin that can be passed to a function
struct DP {
    DP(uint32_t portBase_, uint8_t pin_) : portBase(portBase_), pinIndex(pin_) {}
    const uint32_t portBase;
    const uint8_t pinIndex;

    // note use of {} to avoid Most Vexing Parse
    RBit    directionOutput {portBase + 0x400, pinIndex};
    RField  portMode        {portBase + 0x404, pinIndex * 4, 4};
};


// this would compose without a function template
void wo_notemplate() {
    const uint32_t portBase = 0x4003d000;
    const uint8_t pinIndex = 4;
    DP dp(portBase, pinIndex);

    dp.directionOutput = true;
    dp.portMode = 4;
}
