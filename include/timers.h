/**
 * API for the gneneral purpose timers module.
*/
#pragma once

#include "common.h"
#include "registers.h"
#include "addresses.h"
#include "nvic.h"

// Three classes of timer registers
// - global, bit per timer block - RCGCTIMER
// - per timer block - GPTMCFG, GPTMCTL[A,B]
// - per timer - GPTMTAMR, GPTMTBMR
template<TimerBlockIndex blockIndexEnum>
struct TimerBlock : public Register {
    static constexpr SystemControleRegisters S{};
    static constexpr TimerRegisters<blockIndexEnum> R{};
    static constexpr uint8_t blockIndex = static_cast<uint8_t>(blockIndexEnum);

    RegisterBit<S.RCGCTIMER, blockIndex>    clockEnable;
    RegisterFieldType<R.GPTMCFG, 0, 3, TimerBlockConfiguration>
                                            configuration;
};

// the timer registers are split into two groups, A and B
// the data structure is a bit irregular
// many registers are paired, such as GPTMTAMR and GPTMTBMR
// in the datasheet they are generically referred to as GPTMTnMR
// but to maintain a consistent way to look up in the datasheet
// names such as GPTMTAMR and GPTMTBMR are preferred
// in other cases, such as GPTMCTL, two bits are used, one for each timer
//
// using partial template specialization was tried, but it turned out
// to have too much code duplication
//
// instead a function template, AB() is used to select the correct register
// or bit depending on the timer index
// this makes the code a bit more verbose, but it is more DRY
template<TimerBlockIndex timerBlockIndexEnum, TimerIndex timerIndex>
struct Timer : Register, RegisterAccess {
    static constexpr uint32_t timerBlockIndex = static_cast<uint32_t>(timerBlockIndexEnum);
    static const TimerRegisters<timerBlockIndexEnum> R;

    // AB(a, b) returns either a or b based on the timer index
    template<typename T>
    static constexpr T AB(T a, T b) {
        return (timerIndex == TimerIndex::TimerA) ? a : b;
    }

    RegisterBit<R.GPTMCTL, AB(0, 8)> enable; // TBEN
    RegisterBit<R.GPTMCTL, AB(6, 14)> invertOutput; // TBPWML

    RegisterField<AB(R.GPTMTAMR, R.GPTMTBMR), 3, 1> alternateModeSelect; // TnAMS PWM mode
    RegisterField<AB(R.GPTMTAMR, R.GPTMTBMR), 2, 1> captureMode; // TnCMR edge count mode
    RegisterField<AB(R.GPTMTAMR, R.GPTMTBMR), 0, 2> timerMode; // TnMR 2=periodic

    Register32<AB(R.GPTMTAILR, R.GPTMTBILR)> interval;
    Register32<AB(R.GPTMTAMATCHR, R.GPTMTBMATCHR)> match;
    Register32<AB(R.GPTMTAPR, R.GPTMTBPR)> intervalPrescale;
    Register32<AB(R.GPTMTAPMR, R.GPTMTBPMR)> matchPrescale;

    RegisterBit<R.GPTMRIS, AB(0, 8)> timeoutRawInterrupt; //  TBTORIS

// 8=timeout, 11=match
    RegisterBit<R.GPTMIMR, AB(0, 8)> timeoutInterruptMask;
    RegisterBit<R.GPTMICR, AB(0, 8)> timeoutInterruptClear;

    RegisterBit<AB(R.GPTMTAMR, R.GPTMTBMR), 5> matchInterruptEnable; // TAMIE
    // Capture Mode Match Interrupt Mask CAMIM
    RegisterBit<R.GPTMIMR, AB(1, 9)> xpwmInterruptEnable; // TAPWMIE

    // map timer block index and timer index to interrupt number
    // 0A=19, 1A=21, 2A=23, 3A=35, 4A=70, 5A=92
    // see table 2-9
    // fixme extract function
    static constexpr uint32_t interruptNumber
        = (timerBlockIndex < 3 ? 19 + 2 * timerBlockIndex 
        : timerBlockIndex < 5 ? 35 + 35 * (timerBlockIndex - 3)
        : 92) + static_cast<uint32_t>(timerIndex);
    Interrupt<interruptNumber> interrupt;
};

// PWM mode is a special case of the timer
template<TimerBlockIndex timerBlockIndex, TimerIndex timerIndex>
struct PWMTimer : Timer<timerBlockIndex, timerIndex>, Register {
    static constexpr TimerRegisters<timerBlockIndex> R{};

    // AB(a, b) returns either a or b based on the timer index
    template<typename T>
    static constexpr T AB(T a, T b) {
        return (timerIndex == TimerIndex::TimerA) ? a : b;
    }


    // in PWM mode, prescaler is MSB of count
    RegisterSpan<AB(R.GPTMTAILR, R.GPTMTBILR), 16, AB(R.GPTMTAPR, R.GPTMTBPR), 8> pwmInterval;
    RegisterSpan<AB(R.GPTMTAMATCHR, R.GPTMTBMATCHR), 16, AB(R.GPTMTAPMR, R.GPTMTBPMR), 8> pwmMatch;
};
