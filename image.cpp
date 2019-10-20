#include "image.h"
#include <osbind.h>
#include <utility>
#include <cstdio>
#include <cstdlib>

namespace AtariGraphics {
    Image::Image(const char *filename) : image(degas_fix_address(&oa_image)) {
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

    Image::~Image() {
        restore_palette();
    }

    void Image::save_palette(void) {
        volatile uint16_t (*colreg)[16] = (volatile uint16_t (*)[16]) 0xffff8240;

        // transfer color registers into saved_palette
        for (int i = 0; i < 16; i++)
            saved_palette[i] = (*colreg)[i];
    }
    
    void Image::set_palette(uint16_t palette[]) {
        volatile uint16_t (*colreg)[16] = (volatile uint16_t (*)[16]) 0xffff8240;

        for (int i = 0; i < 16; i++)
            (*colreg)[i] = palette[i];

    }

    void Image::restore_palette(void) {
        set_palette(saved_palette);
    }

    const uint8_t * Image::image_data(void) {
        return reinterpret_cast<uint8_t *>(image->picture_data);
    }
}