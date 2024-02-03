void foo() {
	struct RB : RegisterAccess {
		RB() : port(1), pin(3) {}
		// RB(uint32_t port_, uint8_t pin_) : port(port_), pin(pin_) {}
		RB(uint32_t port_, uint8_t pin_) : port(port_), pin(pin_) {}
		const uint32_t port;
		const uint8_t pin;
		void operator=(bool onoff) {
			const uint32_t bitmask = (1 << pin);
			if (onoff) {
				setbits(port, bitmask);
			} else {
				clearbits(port, bitmask);
			}
		}
	};
	struct DP {
		DP(uint32_t port_, uint8_t pin_) : 
			port(port_), 
			pin(pin_),
			directionOutput(pin_, port_) {}
		const uint32_t port;
		const uint8_t pin;
		RB directionOutput;
	};

	const uint32_t port = 0x4003d000;
	const uint8_t pin = 3;
	DP dp(port, pin);

	dp.directionOutput = true;
    // the above is the non-template way
    // dp is an object, while DigitalPin is an enclosed class template

}
