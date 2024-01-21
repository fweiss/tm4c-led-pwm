#pragma once

#include <stdint.h>

struct RegisterAccess {
    static void clearbits(uint32_t registerAddress, uint32_t bits) {
        *(volatile uint32_t*)registerAddress &= ~ bits;
    }
    static void setbits(uint32_t registerAddress, uint32_t bits) {
        *(volatile uint32_t*)registerAddress |= bits;
    }
    static void write(uint32_t registerAddress, uint32_t value) {
        *(volatile uint32_t*)registerAddress = value;
    }
    static uint32_t read(uint32_t registerAddress) {
        return *(volatile uint32_t*)registerAddress;
    }
};
// definition: RegisterBit<0x3000, 4> bit
// usage: bit = true
template<uint32_t registerAddress, uint8_t bitNumber>
struct RegisterBit : RegisterAccess {
    void operator=(bool onoff) {
        const uint32_t bitmask = (1 << bitNumber);
        if (onoff) {
            setbits(registerAddress, bitmask);
        } else {
            clearbits(registerAddress, bitmask);
        }
    }
};
template<uint32_t address, uint8_t shift, uint8_t width>
struct RegisterMasked : RegisterAccess {
    const uint32_t mask = (1 << width) - 1;
    void operator=(uint32_t value) {
        uint32_t temp = read(address) & ~(mask << shift);
        temp |= ((value & mask) << shift);
        write(address, temp);
    }
};
template<uint32_t baseAddress, uint32_t addressOffset, uint8_t timerIndex>
struct RegisterTimer : RegisterAccess {
    void operator=(int32_t value) {
        write(baseAddress + addressOffset + 4 * timerIndex, value);
    }
};

enum class PortBase {
    A = 0x40004000,
    B = 0x40005000,
    C = 0x40006000,
    D = 0x40007000,
    E = 0x40024000,
    F = 0x40025000,
};

enum class PinIndex {
    _0 = 0x01,
    _1 = 0x02,
    _2 = 0x04,
    _3 = 0x08,
    _4 = 0x10,
    _5 = 0x20,
    _6 = 0x40,
    _7 = 0x80,
};

// six clocks
// - USB
// - PWM
// - UART
// - SYSTEM
// - SSI baud
// - ADC
// TM4C123G main oscillator 16 MHz
struct Clock : RegisterAccess {
    // PWM system clock optional divider (via RCC)
    // USB main + xtal + pll divide by 8
    static const uint8_t PLL_DIV_80MHZ 	= 5;

    // 	rcc_sysclk_config(OSCSRC_MOSC, XTAL_16M, PLL_DIV_80MHZ);
    void blinkClockSetup() {
	    rcc_pll_bypass_enable();
        // if OSCSRC_MOSC
        rcc_enable_main_osc();
        rcc_enable_rcc2(); // RCC2 overried RCC
        rcc_configure_xtal(XTAL_16M);
        rcc_set_osc_source((enum osc_src)OSCSRC_MOSC);

        // pll div != 0
        // system clock
        rcc_pll_on();
		rcc_change_pll_divisor(PLL_DIV_80MHZ);
        // PLL_DIV_80MHZ = 5, /6
    }
    void setupSystemClock() {
        // source either main or pll
        // bypass used for glitch-free changes
        // div400 divides pll by 2
        // final optional sysdiv
        // either 12.5 - 66.67 Mhz, or clock source / 1..16
    }
    // void setupPwmClock() {
    //     // system clock + divisor
    // }
};

// use this template to define a port
// each gpio port has an index 0-5
// each gpio port has a base address, either abp or ahp
// currently, abp ignored, ahp used
// somne ports have restrictions on which pins can be used
// template <uint8_t Index, uint32_t gpioPortBase>
class Port {
public:
    Port(uint32_t index_, uint32_t gpioPortBase_) : 
        index(index_), 
        gpioPortBase(gpioPortBase_),
        pin1(PinIndex::_1),
        pin2(PinIndex::_2),
        pin3(PinIndex::_3)
    {}
    // these are for GPIO module
    // other modules may have different registers, CAN, TimerBlock, I2C, ...
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

    const PinIndex pin1;
    const PinIndex pin2;
    const PinIndex pin3;

};

