#include <cstdint>
#include <osbind.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>

namespace {
    volatile uint32_t& memory32(const uint32_t loc)
    {
        return *reinterpret_cast<uint32_t *>(loc);
    }

    volatile uint16_t& memory16(const uint32_t loc)
    {
        return *reinterpret_cast<uint16_t *>(loc);
    }

    volatile uint8_t& memory8(const uint32_t loc)
    {
        return *reinterpret_cast<uint8_t *>(loc);
    }

    struct AtariScreen
    {
        static constexpr uint32_t _vbashi = 0xff8201UL;
        static constexpr size_t SIZE = 32000;

        uint32_t scr1;
        uint32_t scr2;
        int active;

        void (*blank_routine)(void);

        AtariScreen() {
            active = 0;
            blank_routine = 0L;
            scr1 = scr2 = reinterpret_cast<uint32_t>(Physbase());
        }

        AtariScreen(uint16_t* second_screen) {
            AtariScreen();
            scr2 = reinterpret_cast<uint32_t>(second_screen);
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

        void flip()
        {   
            active = !active;
            if (active)
                while ((uint32_t) Logbase() != scr2 || (uint32_t) Physbase() != scr1)
                    Setscreen(scr2, scr1, -1);            
            else
                while ((uint32_t) Logbase() != scr1 || (uint32_t) Physbase() != scr2)
                    Setscreen(scr1, scr2, -1);
            // printf("flip (%d)\r\n", active);
        }

        void clear()
        {
            memset((char *) scr1, 0, SIZE);
        }

        void set()
        {
            memset((char *) scr1, 0xffffffff, SIZE);
        }

        void cleanup(void)
        {
            while ((uint32_t) Logbase() != scr1 || (uint32_t) Physbase() != scr1)
                Setscreen(scr1, scr1, -1);
        }
    };
}

void anim(void)
{
    constexpr size_t SCREEN_SIZE = 64 * 1024;

    uint8_t *screen1[SCREEN_SIZE + 256];


    // adjust to a suitable address on a 256 bytes boundary
    uint16_t *vscreen = (uint16_t *) (((long) screen1 + 256UL) & 0xffffff00);
    memset(vscreen, 0, SCREEN_SIZE);

    AtariScreen screen(vscreen);

    for (int i = 0; i < 10; i++)
        screen.flip();

    while (Cconis())
        Cconin();
    Cconws("press ANY key"); (void) Cconin();

    screen.cleanup();
    
    delete (uint8_t *) screen1;
}

int main()
{
    Supexec(anim);
}


    
