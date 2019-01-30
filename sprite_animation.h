#ifndef SPRITE_ANIMATION
#define SPRITE_ANIMATION

#include "tiled_image.h"

namespace {

    struct SpriteAnimation {
        const TiledImage* image;
        
        SpriteAnimation(const TiledImage* img) : image(img)
        {

        }
    };
}
#endif // SPRITE_ANIMATION