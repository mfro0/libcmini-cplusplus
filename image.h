#ifndef IMAGE_H
#define IMAGE_H

#include <osbind.h>
#include <cstdint>
#include <utility>
#include <cstdio>
#include "degas_picture.h"

namespace {
    
    struct Image {
        static constexpr int image_size = 32 * 1000L + 34;
        static constexpr int image_wdwidth = 320 * 4 / sizeof(uint8_t);
        static constexpr uint16_t width = 40;
        static constexpr uint16_t height = 40;

        DegasPicture image;

        Image(const char *filename) {
            short fh;
            int32_t length = 0;

            fh = Fopen(filename, 2);
            if (fh > 0) {
                length = Fread(fh, sizeof(DegasPicture), &image);
                Fclose(fh);
            } 
            
            if (fh < 0 || length != sizeof(DegasPicture))
            {
                (void) Cconws("Error: image ");
                (void) Cconws(filename);
                (void) Cconws(" not found\r\n");

                exit(1);
            }
        }
    };
}

#endif // IMAGE_H