#include <osbind.h>
#include <cstdint>

struct TiledImage {
    static constexpr int image_size = 32 * 1000L + 34;

    uint8_t *image;

    TiledImage(const char *filename) {
        short fh;
        int32_t fpos;

        fh = Fopen(filename, 2);
        if (fh > 0) {
            Fread(fh, fpos, image);
            Fclose(fh);
        }
    }
};