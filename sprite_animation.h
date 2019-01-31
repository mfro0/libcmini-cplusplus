#ifndef SPRITE_ANIMATION
#define SPRITE_ANIMATION

#include <array>

#include "tiled_image.h"

namespace {

    struct Coord {
        uint16_t x;
        uint16_t y;
    };

    struct AnimationPath {
        Coord *nodes;
        
        AnimationPath(Coord *c) : nodes(c)
        {

        }
    };

    struct SpriteAnimation {
        const TiledImage image;
        AnimationPath path;

        SpriteAnimation(const TiledImage& img, const AnimationPath& p) : image(img),
                                                                        path(p)
        {

        }
    };
}
#endif // SPRITE_ANIMATION