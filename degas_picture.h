#ifndef DEGAS_PICTURE
#define DEGAS_PICTURE

#include <cstddef>
#include <cstdio>

namespace {
    // this structure actually matches the structure of a
    // DEGAS Elite picture (an enhanced version of the original Degas
    // application) that extends the original format by 32 bytes.
    // Trying to read an original Degas picture will most likely fail.
    struct DegasPicture {
        uint16_t resolution;
        uint16_t palette[16];
        uint16_t picture_data[16000];
        uint16_t left_color[4];
        uint16_t right_color[4];
        uint16_t direction[4];
        uint16_t delay[4];
    };

        
    struct DegasPictureOverAllocated {
        uint8_t filler[256 + offsetof(DegasPicture, picture_data)];
                                        // need to ensure we overallocate enough memory to align
                                        // the picture_data member to an address evenly divisable by 256
                                        // (Atari ST hardware limitation)
        DegasPicture p;
    };

    DegasPicture* degas_fix_address(const DegasPictureOverAllocated* overallocated) {
        return reinterpret_cast<DegasPicture *>(((reinterpret_cast<uint32_t>(overallocated)
                                                  + 256
                                                  + offsetof(DegasPicture, picture_data))
                                                  & 0xffffff00) -
                                                  offsetof(DegasPicture, picture_data));
                                                                               
    }    

}
#endif // DEGAS_PICTURE