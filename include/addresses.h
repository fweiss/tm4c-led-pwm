/**
 * Map the symbolic register names to addresses.
 * Match the symbols used in the datasheet https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * Define banks and offsets at compile time.
 * Use class templates that instatiate static constexpr classes/structs.
 */

#pragma once

#include <stdint.h>
#include "common.h"

struct SystemControleRegisters {
    static constexpr uint32_t base = 0x400FE000;

    // derived from the datasheet
    static constexpr uint32_t	DID0	= base +	0x000;
    static constexpr uint32_t	DID1	= base +	0x004;
    static constexpr uint32_t	PBORCTL	= base +	0x030;
    static constexpr uint32_t	RIS	= base +	0x050;
    static constexpr uint32_t	IMC	= base +	0x054;
    static constexpr uint32_t	MISC	= base +	0x058;
    static constexpr uint32_t	RESC	= base +	0x05C;
    static constexpr uint32_t	RCC	= base +	0x060;
    static constexpr uint32_t	GPIOHBCTL	= base +	0x06C;
    static constexpr uint32_t	RCC2	= base +	0x070;
    static constexpr uint32_t	MOSCCTL	= base +	0x07C;
    static constexpr uint32_t	DSLPCLKCFG	= base +	0x144;
    static constexpr uint32_t	SYSPROP	= base +	0x14C;
    static constexpr uint32_t	PIOSCCAL	= base +	0x150;
    static constexpr uint32_t	PIOSCSTAT	= base +	0x154;
    static constexpr uint32_t	PLLFREQ0	= base +	0x160;
    static constexpr uint32_t	PLLFREQ1	= base +	0x164;
    static constexpr uint32_t	PLLSTAT	= base +	0x168;
    static constexpr uint32_t	SLPPWRCFG	= base +	0x188;
    static constexpr uint32_t	DSLPPWRCFG	= base +	0x18C;
    static constexpr uint32_t	LDOSPCTL	= base +	0x1B4;
    static constexpr uint32_t	LDOSPCAL	= base +	0x1B8;
    static constexpr uint32_t	LDODPCTL	= base +	0x1BC;
    static constexpr uint32_t	LDODPCAL	= base +	0x1C0;
    static constexpr uint32_t	SDPMST	= base +	0x1CC;
    static constexpr uint32_t	PPWD	= base +	0x300;
    static constexpr uint32_t	PPTIMER	= base +	0x304;
    static constexpr uint32_t	PPGPIO	= base +	0x308;
    static constexpr uint32_t	PPDMA	= base +	0x30C;
    static constexpr uint32_t	PPHIB	= base +	0x314;
    static constexpr uint32_t	PPUART	= base +	0x318;
    static constexpr uint32_t	PPSSI	= base +	0x31C;
    static constexpr uint32_t	PPI2C	= base +	0x320;
    static constexpr uint32_t	PPUSB	= base +	0x328;
    static constexpr uint32_t	PPCAN	= base +	0x334;
    static constexpr uint32_t	PPADC	= base +	0x338;
    static constexpr uint32_t	PPACMP	= base +	0x33C;
    static constexpr uint32_t	PPPWM	= base +	0x340;
    static constexpr uint32_t	PPQEI	= base +	0x344;
    static constexpr uint32_t	PPEEPROM	= base +	0x358;
    static constexpr uint32_t	PPWTIMER	= base +	0x35C;
    static constexpr uint32_t	SRWD	= base +	0x500;
    static constexpr uint32_t	SRTIMER	= base +	0x504;
    static constexpr uint32_t	SRGPIO	= base +	0x508;
    static constexpr uint32_t	SRDMA	= base +	0x50C;
    static constexpr uint32_t	SRHIB	= base +	0x514;
    static constexpr uint32_t	SRUART	= base +	0x518;
    static constexpr uint32_t	SRSSI	= base +	0x51C;
    static constexpr uint32_t	SRI2C	= base +	0x520;
    static constexpr uint32_t	SRUSB	= base +	0x528;
    static constexpr uint32_t	SRCAN	= base +	0x534;
    static constexpr uint32_t	SRADC	= base +	0x538;
    static constexpr uint32_t	SRACMP	= base +	0x53C;
    static constexpr uint32_t	SRPWM	= base +	0x540;
    static constexpr uint32_t	SRQEI	= base +	0x544;
    static constexpr uint32_t	SREEPROM	= base +	0x558;
    static constexpr uint32_t	SRWTIMER	= base +	0x55C;
    static constexpr uint32_t	RCGCWD	= base +	0x600;
    static constexpr uint32_t	RCGCTIMER	= base +	0x604;
    static constexpr uint32_t	RCGCGPIO	= base +	0x608;
    static constexpr uint32_t	RCGCDMA	= base +	0x60C;
    static constexpr uint32_t	RCGCHIB	= base +	0x614;
    static constexpr uint32_t	RCGCUART	= base +	0x618;
    static constexpr uint32_t	RCGCSSI	= base +	0x61C;
    static constexpr uint32_t	RCGCI2C	= base +	0x620;
    static constexpr uint32_t	RCGCUSB	= base +	0x628;
    static constexpr uint32_t	RCGCCAN	= base +	0x634;
    static constexpr uint32_t	RCGCADC	= base +	0x638;
    static constexpr uint32_t	RCGCACMP	= base +	0x63C;
    static constexpr uint32_t	RCGCPWM	= base +	0x640;
    static constexpr uint32_t	RCGCQEI	= base +	0x644;
    static constexpr uint32_t	RCGCEEPROM	= base +	0x658;
    static constexpr uint32_t	RCGCWTIMER	= base +	0x65C;
    static constexpr uint32_t	SCGCWD	= base +	0x700;
    static constexpr uint32_t	SCGCTIMER	= base +	0x704;
    static constexpr uint32_t	SCGCGPIO	= base +	0x708;
    static constexpr uint32_t	SCGCDMA	= base +	0x70C;
    static constexpr uint32_t	SCGCHIB	= base +	0x714;
    static constexpr uint32_t	SCGCUART	= base +	0x718;
    static constexpr uint32_t	SCGCSSI	= base +	0x71C;
    static constexpr uint32_t	SCGCI2C	= base +	0x720;
    static constexpr uint32_t	SCGCUSB	= base +	0x728;
    static constexpr uint32_t	SCGCCAN	= base +	0x734;
    static constexpr uint32_t	SCGCADC	= base +	0x738;
    static constexpr uint32_t	SCGCACMP	= base +	0x73C;
    static constexpr uint32_t	SCGCPWM	= base +	0x740;
    static constexpr uint32_t	SCGCQEI	= base +	0x744;
    static constexpr uint32_t	SCGCEEPROM	= base +	0x758;
    static constexpr uint32_t	SCGCWTIMER	= base +	0x75C;
    static constexpr uint32_t	DCGCWD	= base +	0x800;
    static constexpr uint32_t	DCGCTIMER	= base +	0x804;
    static constexpr uint32_t	DCGCGPIO	= base +	0x808;
    static constexpr uint32_t	DCGCDMA	= base +	0x80C;
    static constexpr uint32_t	DCGCHIB	= base +	0x814;
    static constexpr uint32_t	DCGCUART	= base +	0x818;
    static constexpr uint32_t	DCGCSSI	= base +	0x81C;
    static constexpr uint32_t	DCGCI2C	= base +	0x820;
    static constexpr uint32_t	DCGCUSB	= base +	0x828;
    static constexpr uint32_t	DCGCCAN	= base +	0x834;
    static constexpr uint32_t	DCGCADC	= base +	0x838;
    static constexpr uint32_t	DCGCACMP	= base +	0x83C;
    static constexpr uint32_t	DCGCPWM	= base +	0x840;
    static constexpr uint32_t	DCGCQEI	= base +	0x844;
    static constexpr uint32_t	DCGCEEPROM	= base +	0x858;
    static constexpr uint32_t	DCGCWTIMER	= base +	0x85C;
    static constexpr uint32_t	PRWD	= base +	0xA00;
    static constexpr uint32_t	PRTIMER	= base +	0xA04;
    static constexpr uint32_t	PRGPIO	= base +	0xA08;
    static constexpr uint32_t	PRDMA	= base +	0xA0C;
    static constexpr uint32_t	PRHIB	= base +	0xA14;
    static constexpr uint32_t	PRUART	= base +	0xA18;
    static constexpr uint32_t	PRSSI	= base +	0xA1C;
    static constexpr uint32_t	PRI2C	= base +	0xA20;
    static constexpr uint32_t	PRUSB	= base +	0xA28;
    static constexpr uint32_t	PRCAN	= base +	0xA34;
    static constexpr uint32_t	PRADC	= base +	0xA38;
    static constexpr uint32_t	PRACMP	= base +	0xA3C;
    static constexpr uint32_t	PRPWM	= base +	0xA40;
    static constexpr uint32_t	PRQEI	= base +	0xA44;
    static constexpr uint32_t	PREEPROM	= base +	0xA58;
    static constexpr uint32_t	PRWTIMER	= base +	0xA5C;
};

