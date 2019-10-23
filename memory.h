#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>

namespace {
    volatile uint32_t& memory32(const uint32_t loc) {
        return *reinterpret_cast<volatile uint32_t *>(loc);
    }

    volatile uint16_t& memory16(const uint32_t loc) {
        return *reinterpret_cast<volatile uint16_t *>(loc);
    }

    volatile uint8_t& memory8(const uint32_t loc) {
        return *reinterpret_cast<volatile uint8_t *>(loc);
    }
}

#endif // MEMORY_H