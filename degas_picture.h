#ifndef DEGAS_PICTURE
#define DEGAS_PICTURE

namespace {
    struct DegasPicture {
        uint16_t resolution;
        uint16_t palette[16];
        uint16_t picture_data[16000];
    };
}
#endif // DEGAS_PICTURE