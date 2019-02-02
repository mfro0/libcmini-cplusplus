#ifndef IMAGE_H
#define IMAGE_H

#include <osbind.h>
#include <cstdint>
#include <utility>
#include <cstdio>
#include "degas_picture.h"

namespace {
    
    struct Image {
        static constexpr int image_wdwidth = 320 * 4 / sizeof(uint8_t);
        static constexpr uint16_t width = 40;
        static constexpr uint16_t height = 40;

        uint16_t saved_palette[16];
        DegasPictureOverAllocated oa_image;
        DegasPicture* image;

        Image(const char *filename) : image(degas_fix_address(&oa_image)) {
            short fh;
            int32_t length = 0;

            fh = Fopen(filename, 2);
            if (fh > 0) {
                length = Fread(fh, sizeof(DegasPicture), image);
                Fclose(fh);
            } 
            
            if (fh < 0 || length != sizeof(DegasPicture)) {
                (void) Cconws("Error: image ");
                (void) Cconws(filename);
                (void) Cconws(" could not be loaded\r\n");

                exit(1);
            }
            save_palette();
            set_palette(image->palette);
        }

        ~Image() {
            restore_palette();
        }

        void save_palette(void) {
            volatile uint16_t (*colreg)[16] = (volatile uint16_t (*)[16]) 0xffff8240;

            // transfer color registers into saved_palette
            for (int i = 0; i < 16; i++)
                saved_palette[i] = (*colreg)[i];
        }

        void set_palette(uint16_t palette[]) {
            volatile uint16_t (*colreg)[16] = (volatile uint16_t (*)[16]) 0xffff8240;

            for (int i = 0; i < 16; i++)
                (*colreg)[i] = palette[i];

        }

        void restore_palette(void) {
            set_palette(saved_palette);
        }

        const uint8_t *image_data(void) {
            return reinterpret_cast<uint8_t *>(image->picture_data);
        }
    };
}

#endif // IMAGE_H