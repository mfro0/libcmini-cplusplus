#include "sprite.h"

namespace AtariGraphics
{
    Sprite::Sprite(AtariScreen& sc, TiledImage& image) : screen(sc),
                                                         image(image) {
        sprite_data = image.tile(3);
    }

    void Sprite::save(void) {
    }

    void Sprite::draw(void) {
        save();
        for (int i = 0; i < height; i++)
            ;
            // memcpy(save_area, screen, )
    }

    void Sprite::undraw(void) {

    }
}