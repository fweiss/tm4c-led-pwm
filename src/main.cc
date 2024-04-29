#include "GPIO.h"
#include "timers.h"
#include "helpers.h"

const int FLASH_DELAY = 8000000;

// initially used PB1/T2CPP1 to  debug, but no interrupt with PWM mode
void setupTimer2BInterrupt() {
    TimerBlock<TimerBlockIndex::Timer2> timerBlock;
    Timer<TimerBlockIndex::Timer2, TimerIndex::TimerB> timer;

    timerBlock.clockEnable = true;
    timerBlock.configuration = TimerBlockConfiguration::SingleWide;

    // 0 = capture compare 1 = pwm
    // pwm needed t see the output on the pin
    // no interrupt when in pwm mode
    timer.alternateModeSelect = 0; // TnAMS PWM mode
    timer.captureMode = 0; // TnCMR edge count mode
    timer.timerMode = 2; // TnMR 2=periodic

    // only 16 bit
    // 0xff00 = 1.64 ms, 0x8000 = 0.82 ms
    timer.interval = 0x8000;
    timer.intervalPrescale = 0x001;

    timer.timeoutInterruptMask = true;
    timer.enable = true;

    timer.interrupt.enable = true;
}

// for now, bite the bullet and hand code this instead of lambda
extern "C" void timer2b_isr(void) {
    Timer<TimerBlockIndex::Timer2, TimerIndex::TimerB> timer;
    timer.timeoutInterruptClear = true;
    DigitalPin<PortIndex::PortF, PinIndex::Pin2> blueLed;
    blueLed = !blueLed; // effective PWM 50%
}

int main(void) {

    Clock clocks;
    clocks.blinkClockSetup();

    Port<PortIndex::PortF> port;
    port.highPerformanceBusEnable = true;
    port.clockEnable = true;
    // require 3 system clock delay after peripheral clock enable
    delay(3);

    DigitalPin<PortIndex::PortF, PinIndex::Pin1> redLed;
    DigitalPin<PortIndex::PortF, PinIndex::Pin2> blueLed;
    DigitalPin<PortIndex::PortF, PinIndex::Pin3> greenLed;

    setupOutputLed(redLed);
    setupOutputLed(blueLed);
    setupOutputLed(greenLed);

#define EXPERIMENT_2
    // r = PF1 T0CCP1
    // b = PF2 T1CCP0
    // g = PF3 T1CCP1

#ifdef EXPERIMENT_1
    // block 0 and 1, timer B
    // flash blue dim red/green
    auto &mainLed = blueLed;
    auto &pwmLed = greenLed;
    TimerBlock<TimerBlockIndex::Timer1> timerBlock;
    PWMTimer<TimerBlockIndex::Timer1, TimerIndex::TimerB> timer;
#endif

#ifdef EXPERIMENT_2
    // block 1 timer 0/1 experiment
    // flash red dim green/blue
    auto &mainLed = redLed;
    auto &pwmLed = greenLed;
    TimerBlock<TimerBlockIndex::Timer1> timerBlock;
    PWMTimer<TimerBlockIndex::Timer1, TimerIndex::TimerB> timer;

#endif

    timerBlock.clockEnable = true; // todo delay
    timerBlock.configuration = TimerBlockConfiguration::SingleWide;
    setupPwm(timer);

    timer.pwmInterval = 255 * 65536;
    timer.pwmMatch = 42 * 65536;

    pwmLed.alternateFunctionEnable = true;
    pwmLed.digitalFunction = DigitalFunction::T0CPP0;

    setupTimer2BInterrupt();

    while (true) {
        mainLed = true;
        delay(FLASH_DELAY);
        mainLed = false;
        delay(FLASH_DELAY);

        timer2BDebug();

    }

    return 0;
}
