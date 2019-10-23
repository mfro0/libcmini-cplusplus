#include <osbind.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <array>

#include "screen.h"
#include "sprite.h"
#include "tiled_image.h"
#include "image.h"
#include "sprite_animation.h"
#include "rng.h"

#include <iostream>

namespace {
    using namespace AtariGraphics;

    void anim(void) {
        const TiledImage bees("images/bees.pi1", SpriteDefinition(40, 40));
        Image background("images/meadow.pi1");
        AtariScreen screen(reinterpret_cast<uint32_t>(background.image_data()));
            
        std::array<Coord, 4> anodes = {{ { 10, 10 },
                                         { 10, 11 },
                                         { 11, 11 },
                                         { 12, 11 } }};
        // decltype(auto) anodes = std::make_array({10, 10}, {10, 11});
        SpriteAnimation an(bees, AnimationPath(anodes));

        std::cout << "address=" << std::hex << reinterpret_cast<uint32_t>(screen.get_screen());
          
        screen.set_screen(background);
        while (Cconis())
            Cconin();

        (void) Cconws("press anykey"); (void) Cconin();

        screen.cleanup();
    }
}


int main() {
    Supexec(anim);
}


    
