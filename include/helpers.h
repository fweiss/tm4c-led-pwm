#pragma once

static void delay(uint32_t cycles) {
    for (uint32_t i = 0; i < cycles; i++) {
        __asm__("nop");
    }
}

template<PortIndex portIndex, PinIndex pinIndex>
void setupOutputLed(DigitalPin<portIndex, pinIndex> &ledPin) {
    // could streamline using or'ed pin bits
    ledPin.directionOutput = true;
    ledPin.digitalEnable = true;
    ledPin.alternateFunctionEnable = false;
    ledPin.pullUpEnable = false;
    ledPin.pullDownEnable = false;
    // output config
    ledPin.openDrainEnable = false;
    ledPin.drive2mA = true;
}

// clock
// want about 1 Hz PWM timer
// PWM divisor 16/32 bit, 32/64 bit
// system clock 80 MHz (400 / 5)
// 65,000 * 1230 ~ 80,000,000
// so currrently with 30,000 interval, about 2.7 kHz PMW

// section 11.3.2.5, 11.4.5
// 11.2 gpio pin output, GPIOAFSEL, GPIOPCTL (code 7)
// todo check if this causes specialization of the function
// actually specialization is moot, since it is inlined by the compiler
template<TimerBlockIndex timerBlockIndex, TimerIndex timerIndex>
void setupPwm(Timer<timerBlockIndex, timerIndex> &timer) {

    timer.enable = false;
    delay(7); // empirically need at least 7 ?

    // setup for PWM
    // could be flattened to one write
    timer.alternateModeSelect = 1; // TnAMS PWM mode
    timer.captureMode = 0; // TnCMR edge count mode
    timer.timerMode = 2; // TnMR 2=periodic

    // note that in non-invert, match is count down
    // at which point output is cleared
    // in invert, match is the duty cycle
    timer.invertOutput = true; // debug

    timer.enable = true;
}

void timer2BDebug() {
    __attribute__((unused))uint32_t r = RegisterAccess::read(0x00000098); // NVIC
    __attribute__((unused))uint32_t i = RegisterAccess::read(0xe000e300); // interrupt
    __attribute__((unused))uint32_t e = RegisterAccess::read(0xe000e100); // EN0
    constexpr uint32_t timerBase = 0x40032000;
    __attribute__((unused))uint32_t mmis = RegisterAccess::read(timerBase + 0x020); // GPTMMIS
    __attribute__((unused))uint32_t mris = RegisterAccess::read(timerBase + 0x01c); // GPTMRIS
    __attribute__((unused))uint32_t imr = RegisterAccess::read(timerBase + 0x018); // GPTMIMR mask
    __attribute__((unused))uint32_t tbr = RegisterAccess::read(timerBase + 0x04c); // GPTMTBR
    delay(1); // dummy for breakpoint

}
void timer1BDebug() {
    __attribute__((unused))uint32_t r = RegisterAccess::read(0x00000098); // NVIC
    __attribute__((unused))uint32_t i = RegisterAccess::read(0xe000e300); // interrupt
    __attribute__((unused))uint32_t e = RegisterAccess::read(0xe000e100); // EN0
    __attribute__((unused))uint32_t mmis = RegisterAccess::read(0x40031000 + 0x020); // GPTMMIS
    __attribute__((unused))uint32_t mris = RegisterAccess::read(0x40031000 + 0x01c); // GPTMRIS
    __attribute__((unused))uint32_t imr = RegisterAccess::read(0x40031000 + 0x018); // GPTMIMR
    delay(1); // dummy for breakpoint
}

