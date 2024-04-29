This: ``gpio_set(RGB_PORT, LED_G);`` is compiled to:

```
	ldr	r2, .L9+4	@ tmp115,
	movs	r3, #255	@ tmp116,
	str	r3, [r2]	@ tmp116, MEM[(volatile uint32_t *)1074122784B] 4005D020
```

This: ``((volatile uint32_t*)(0x4005D000 + 0x000))[0x02] = 0x02;`` similarly is compiled to:

```
	ldr	r3, .L9+8	@ tmp117,
	movs	r1, #2	@ tmp118,
	str	r1, [r3]	@ tmp118, MEM[(volatile uint32_t *)1074122760B] 4005D008

https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads

/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin

arm-none-eabi-g++

file HelloWorld -> elf

arm-none-eabi-objdump -h HelloWorld 

arm-none-eabi-strip -g HelloWorld

stripped 18,004

-d disassemble
0000-9464: 37,988

## Links and references
https://github.com/cortexm/baremetal




