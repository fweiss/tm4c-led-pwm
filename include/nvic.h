#pragma once

#include "addresses.h"
#include "registers.h"

// this should be a member in each peripheral that has interrupts
// the peripheral computes the interrupt number
// see table 2-9
template<uint32_t interruptNumber>
struct Interrupt : Register {
    static constexpr NVICRegisters R{};

    RegisterSpanBit<R.EN0, R.EN4, interruptNumber> enable;
    // disable, priority, active, pending
};
