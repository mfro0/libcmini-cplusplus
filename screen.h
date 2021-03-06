#ifndef SCREEN_H
#define SCREEN_H

#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <osbind.h>
#include "memory.h"
#include "image.h"

namespace AtariGraphics {
    struct AtariScreen
    {
        static constexpr uint32_t dbaseh = 0xff8201UL;
        static constexpr uint32_t dbasel = 0xff8203UL;

        static constexpr size_t SIZE = 32 * 1000;
        
        uint32_t log;

        uint16_t active;
        void (*blank_routine)(void);


        AtariScreen();
        AtariScreen(uint32_t second_screen);
        ~AtariScreen(void);
        uint32_t old_address;
        void vblank(void) __attribute__((interrupt));
        void set_blank(void (* blank)(void));
        void (*get_blank(void))(void);
        void set_screen(const Image &img);
        void clear();
        void set();
        void cleanup(void);
    };
}
#endif // SCREEN_H