#include <cstdint>
#include <osbind.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "screen.h"
#include "sprite.h"
#include "tiled_image.h"
#include "image.h"
#include "sprite_animation.h"


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
    TiledImage bees("images/bees.pi1");
    Image background("images/meadow.pi1");

    AtariScreen screen(reinterpret_cast<uint32_t>(background.image_data()));

    Coord anodes[] =  { { 10, 10 },
                        { 11, 10 }, };

    SpriteAnimation an(bees, anodes);
    for (int i = 0; i < 100; i++)
        screen.flip();

    while (Cconis())
        Cconin();
    (void) Cconws("press ANY key"); (void) Cconin();

    screen.cleanup();
}

int main()
{
    Supexec(anim);
}


    
