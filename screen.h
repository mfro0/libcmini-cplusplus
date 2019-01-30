#ifndef SCREEN_H
#define SCREEN_H

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <osbind.h>

namespace screen {
    struct AtariScreen
    {
        static constexpr uint32_t _vbashi = 0xff8201UL;
        static constexpr size_t SIZE = 32 * 1000;
        
        uint32_t log;

        uint16_t active;
        void (*blank_routine)(void);
        uint32_t frontbuffer;
        uint32_t backbuffer;


        AtariScreen() : active(0),
                        blank_routine(0L),
                        frontbuffer(physbase()),
                        backbuffer(physbase()) {
        }

        AtariScreen(uint32_t second_screen) : active(0),
                                              blank_routine(0L),
                                              frontbuffer(second_screen),
                                              backbuffer(physbase())
        {
            // printf("screen address = 0x%lx, 0x%lx\r\n", frontbuffer, backbuffer);
        }
        
        void vblank(void) __attribute__((interrupt))
        {
            if (blank_routine != NULL)
                (*blank_routine)();
        }

        void set_blank(void (*blank)(void)) {
            blank_routine = blank;
        }

        void (*get_blank(void))(void)
        {
            return blank_routine;
        }

        static uint32_t logbase(void){
            return reinterpret_cast<uint32_t>(Logbase());
        }

        static uint32_t physbase(void){
            return reinterpret_cast<uint32_t>(Physbase());
        }

        void flip()
        {   
            active = !active;
            if (active)
            {
                while ((logbase() != backbuffer) || (physbase() != frontbuffer))
                    Setscreen(backbuffer, frontbuffer, -1);  
                log = backbuffer;          
            }
            else
            {

                while ((logbase() != frontbuffer) || (physbase() != backbuffer))
                    Setscreen(frontbuffer, backbuffer, -1);
                log = frontbuffer;
            }
            // printf("flip (%d)\r\n", active);
        }

        void clear()
        {
            memset((char *) log, 0, SIZE);
        }

        void set()
        {
            memset((char *) log, 0xffffffff, SIZE);
        }

        void cleanup(void)
        {
            while ((logbase() != frontbuffer) || (physbase() != frontbuffer))
                Setscreen(frontbuffer, frontbuffer, -1);
        }

    };
}
#endif // SCREEN_H