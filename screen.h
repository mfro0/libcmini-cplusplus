#ifndef SCREEN_H
#define SCREEN_H

#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <osbind.h>
#include "memory.h"

namespace AtariGraphics {
    struct AtariScreen
    {
        static constexpr uint32_t _vbashi = 0xff8201UL;
        static constexpr uint32_t _vbaslo = 0xff9203UL;

        static constexpr size_t SIZE = 32 * 1000;
        
        uint32_t log;

        uint16_t active;
        void (*blank_routine)(void);
        uint32_t frontbuffer;
        uint32_t backbuffer;


        AtariScreen();

        AtariScreen(uint32_t second_screen);
        
        ~AtariScreen(void);

        void vblank(void) __attribute__((interrupt));

        void set_blank(void (* blank)(void));

        void (*get_blank(void))(void);

        uint32_t logbase(void);

        uint32_t physbase(void);

        void set_log_screen(uint32_t address);

        uint32_t get_log_screen(void);

        void clear();

        void set();

        void cleanup(void);
    };
}
#endif // SCREEN_H