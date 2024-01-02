// chapter 20
void setupPwm(GPIOx &pin) {
	// setup a timer that outputs pwm to the given pin
	long RCGC0;
	RCGC0 = 0b00100000; // enable pwm clock

	long RCGC2; // enable gpio module clock

	long GPIOAFSEL; // enable pin for alternate function

	long GPIOPCTL; // assign pwm signals to appropriate pins

	long rcc; // USEPWMDIV and divide by 2

	long PWM0CTL; // countdown mode, immediate updates
	long PWM0GENA;
	long PWM0GENB;

	long PWM0LOAD; // pwm frequency

	long PWM0CMPA; // pulse width
	long PWM0CMPB;

	PWM0CTL; // start timers

	long PWMENABLE; // enable pwm output
}
