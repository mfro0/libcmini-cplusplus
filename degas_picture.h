#ifndef DEGAS_PICTURE
#define DEGAS_PICTURE

namespace {
    struct DegasPicture {
        uint16_t resolution;
        uint16_t palette[16];
        uint16_t picture_data[16000];
    };

    struct DegasPictureOverAllocated {
        struct DegasPicture p;
        uint8_t filler[256];            // need to ensure we overallocate enough memory to align
                                        // picture_data to an address evenly divisable by 256
                                        // (Atari ST hardware limitation)
    };
}
#endif // DEGAS_PICTURE