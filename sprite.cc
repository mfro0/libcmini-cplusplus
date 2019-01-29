#include <cstdint>
#include "screen.h"
#include "image.h"

using namespace screen;

Image img = Image("images/bees.pi1");

struct Sprite {
    AtariScreen *screen;

    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;

    uint8_t *sprite_data;
    uint8_t *save_area;

    Sprite(AtariScreen *sc) : screen(sc)
    {

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
};