template<PortIndex portIndexEnum>
struct PortRegisters {
    static constexpr uint32_t portIndex = static_cast<uint32_t>(portIndexEnum);
    static constexpr uint32_t portBaseRegister = 0x40058000;
    static constexpr uint32_t baseOffset = 0x1000 * portIndex;
    static constexpr uint32_t base = portBaseRegister + baseOffset;

    // derived from the datasheet
    static constexpr uint32_t	GPIODATA	= base +	0x000;
    static constexpr uint32_t	GPIODIR	= base +	0x400;
    static constexpr uint32_t	GPIOIS	= base +	0x404;
    static constexpr uint32_t	GPIOIBE	= base +	0x408;
    static constexpr uint32_t	GPIOIEV	= base +	0x40C;
    static constexpr uint32_t	GPIOIM	= base +	0x410;
    static constexpr uint32_t	GPIORIS	= base +	0x414;
    static constexpr uint32_t	GPIOMIS	= base +	0x418;
    static constexpr uint32_t	GPIOICR	= base +	0x41C;
    static constexpr uint32_t	GPIOAFSEL	= base +	0x420;
    static constexpr uint32_t	GPIODR2R	= base +	0x500;
    static constexpr uint32_t	GPIODR4R	= base +	0x504;
    static constexpr uint32_t	GPIODR8R	= base +	0x508;
    static constexpr uint32_t	GPIOODR	= base +	0x50C;
    static constexpr uint32_t	GPIOPUR	= base +	0x510;
    static constexpr uint32_t	GPIOPDR	= base +	0x514;
    static constexpr uint32_t	GPIOSLR	= base +	0x518;
    static constexpr uint32_t	GPIODEN	= base +	0x51C;
    static constexpr uint32_t	GPIOLOCK	= base +	0x520;
    static constexpr uint32_t	GPIOCR	= base +	0x524;
    static constexpr uint32_t	GPIOAMSEL	= base +	0x528;
    static constexpr uint32_t	GPIOPCTL	= base +	0x52C;
    static constexpr uint32_t	GPIOADCCTL	= base +	0x530;
    static constexpr uint32_t	GPIODMACTL	= base +	0x534;
    static constexpr uint32_t	GPIOPeriphID4	= base +	0xFD0;
    static constexpr uint32_t	GPIOPeriphID5	= base +	0xFD4;
    static constexpr uint32_t	GPIOPeriphID6	= base +	0xFD8;
    static constexpr uint32_t	GPIOPeriphID7	= base +	0xFDC;
    static constexpr uint32_t	GPIOPeriphID0	= base +	0xFE0;
    static constexpr uint32_t	GPIOPeriphID1	= base +	0xFE4;
    static constexpr uint32_t	GPIOPeriphID2	= base +	0xFE8;
    static constexpr uint32_t	GPIOPeriphID3	= base +	0xFEC;
};

