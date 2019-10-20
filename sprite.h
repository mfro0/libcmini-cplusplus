#ifndef SPRITE_H
#define SPRITE_H

#include "screen.h"
#include "tiled_image.h"

namespace AtariGraphics {
    
    struct Sprite {
        AtariScreen& screen;
        TiledImage& image;

        uint16_t x;
        uint16_t y;
        uint16_t width;
        uint16_t height;

        uint16_t *sprite_data;
        uint8_t *save_area;


        Sprite(AtariScreen& sc, TiledImage& image);

        void save(void);
        void draw(void);
        void undraw(void);
    };
}
#endif // SPRITE_H