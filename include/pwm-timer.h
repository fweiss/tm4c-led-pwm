static void delay(uint32_t cycles) {
	for (uint32_t i = 0; i < cycles; i++) {
		__asm__("nop");
    }
}

// clock
// want about 1 Hz PWM timer
// PWM divisor 16/32 bit, 32/64 bit
// system clock 80 MHz (400 / 5)
// 65,000 * 1230 ~ 80,000,000
// so currrently with 30,000 interval, about 2.7 kHz PMW

// section 11.3.2.5, 11.4.5
// 11.2 gpio pin output, GPIOAFSEL, GPIOPCTL (code 7)
// r = F1 T0CCP1
// g = F2 T1CCP0
// b = F3 T1CCP1
// todo check if this causes specialization of the function
template<TimerBlockIndex timerBlockIndex, uint8_t timerIndex>
void setupPwm(TimerBlockTimer<timerBlockIndex, timerIndex> &timer, DigitalPin &pin) {

	// auto &timer = timerBlock.timerB;
	timer.enable = false;
	delay(7); // empirically need at least 7 ?
	timer.setPwmMode(); //TAAMS, TACMR, TAMR
	timer.invertOutput = true; // debug

	timer.intervalPrescale = 255; // 8-bit or 16-bit
	timer.interval = 65535; // 16-bit
	timer.matchPrescale = 127; // 8-bit or 16-bit
	timer.match = 65535;

	// GPTMCTL.TnEVENT if interrupts are used
	// GPTMTnMR.TnPWMIE
	// portf.pin1.driveSelect = 2, 4, 8 GPIODR8R - done in main()

	pin.enableAlternateFunction = true;
	const uint8_t digitalFunctionTimerCCP = 7;
	pin.portControl = digitalFunctionTimerCCP;
	
	timer.enable = true;
	// GPTMTnILR to change period
}
