#ifndef SPRITE_H
#define SPRITE_H

#include "screen.h"
#include "tiled_image.h"

namespace {
    extern TiledImage img;
        
    struct Sprite {
        screen::AtariScreen *screen;

        uint16_t x;
        uint16_t y;
        uint16_t width;
        uint16_t height;

        uint8_t *sprite_data;
        uint8_t *save_area;

        
        Sprite(screen::AtariScreen *sc) : screen(sc)
        {
            img.tile(3);
        }

        void save(void)
        {

        }

        void draw(void) {
            save();
            for (int i = 0; i < height; i++)
                ;
                // memcpy(save_area, screen, )
        }

        void undraw(void) {

        }
    };
}
#endif // SPRITE_H