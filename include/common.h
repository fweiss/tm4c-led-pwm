// common enums, classes, and functions
// that are used in multiple places

#pragma once

enum class PortIndex : uint32_t {
    PortA = 0,
    PortB = 1,
    PortC = 2,
    PortD = 3,
    PortE = 4,
    PortF = 5,
};

enum class PinIndex {
    Pin0 = 0, Pin1, Pin2, Pin3, Pin4, Pin5, Pin6
};

// flatten the enum for the 16/32 bit and 32/64 bit timers
// since the register addesses are roughly sequential [11.5]
enum class TimerBlockIndex {
    Timer0 = 0, Timer1, Timer2, Timer3, Timer4, Timer5,
    WTimer0, WTimer1, WTimer2, WTimer3, WTimer4, WTimer5, 
};

enum class TimerIndex {
    TimerA = 0, TimerB
};

// RCC.XTAL
// there are restrictions on the crystal value for USB operation
enum class CrystalValue {
    XTAL_16M = 0x15,
    XTAL_25M = 0x1A,
};

// RCC2.OSCSRC
enum class OscillatorSource2 {
    MOSC        = 0, // main oscillator
    PIOSC       = 1, // precision internal oscillator
    PIOSC_DIV4  = 2, // precision internal oscillator / 4
    LFIOSC      = 3, // low frequency internal oscillator
};

// what we're trying to do here is to make the digital function
// a type-safe enum that can be used in the DigitalPin class
// but since the actual values are not sequential, we can't use
// a simple enum.  Instead, we use a class with a nested enum.
class DigitalFunction {
public:
    enum class Codes {
        GPIO        = 0,
        TimerCCP    = 7, 
    };
    static constexpr auto GPIO      = Codes::GPIO;
    static constexpr auto T0CPP0    = Codes::TimerCCP;
    static constexpr auto T2CPP1    = Codes::TimerCCP;
};

enum class TimerBlockConfiguration {
    DoubleWide      = 0x00,    // 32/64 bit timers
    RealTimeClock   = 0x01,    // real-time clock
    SingleWide      = 0x04,    // 16/32 bit timers
};
