#pragma once

#include <stdint.h>

#include "common.h"
#include "addresses.h"
#include "registers.h"

// six clocks
// - USB
// - PWM
// - UART
// - SYSTEM
// - SSI baud
// - ADC
// TM4C123G main oscillator 16 MHz
struct Clock : Register, SystemControleRegisters {
    // PWM system clock optional divider (via RCC)
    // USB main + xtal + pll divide by 8
    static const uint8_t PLL_DIV_80MHZ 	= 2; // 400 MHz / (2 << 1) + 1 = 80 MHz

    RegisterField<RCC, 6, 5> xtalConfig; // aka xtal value, xtal freq, divisor
    RegisterBit<RCC, 0> mainOscillatorDisable;
    RegisterBit<RCC, 22> systemClockDividerEnable;
    RegisterFieldType<RCC, 6, 5, CrystalValue> xtalConfig2;

    RegisterBit<RCC2, 31> useRCC2;
    RegisterBit<RCC2, 11> bypassEnable;
    RegisterField<RCC2, 4, 3> oscillatorSource;
    RegisterFieldType<RCC2, 4, 3, OscillatorSource2> oscillatorSource2;
    RegisterBit<RCC2, 13> pllPowerDown;
    RegisterField<RCC2, 23, 6> systemClockDivisor2;
    RegisterField<RCC2, 22, 1> systemClockDivisor2LSB; // not bool in this case
    RegisterBit<RCC2, 30> use400Mhz;

    RegisterBit<PLLSTAT, 0> pllLock;

    // using main oscillator 16 MHz
    // using pll to get 80 MHz   
    void blinkClockSetup() {
        bypassEnable = true;
        mainOscillatorDisable = false;
        useRCC2 = true;

        xtalConfig2 = CrystalValue::XTAL_16M;

        oscillatorSource2 = OscillatorSource2::MOSC;

        pllPowerDown = false;

        // set system clock to 80 MHz
        // could combine the divisor and lsb into one field
        bypassEnable = true;  // redundant
        systemClockDividerEnable = true;
        use400Mhz = true;
        systemClockDivisor2 = PLL_DIV_80MHZ;
        systemClockDivisor2LSB = 0;
        while (pllLock == false); // wait for PLL lock
        bypassEnable = false;
    }
    
    void setupSystemClock() {
        // source either main or pll
        // bypass used for glitch-free changes
        // div400 divides pll by 2
        // final optional sysdiv
        // either 12.5 - 66.67 Mhz, or clock source / 1..16
    }
};

// use this template to define a port
// each gpio port has an index 0-5
// each gpio port has a base address, either abp or ahp
// currently, abp ignored, ahp used
// somne ports have restrictions on which pins can be used
template<PortIndex portIndexEnum>
struct Port : Register {
    static constexpr SystemControleRegisters Q{};
    static constexpr uint8_t portIndex = static_cast<uint8_t>(portIndexEnum);

    RegisterBit<Q.RCGCGPIO, portIndex> clockEnable;
    RegisterBit<Q.GPIOHBCTL, portIndex> highPerformanceBusEnable;
};

template<PortIndex portIndex, PinIndex pinIndexEnum>
struct DigitalPin : Register {
    static const PortRegisters<portIndex> Q;
    static constexpr uint8_t pinIndex = static_cast<uint8_t>(pinIndexEnum);
    static constexpr uint8_t pinBits = (1 << pinIndex); // needed for bit-banding

    // the behavior is simply a bool value
    // bit-banding on the data register
    void operator=(bool onOff) {
        *(volatile uint32_t*)(Q.GPIODATA + (pinBits << 2)) = onOff ? 0xff : 0x00;
    }
    operator bool() const {
        return *(volatile uint32_t*)(Q.GPIODATA + (pinBits << 2)) != 0;
    }

    RegisterBit<Q.GPIODIR, pinIndex>            directionOutput;
    RegisterBit<Q.GPIOAFSEL, pinIndex>          alternateFunctionEnable;
    RegisterBit<Q.GPIODR2R, pinIndex>           drive2mA;
    RegisterBit<Q.GPIOODR, pinIndex>            openDrainEnable;
    RegisterBit<Q.GPIOPUR, pinIndex>            pullUpEnable;
    RegisterBit<Q.GPIOPDR, pinIndex>            pullDownEnable;
    RegisterBit<Q.GPIODEN, pinIndex>            digitalEnable;
    RegisterField<Q.GPIOPCTL, 4 * pinIndex, 4>  portMode;

};