// this is not only static, but also constexpr,
// allowing the compiler to eliminate it from the runtime
template<TimerBlockIndex timerIndexEnum>
struct TimerRegisters {
    static constexpr uint32_t timerBaseRegister = 0x40030000;
    static constexpr uint32_t timerIndex = static_cast<uint32_t>(timerIndexEnum);

    static constexpr uint32_t baseOffset 
        = timerIndex < 8
        ? 0x1000 * timerIndex
        : 0x1000 * (timerIndex + 5); // so that 0xc000 follows 0x7000 [11.5]
    static constexpr uint32_t base = timerBaseRegister + baseOffset;

    // derived from the datasheet
    static constexpr uint32_t	GPTMCFG	    = base +	0x000;
    static constexpr uint32_t	GPTMTAMR	= base +	0x004;
    static constexpr uint32_t	GPTMTBMR	= base +	0x008;
    static constexpr uint32_t	GPTMCTL	    = base +	0x00C;
    static constexpr uint32_t	GPTMSYNC	= base +	0x010;
    static constexpr uint32_t	GPTMIMR	    = base +	0x018;
    static constexpr uint32_t	GPTMRIS	    = base +	0x01C;
    static constexpr uint32_t	GPTMMIS	    = base +	0x020;
    static constexpr uint32_t	GPTMICR	    = base +	0x024;
    static constexpr uint32_t	GPTMTAILR	= base +	0x028;
    static constexpr uint32_t	GPTMTBILR	= base +	0x02C;
    static constexpr uint32_t	GPTMTAMATCHR	= base +	0x030;
    static constexpr uint32_t	GPTMTBMATCHR	= base +	0x034;
    static constexpr uint32_t	GPTMTAPR	= base +	0x038;
    static constexpr uint32_t	GPTMTBPR	= base +	0x03C;
    static constexpr uint32_t	GPTMTAPMR	= base +	0x040;
    static constexpr uint32_t	GPTMTBPMR	= base +	0x044;
    static constexpr uint32_t	GPTMTAR	    = base +	0x048;
    static constexpr uint32_t	GPTMTBR	    = base +	0x04C;
    static constexpr uint32_t	GPTMTAV	    = base +	0x050;
    static constexpr uint32_t	GPTMTBV	    = base +	0x054;
    static constexpr uint32_t	GPTMRTCPD	= base +	0x058;
    static constexpr uint32_t	GPTMTAPS	= base +	0x05C;
    static constexpr uint32_t	GPTMTBPS	= base +	0x060;
    static constexpr uint32_t	GPTMTAPV	= base +	0x064;
    static constexpr uint32_t	GPTMTBPV	= base +	0x068;
    static constexpr uint32_t	GPTMPP	    = base +	0xFC0;
};
