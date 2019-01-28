#include <cstdint>

namespace {
    volatile uint8_t& memory(const uint32_t loc)
    {
        return *reinterpret_cast<uint8_t *>(loc);
    }
}

int main()
{
    uint16_t screen1[16000];
    uint16_t screen2[16000];

    memory(0xff8200UL) = reinterpret_cast<uint32_t>(screen1);
    memory(0xff8200UL) = reinterpret_cast<uint32_t>(screen2);
}


    