class DigitalPin {
public:
    DigitalPin(Port &port, PinIndex _pin) : 
        base(port.gpioPortBase), 
        pin(_pin),
        enableAlternateFunction(base, pin),
        portControl(base, pin)
    {}
    // DigitalPin& operator=(uint32_t value) {
    //     *(volatile uint32_t*)(data + (pinNumber() << 2)) = value;
    //     return *this;
    // }
    // operator uint32_t() const {
    //     return *(volatile uint32_t*)(data + (static_cast<uint32_t>(pin) << 2));
    // }
    DigitalPin& operator=(bool onOff) {
        *(volatile uint32_t*)(data + (pinNumber() << 2)) = onOff ? 0xff : 0x00;
        return *this;
    }
    operator bool() const {
        return *(volatile uint32_t*)(data + (pinNumber() << 2)) != 0;
    }
    // type of enable pin buts in lower 8 bits
    struct EnableAlternateFunction  : public RegisterAccess {
        EnableAlternateFunction(uint32_t base_, PinIndex pin_) : 
            xbase(base_),
            xpin(pin_)
        {}
        uint32_t xbase;
        PinIndex xpin;
        void operator=(bool onoff) {
            // uint32_t registerAddress = 0x4005D000 + 0x420; // GPIOAFSEL
            if (onoff) {
                setbits(xbase + 0x420, static_cast<uint8_t>(xpin)); // pin1
            } else {
                clearbits(xbase + 0x420, static_cast<uint8_t>(xpin)); // pin1
            }
        }
    };
    struct PinPortControl : public RegisterAccess { // GPIOPCTL
        PinPortControl(uint32_t base_, PinIndex pin_) :
            xbase(base_),
            xpin(pin_)
        {}
        uint32_t xbase;
        PinIndex xpin;
        const uint32_t registerAddress = 0x4005D000 + 0x52c; // depnds on port
        void operator=(uint8_t peripheralSignal) {
            // bridge
            uint8_t pini = __builtin_ctz((uint8_t)xpin);

            uint8_t shift = pini * 4; // depends on pin index (0..7) * 4
            uint32_t mask = 0x0f << shift;
            uint32_t shifted = peripheralSignal << shift;

            uint32_t temp = read(registerAddress);
            temp &= ~ mask; // clear field
            temp |= (shifted & mask); // set field
            write(registerAddress, temp);
        }
    };
    const uint32_t base;
    const PinIndex pin;

    EnableAlternateFunction enableAlternateFunction; // offset 0x420
    PinPortControl portControl; // offset 0x52c, packed 4 x 8
private:
    // const uint32_t base;
    // const PinIndex pin;
    uint8_t pinNumber() const {
        return static_cast<uint8_t>(pin);
    }
    // the following are offsets to various GPIO control registers
    // belonging to a particular port
    // in each register, the lower 8 bits correspond to one of
    // the 8 possible GPIOs in the  port
    // these bits can be ORed together to set multiple GPIOs
    const uint32_t data = base + 0x000; // data[7..0] address masking
    const uint32_t dir = base + 0x400; // bool[7..0]
    // interrupt sense 404 // bool[7..0]
    // interrupt both edges 408 // bool[7..0]
    // interrupt edge 40c // bool[7..0]
    // interrupt mask 410 // bool[7..0]
    // raw interrupt 414 // bool[7..0]
    // masked interrupt 418 // bool[7..0]
    // interrupt clear 41c // bool[7..0]
    const uint32_t afsel = base + 0x420; // bool[7..0]
    // additionally, GPIOPCTL for port sets the peripheral signal

    // drive 2 ma 500 // bool[7..0]
    // drive 4 ma 504
    // drive 8 ma 508
    // open drain 50c
    const uint32_t dr2r = base + 0x500;
    const uint32_t dr4r = base + 0x504;
    const uint32_t dr8r = base + 0x508;
    const uint32_t odr = base + 0x50C;

    const uint32_t pur = base + 0x510; // pullup bool[7..0]
    const uint32_t pdr = base + 0x514;
    const uint32_t den = base + 0x51C; // digital enable
    const uint32_t lock = base + 0x520; // data[31..0]
    const uint32_t cr = base + 0x524; //commit lock bool[7..0]
    const uint32_t amsel = base + 0x528; // analog select bool[7..0]
    const uint32_t pctl = base + 0x52C; // port control data[4][8]
    // 530 adc ocntrol bool[7..0]
    // 534 dma control bool[7..0]

