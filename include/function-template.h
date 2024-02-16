#include <stdint.h>

template<int P>
class FR {
    public:
    static const int x = P + 10;
};

template<uint32_t P, uint32_t Q>
class FRF {
    public:
    void operator=(bool onoff) const {
        if (onoff) {
            *(volatile uint32_t*)P |= Q;
        } else {
            *(volatile uint32_t*)P &= ~ Q;
        }
    }
};

template<uint32_t P, uint32_t Q>
class FDP : public FR<P> {
    public:
    FRF<P + 1, Q> direction1;
    FRF<P + 2, Q> direction2;
    FRF<P + 3, Q> direction3;
    FRF<P + 4, Q> direction4;
    FRF<P + 5, Q> direction5;
    FRF<P + 6, Q> direction6;
};

template<uint32_t P, uint32_t Q>
void s(const FDP<P, Q> & dp) {
    dp.direction1 = true;
    dp.direction2 = true;
    dp.direction3 = true;
    dp.direction4 = true;
    dp.direction5 = true;
    dp.direction6 = true;
}

int function_template() {
    FDP<0x40051000, 2> dp12;
    FDP<0x4005D000, 3> dp23;

    s(dp12);
    s(dp23);

    return 0;
}
