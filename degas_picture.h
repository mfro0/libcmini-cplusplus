#ifndef DEGAS_PICTURE
#define DEGAS_PICTURE

#include <cstddef>
#include <cstdio>

namespace {
    struct DegasPicture {
        uint16_t resolution;
        uint16_t palette[16];
        uint16_t picture_data[16000];
    };

    struct DegasPictureOverAllocated {
        DegasPicture p;

        static DegasPicture* fix_address(DegasPictureOverAllocated* oa)
        {
            printf("p = %p,\r\nfixed address = 0x%lx\r\n",
                   oa,
                   (reinterpret_cast<uint32_t>(oa) & 0xffffff00) -
                                                    offsetof(DegasPicture, picture_data));
            while (Cconis()) Cconin(); (void) Cconws("press key"); Cconin();

            return reinterpret_cast<DegasPicture *>((reinterpret_cast<uint32_t>(oa) & 0xffffff00) -
                                                                               offsetof(DegasPicture, picture_data));
                                                                               
        }    
        uint8_t filler[256];            // need to ensure we overallocate enough memory to align
                                        // the picture_data member to an address evenly divisable by 256
                                        // (Atari ST hardware limitation)
    };
}
#endif // DEGAS_PICTURE