    // fd0 perpheral id data[7..0] et al
    // feo more
    // ff0 more

};

enum class TimerBlockIndex {
    Block0, Block1, Block2, Block3, Block4, Block5
};

// Three classes of timer registers
// - global, bit per timer block - RCGCTIMER
// - per timer block - GPTMCFG, GPTMCTL[A,B]
// - per timer - GPTMTAMR, GPTMTBMR
template<TimerBlockIndex blockIndex>
struct TimerBlock : public RegisterAccess {
    // setup base addresses
    static constexpr uint32_t timerModuleBaseAddress = 0x40030000;
    static constexpr uint32_t blockAddressOffset = static_cast<uint32_t>(blockIndex) * 0x1000;
    static constexpr uint32_t blockBaseAddress = timerModuleBaseAddress + blockAddressOffset;
    static constexpr uint32_t systemControlBaseAddress = 0x400FE000;

    RegisterBit<systemControlBaseAddress + 0x604, static_cast<uint8_t>(blockIndex)> clockEnable; // RCGCTIMER
    RegisterMasked<blockBaseAddress, 0, 3> configuration; // GPTMCFG

    // template for A/B timer API
    // timerIndex selects bit and register offsets for the A/B timers
    // timerA=0, timerB=1
    template<uint8_t timerIndex>
    struct Timer {
        static const uint32_t enableOffset = timerIndex * 8;
        RegisterBit<blockBaseAddress + 0x00c, enableOffset> enable; // GPTMCTL.[TAEN,TBEN];
        static const uint8_t invertOutputShift = 6 + 8 * timerIndex;
        RegisterBit<blockBaseAddress + 0x00c, invertOutputShift> invertOutput; // GPTMCTL.TBPWML

        RegisterTimer<blockBaseAddress, 0x028, timerIndex> interval; // GPTMTnILR
        RegisterTimer<blockBaseAddress, 0x030, timerIndex> match; // GPTMTnMATCHR
        RegisterTimer<blockBaseAddress, 0x038, timerIndex> intervalPrescale; // GPTMTnPR
        RegisterTimer<blockBaseAddress, 0x040, timerIndex> matchPrescale; // GPTMTnPMR

        void setPwmMode() {
            const uint32_t timerOffset= 0x004 + 4 * timerIndex;
            const uint32_t modeRegister = blockBaseAddress + timerOffset; // GPTMTnMR
            const uint32_t taams = (1 << 3); // PWM mode
            const uint32_t tacmr = (0 << 2); // 0 = edge count mode
            const uint32_t tamr  = (2 << 0); // 2 = periodic
            // would be nice to use RegisterMasked
            write(modeRegister, taams | tacmr | tamr);
        }
    };

    Timer<0> timerA;
    Timer<1> timerB;
};
// wish there was a DRY ay to do this
// but heck, that is not exposed in the API
struct TimerBlocks {
    // static TimerBlock<0x40030000, 0> block0;
    // static TimerBlock<0x40031000, 1> block1;
    // static TimerBlock<0x40032000, 2> block2;
    // static TimerBlock<0x40033000, 3> block3;
    // static TimerBlock<0x40034000, 4> block4;
    // static TimerBlock<0x40035000, 5> block5;

    static TimerBlock<TimerBlockIndex::Block0> block0;
    static TimerBlock<TimerBlockIndex::Block1> block1;
    static TimerBlock<TimerBlockIndex::Block2> block2;
    static TimerBlock<TimerBlockIndex::Block3> block3;
    static TimerBlock<TimerBlockIndex::Block4> block4;
    static TimerBlock<TimerBlockIndex::Block5> block5;

};
TimerBlock<TimerBlockIndex::Block0> TimerBlocks::block0;
TimerBlock<TimerBlockIndex::Block1> TimerBlocks::block1;

// for passing Timer to a function template, use template alias
template<TimerBlockIndex timerBlockIndex, uint8_t timerIndex>
using TimerBlockTimer = TimerBlock<timerBlockIndex>::Timer<timerIndex>;
