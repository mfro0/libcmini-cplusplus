#include <cstdint>
#include <osbind.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "screen.h"

using namespace screen;

namespace {
    volatile uint32_t& memory32(const uint32_t loc)
    {
        return *reinterpret_cast<uint32_t *>(loc);
    }

    volatile uint16_t& memory16(const uint32_t loc)
    {
        return *reinterpret_cast<uint16_t *>(loc);
    }

    volatile uint8_t& memory8(const uint32_t loc)
    {
        return *reinterpret_cast<uint8_t *>(loc);
    }


}

void anim(void)
{
    constexpr size_t SCREEN_SIZE = 32 * 1024L;

    uint8_t *screen1[SCREEN_SIZE + 256];


    // adjust to a suitable address on a 256 bytes boundary
    uint32_t vscreen = (((uint32_t) screen1 + 256UL) & 0xffffff00);
    memset((uint8_t *) vscreen, 0, SCREEN_SIZE);

    // printf("new screen address=0x%lx\r\n", vscreen);

    AtariScreen screen(vscreen);

    for (int i = 0; i < 100; i++)
        screen.flip();

    screen.cleanup();
}

int main()
{
    Supexec(anim);

    while (Cconis())
        Cconin();
    Cconws("press ANY key"); (void) Cconin();
}


    
