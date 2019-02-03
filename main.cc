#include <osbind.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "screen.h"
#include "sprite.h"
#include "tiled_image.h"
#include "image.h"
#include "sprite_animation.h"

namespace {



    void anim(void) {
        const TiledImage bees("images/bees.pi1", SpriteDefinition(40, 40));
        Image background("images/meadow.pi1");

        AtariScreen screen(reinterpret_cast<uint32_t>(background.image_data()));

        const Coord anodes[] =  { { 10, 10 },
                                  { 11, 10 }, };

        SpriteAnimation an(bees, AnimationPath(anodes));

        while (Cconis())
            Cconin();
        (void) Cconws("press ANY key"); (void) Cconin();

        screen.cleanup();
    }
}

int main() {
    Supexec(anim);
}


    
