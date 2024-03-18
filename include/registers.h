/**
 * Low-level access to chip registers, bits, and fields.
 * They are all static, so they don't take up any memory
 * and can be used merely by inheritance.
 */

#pragma once

#include <stdint.h>

struct RegisterAccess {
    static inline void clearbits(uint32_t registerAddress, uint32_t bits) {
        *(volatile uint32_t*)registerAddress &= ~ bits;
    }
    static inline void setbits(uint32_t registerAddress, uint32_t bits) {
        *(volatile uint32_t*)registerAddress |= bits;
    }
    static inline void write(uint32_t registerAddress, uint32_t value) {
        *(volatile uint32_t*)registerAddress = value;
    }
    static inline uint32_t read(uint32_t registerAddress) {
        return *(volatile uint32_t*)registerAddress;
    }
};

struct Register {

    // definition: RegisterBit<0x3000, 4> bit
    // usage: bit = true
    template<uint32_t registerAddress, uint8_t bitNumber>
    struct RegisterBit : RegisterAccess {
        void inline operator=(bool onoff) {
            const uint32_t bitmask = (1 << bitNumber);
            if (onoff) {
                setbits(registerAddress, bitmask);
            } else {
                clearbits(registerAddress, bitmask);
            }
        }
        inline operator bool() const {
            return (read(registerAddress) & (1 << bitNumber)) != 0;
        }
    };

    template<uint32_t address, uint8_t shift, uint8_t width>
    struct RegisterField : RegisterAccess {
        static constexpr uint32_t mask = (1 << width) - 1;
        inline void operator=(uint32_t value) {
            uint32_t temp = read(address) & ~(mask << shift);
            temp |= ((value & mask) << shift);
            write(address, temp);
        }
    };

    template<uint32_t registerAddress>
    struct Register32 : RegisterAccess {
        inline void operator=(int32_t value) {
            write(registerAddress, value);
        }
    };

    // a type-safe register field
    // usage: RegisterFieldType<0x3000, 4, 2, CrystalValue> field
    // compile time check for correct value type/enumeration
    // todo check for reserved bits
    template<uint32_t registerAddress, uint8_t offset, uint8_t width, typename CrystalValue>
    struct RegisterFieldType : RegisterAccess {
        static constexpr uint32_t mask = (1 << width) - 1;
        inline void operator=(CrystalValue value) {
            uint32_t temp = read(registerAddress) & ~(mask << offset);
            temp |= ((static_cast<uint32_t>(value) & mask) << offset);
            write(registerAddress, temp);
        }
    };

    // a logial field that spans two registers
    // parameters in little-endian order
    // width extrends from zero to the left
    template<uint32_t regLSB, uint8_t widthLSB, uint32_t regMSB, uint8_t widthMSB>
    // __attribute__ ((no_inline))
    struct RegisterSpan : RegisterAccess {
        inline void operator=(uint32_t value) {
            if (widthLSB + widthMSB != 32) {
                // todo error
            }
            static constexpr uint32_t maskkLSB = (1 << widthLSB) - 1;
            static constexpr uint32_t makeMSB = (1 << widthMSB) - 1;
            write(regLSB, value & maskkLSB);
            write(regMSB, (value >> widthLSB) & makeMSB);
        }
        // RegisterField<reg1, 0, width1> field1;
        // RegisterField<reg2, 0, width2> field2;
    };

};
