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

    class AtariScreen
    {
        static constexpr uint32_t _vbashi = 0xff8201UL;
        static constexpr size_t SIZE = 32000 / sizeof(uint16_t);

        uint32_t scr1;
        uint32_t scr2;
        void (*blank_routine)(void);

    public:
        AtariScreen() { blank_routine = 0L; }
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
            Getscreen(&scr1, &scr2, -1);
            Setscreen(scr2, scr1, -1);
        }

        void clear()
        {
            for (int i = 0; i < SIZE / 2; i++)
                ; //memory(address() + i) = 0;
        }

        void set()
        {
            for (int i = 0; i < SIZE / 2; i++)
                ;// memory(address() + i) = 0xffff;
        }
    };

    class tst
    {
            int val;    
        public:
            tst(int i) { val = i; };
            ~tst() { ; };
            int getvalue(void) { return val; }
    };
}

// ensure global constructors are called
tst mytest(42);

void anim(void)
{
    constexpr int SCREEN_SIZE_WORDS = 32000 / 2;

    uint16_t screen1[SCREEN_SIZE_WORDS + 128] = {0};

    // align to a suitable address on a 256 bytes boundary
    uint16_t *vscreen = reinterpret_cast<uint16_t *>((reinterpret_cast<long>(screen1) + 256UL) & 0xffff00);
    uint32_t old_screen;

    printf("vscreen now: 0x%lx\r\n", vscreen);

    AtariScreen screen;

    old_screen = screen.address();

    printf("address was 0x%lx, set to 0x%lx now\r\n",
           old_screen,
           reinterpret_cast<uint32_t>(vscreen));
    

    screen.set_address(reinterpret_cast<uint32_t>(vscreen));

    /*
    for (int i = 0; i < 100; i++)
    {
        if (i & 1)
            screen.clear();
        else
            screen.set();
    }
    */

    screen.set_address(old_screen);
}

int main()
{
    Supexec(anim);
}


    
