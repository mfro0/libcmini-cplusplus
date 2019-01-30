#ifndef TILED_IMAGE_H
#define TILED_IMAGE_H

#include <osbind.h>
#include <cstdint>
#include <utility>
#include <cstdio>
#include "degas_picture.h"

namespace {
    
struct TiledImage {
    static constexpr int image_size = 32 * 1000L + 34;
    static constexpr int image_wdwidth = 320 * 4 / sizeof(uint8_t);
    static constexpr uint16_t width = 40;
    static constexpr uint16_t height = 40;

    DegasPicture image;

    auto tile_size(uint16_t i) -> std::pair<uint16_t, uint16_t> {
        return std::make_pair<uint16_t, uint16_t>(i * width, i * height * image_wdwidth);
    }

    TiledImage(const char *filename) {
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

    uint8_t* tile(const uint16_t tile_index) {
        printf("tile size of image %d is (%d,%d)\r\n",
               tile_index,
               tile_size(tile_index).first,
               tile_size(tile_index).second);
        return 0L;
    }
};
}
#endif // TILED_IMAGE_H