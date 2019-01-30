#include <cstdint>
#include <osbind.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "screen.h"
#include "sprite.h"
#include "tiled_image.h"
#include "sprite_animation.h"

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

    TiledImage bees("images/bees.pi1");
    Image background("images/meadow.pi1");
    
    AtariScreen screen(reinterpret_cast<uint32_t>(background.image_data()));
    
    for (int i = 0; i < 100; i++)
        screen.flip();

    screen.cleanup();
}

int main()
{
    Supexec(anim);

    while (Cconis())
        Cconin();
    (void) Cconws("press ANY key"); (void) Cconin();
}


    
