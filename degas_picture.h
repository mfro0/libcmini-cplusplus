#ifndef DEGAS_PICTURE
#define DEGAS_PICTURE

#include <cstddef>
#include <cstdint>

namespace AtariGraphics {
    // this structure matches the format of a
    // DEGAS Elite picture (an enhanced version of the original Degas
    // application) that extends the original format by 32 bytes.
    // Trying to read an original Degas picture will most likely fail.
    struct DegasPicture {
        uint16_t resolution;
        uint16_t palette[16];
        uint16_t picture_data[16000];
        uint16_t left_color[4];         // left color animation limit table
        uint16_t right_color[4];        // right color animation limit table
        uint16_t direction[4];          // animation channel direction flag (0=left, 1=off, 2=right)
        uint16_t delay[4];              // 128 - animation channel delay in 1/60's of a second
    
    };

        
    struct DegasPictureOverAllocated {
        uint8_t filler[256 + offsetof(DegasPicture, picture_data)];
                                        // need to ensure we overallocate enough memory to align
                                        // the picture_data member to an address evenly divisable by 256
                                        // (Atari ST hardware limitation). This is meant to be able to set
                                        // the ATARI video base address directly in the image data
        DegasPicture p;
    };

    DegasPicture* fix_address(const DegasPictureOverAllocated* overallocated);

}
#endif // DEGAS_PICTURE