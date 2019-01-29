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

        AtariScreen(uint32_t second_screen) : scr2(second_screen),
                                              active(0),
                                              blank_routine(0L)
        {
            scr1 = reinterpret_cast<uint32_t>(Physbase());
            printf("screen address = 0x%lx, 0x%lx\r\n", scr1, scr2);
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
            printf("flip (%d)\r\n", active);
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
    constexpr size_t SCREEN_SIZE = 64 * 1024L;

    uint8_t *screen1[SCREEN_SIZE + 256];


    // adjust to a suitable address on a 256 bytes boundary
    uint32_t vscreen = (((uint32_t) screen1 + 256UL) & 0xffffff00);
    memset((uint8_t *) vscreen, 0, SCREEN_SIZE);

    printf("new screen address=0x%lx\r\n", vscreen);

    AtariScreen screen(vscreen);

    for (int i = 0; i < 100; i++);
        screen.flip();

    screen.cleanup();
}

int main()
{
    Supexec(anim);

    while (Cconis())
        Cconin();
    Cconws("press ANY key"); (void) Cconin();
}


    
