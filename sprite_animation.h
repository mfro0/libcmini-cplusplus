#ifndef SPRITE_ANIMATION
#define SPRITE_ANIMATION

#include <array>

#include "tiled_image.h"

#define DEBUG
#ifdef DEBUG
#include "natfeats.h"
#define dbg(format, arg...) do { nf_printf("DEBUG: (%s):" format, __FUNCTION__, ##arg); } while (0)
#define out(format, arg...) do { nf_printf("" format, ##arg); } while (0)
#else
#define dbg(format, arg...) do { ; } while (0)
#endif /* DEBUG */

namespace AtariGraphics {

    struct Coord {
        uint16_t x;
        uint16_t y;
    };

    struct AnimationPath {
        const std::array<Coord, 4>& nodes;
        
        AnimationPath(const std::array<Coord, 4>& c) : nodes(c)
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
                dbg("node = (%d, %d)\r\n", node.x, node.y);
            }
        }
    };
}
#endif // SPRITE_ANIMATION
