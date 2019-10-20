#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include "degas_picture.h"

namespace Image {
    
    struct Image {
        static constexpr int image_wdwidth = 320 * 4 / sizeof(uint8_t);
        static constexpr uint16_t width = 40;
        static constexpr uint16_t height = 40;

        uint16_t saved_palette[16];
        DegasPictureOverAllocated oa_image;
        DegasPicture* image;

        Image(const char *filename);
        ~Image();
        void save_palette(void);
        void set_palette(uint16_t palette[]);
        void restore_palette(void);
        const uint8_t * image_data(void);
    };
}

#endif // IMAGE_H