#include "degas_picture.h"
#include <cstdint>

namespace AtariGraphics {
    DegasPicture * fix_address(const DegasPictureOverAllocated* overallocated) {
        return reinterpret_cast<DegasPicture *>(((reinterpret_cast<uint32_t>(overallocated)
                                                  + 256
                                                  + offsetof(DegasPicture, picture_data))
                                                  & 0xffffff00) -
                                                  offsetof(DegasPicture, picture_data));
                                                                               
    }    
}   