#ifndef DEGAS_PICTURE
#define DEGAS_PICTURE

#include <cstddef>

namespace {
    struct DegasPicture {
        uint16_t resolution;
        uint16_t palette[16];
        uint16_t picture_data[16000];
    };

    struct DegasPictureOverAllocated {
        uint8_t filler[256];            // need to ensure we overallocate enough memory to align
                                        // the picture_data member to an address evenly divisable by 256
                                        // (Atari ST hardware limitation)
        DegasPicture p;

        DegasPicture* fix_address(void)
        {
            return reinterpret_cast<DegasPicture *>((reinterpret_cast<uint32_t>(&p) & 0xffffff00) -
                                                                               offsetof(DegasPicture, picture_data));
                                                                               
        }    
    };
}
#endif // DEGAS_PICTURE