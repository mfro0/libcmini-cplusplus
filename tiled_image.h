#ifndef TILED_IMAGE_H
#define TILED_IMAGE_H

#include <osbind.h>
#include <cstdint>
#include <utility>
#include <cstdio>

namespace {
    struct DegasPicture {
        uint16_t resolution;
        uint16_t palette[16];
        uint16_t picture_data[16000];
    };

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
        int32_t fpos;

        fh = Fopen(filename, 2);
        if (fh > 0) {
            fpos = Fseek(0, fh, 2);    // seek to end of file
            Fread(fh, fpos, &image);
            Fclose(fh);
            printf("image %s has been loaded\r\nto %p\r\n", filename, &image);
            printf("press any key\r\n");
            while (Cconis()) Cconin(); Cconin();
        }
    }

    uint8_t* tile(uint16_t tile_index) {
        printf("tile size of image %d is (%d,%d)\r\n",
               tile_index,
               tile_size(tile_index).first,
               tile_size(tile_index).second);
        return 0L;
    }
};
}
#endif // TILED_IMAGE_H