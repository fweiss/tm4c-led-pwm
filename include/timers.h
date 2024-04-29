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

// Using partial template specialization here to map
// generic API registers, such as "interval", to specific registers,
// such as "GPTMTAILR" and "GPTMTBILR", based on the TimerIndex template parameter.
// This does create two separate template classes, however since they are
// static, the optimizer collapses the API calls into inline code.
// Despite this code being quite un-DRY, the alternatives did not
// offer meaningful simplification.
template<TimerBlockIndex timerBlockIndex, TimerIndex timerIndex>
struct Timer {
};

template<TimerBlockIndex timerBlockIndex>
struct Timer<timerBlockIndex, TimerIndex::TimerA> : Register {
    static const TimerRegisters<timerBlockIndex> R;

    RegisterBit<R.GPTMCTL, 0> enable; // TAEN
    RegisterBit<R.GPTMCTL, 6> invertOutput; // TAPWML

    Register32<R.GPTMTAILR> interval;
    Register32<R.GPTMTAMATCHR> match;
    Register32<R.GPTMTAPR> intervalPrescale;
    Register32<R.GPTMTAPMR> matchPrescale;
};

template<TimerBlockIndex timerBlockIndexEnum>
struct Timer<timerBlockIndexEnum, TimerIndex::TimerB> : Register, RegisterAccess {
    static constexpr uint32_t timerBlockIndex = static_cast<uint32_t>(timerBlockIndexEnum);
    static const TimerRegisters<timerBlockIndexEnum> R;

    RegisterBit<R.GPTMCTL, 8> enable; // TBEN
    RegisterBit<R.GPTMCTL, 14> invertOutput; // TBPWML

    RegisterField<R.GPTMTBMR, 3, 1> alternateModeSelect; // TnAMS PWM mode
    RegisterField<R.GPTMTBMR, 2, 1> captureMode; // TnCMR edge count mode
    RegisterField<R.GPTMTBMR, 0, 2> timerMode; // TnMR 2=periodic

    Register32<R.GPTMTBILR> interval;
    Register32<R.GPTMTBMATCHR> match;
    Register32<R.GPTMTBPR> intervalPrescale;
    Register32<R.GPTMTBPMR> matchPrescale;

    RegisterBit<R.GPTMRIS, 8> timeoutRawInterrupt; //  TBTORIS

// 8=timeout, 11=match
    RegisterBit<R.GPTMIMR, 8> timeoutInterruptMask;
    RegisterBit<R.GPTMICR, 8> timeoutInterruptClear;

    RegisterBit<R.GPTMTBMR, 5> matchInterruptEnable; // TAMIE
    RegisterBit<R.GPTMIMR, 9> pwmInterruptEnable; // TAPWMIE

    // map timer block index and timer index to interrupt number
    // 0A=19, 1A=21, 2A=23, 3A=35, 4A=70, 5A=92
    // see table 2-9
    // fixme extract function
    static constexpr uint32_t interruptNumber
        = (timerBlockIndex < 3 ? 19 + 2 * timerBlockIndex 
        : timerBlockIndex < 5 ? 35 + 35 * (timerBlockIndex - 3)
        : 92) + static_cast<uint32_t>(TimerIndex::TimerB);
    Interrupt<interruptNumber> interrupt;
};

template<TimerBlockIndex timerBlockIndex, TimerIndex timerIndex>
struct PWMTimer : Timer<timerBlockIndex, timerIndex>, Register {
    static constexpr TimerRegisters<timerBlockIndex> R{};

    // in PWM mode, prescaler is MSB of count
    RegisterSpan<R.GPTMTBILR, 16, R.GPTMTBPR, 8> pwmInterval;
    RegisterSpan<R.GPTMTBMATCHR, 16, R.GPTMTBPMR, 8> pwmMatch;
};
