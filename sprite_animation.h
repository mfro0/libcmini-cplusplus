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
        const Coord * const nodes;
        
        AnimationPath(const Coord * const c) : nodes(c)
        {

        }
    };

    struct SpriteAnimation {
        const TiledImage image;
        const AnimationPath path;

        SpriteAnimation(const TiledImage& img, const AnimationPath& p) : image(img),
                                                                        path(p)
        {

        }
    };
}
#endif // SPRITE_ANIMATION