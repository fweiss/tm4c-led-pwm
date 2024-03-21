#include "GPIO.h"
#include "timers.h"
#include "helpers.h"

const int FLASH_DELAY = 8000000;

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
    // timerBlock.configure = timerBlock.configure.TIMER_16_BIT;
    timerBlock.configuration = 4;
    setupPwm(timer);

    timer.pwmInterval = 255 * 65536;
    timer.pwmMatch = 42 * 65536;

    pwmLed.alternateFunctionEnable = true;
    const uint8_t digitalFunctionTimerCCP = 7;
    pwmLed.portMode = digitalFunctionTimerCCP;

    while (true) {
        mainLed = true;
        delay(FLASH_DELAY);
        mainLed = false;
        delay(FLASH_DELAY);
    }

    return 0;
}
