#ifndef TILED_IMAGE_H
#define TILED_IMAGE_H

#include <osbind.h>
#include <cstdint>
#include <utility>
#include <cstdio>
#include "degas_picture.h"

namespace {
    
struct TiledImage {
    static constexpr int image_size = sizeof(DegasPicture::picture_data);
    static constexpr int BITS_PER_PIXEL = 4;
    static constexpr int IMAGE_WDWIDTH = 320 * BITS_PER_PIXEL / sizeof(uint16_t) / 8;
    
    static constexpr uint16_t TILE_WIDTH = 40;
    static constexpr uint16_t TILE_HEIGHT = 40;

    DegasPicture picture;

    DegasPicture load(const char *filename) {
        short fh;
        int32_t length = 0;
        DegasPicture picture;

        fh = Fopen(filename, 2);
        if (fh > 0) {
            length = Fread(fh, sizeof(DegasPicture), &picture);
            Fclose(fh);
        } 
        
        if (fh < 0 || length != sizeof(DegasPicture))
        {
            (void) Cconws("Error: image ");
            (void) Cconws(filename);
            (void) Cconws(" not found\r\n");

            exit(1);
        }

        return picture;
    }

    TiledImage(const char *filename) : picture(load(filename)) {
        
    }

    uint16_t* tile(const uint16_t tile_index) {
        // return start address of tile # tile_index
        // tiles are TILE_WIDTH pixels wide, image is IMAGE_WDWIDTH
        // words wide
        return picture.picture_data + TILE_WIDTH * BITS_PER_PIXEL / (sizeof(uint16_t) * 8);
    }
};
}
#endif // TILED_IMAGE_H