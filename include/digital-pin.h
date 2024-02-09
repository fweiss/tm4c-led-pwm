#include "GPIO.h"

// Define a bit in a register that can be accessed as a boolean.
// Use ``operator=()`` to set and ``operator bool()`` to read.
//
// See also RField
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

// define the data sheet mnemonics to facilite cross reference
struct DPRegisters {
    DPRegisters(uint32_t portBase_) : portBase(portBase_) {}
    const uint32_t portBase;

    const uint32_t GPIODATA = portBase + 0x000; // note special addressing mode
    const uint32_t GPIODIR = portBase + 0x400;
    // 0x404-0x41c interrupt
    const uint32_t GPIOAFSEL = portBase + 0x420;
    const uint32_t GPIODR2R = portBase + 0x500;
    const uint32_t GPIOODR = portBase + 0x50C;
    const uint32_t GPIOPUR = portBase + 0x510;
    const uint32_t GPIOPDR = portBase + 0x514;
    const uint32_t GPIODEN = portBase + 0x51C;
    const uint32_t GPIOPCTL = portBase + 0x52C;
};

// digital pin that can be passed to a function
struct DP : DPRegisters {
    DP(uint32_t portBase_, uint8_t pin_) : DPRegisters(portBase), portBase(portBase_), pinIndex(pin_) {}
    const uint32_t portBase;
    const uint8_t pinIndex;

    const uint32_t data = portBase + 0x000;
    const uint32_t pinBits = (1 << pinIndex);

    // the behavior is simply a bool value
    // bit-banding on the data register
    void operator=(bool onOff) {
        *(volatile uint32_t*)(data + (pinBits << 2)) = onOff ? 0xff : 0x00;
    }
    operator bool() const {
        return *(volatile uint32_t*)(data + (pinBits << 2)) != 0;
    }

    // note use of {} to avoid Most Vexing Parse
    RBit    directionOutput         {GPIODIR, pinIndex};
    RBit    digitalEnable           {GPIODEN, pinIndex};
    RBit    alternateFunctionEnable {GPIOAFSEL, pinIndex};
	RBit    pullUpEnable            {GPIOPUR, pinIndex};
	RBit    pullDownEnable          {GPIOPDR, pinIndex};
	RBit    openDrainEnable         {GPIOODR, pinIndex};
	RBit    drive2mA                {GPIODR2R, pinIndex};

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
