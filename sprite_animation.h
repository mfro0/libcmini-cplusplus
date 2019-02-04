#ifndef SPRITE_ANIMATION
#define SPRITE_ANIMATION

#include <array>

#include "tiled_image.h"

namespace {

    typedef std::pair<uint16_t, uint16_t> pair16;

    struct AnimationPath {
        const std::array<pair16, 2> nodes;
        
        AnimationPath(const std::array<pair16, 2>& c) : nodes(c)
        {

        }
    };

    struct SpriteAnimation {
        const TiledImage image;
        const AnimationPath path;

        SpriteAnimation(const TiledImage& img, const AnimationPath& p) : image(img),
                                                                         path(p)
        {
            int n = 0;

            for (const auto& node : path.nodes) {
                // sprite[n].undraw();
                // printf("node = (%d, %d)\r\n", node.first, node.second);
            }
        }
    };
}
#endif // SPRITE_ANIMATION