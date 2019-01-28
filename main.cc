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
        static constexpr size_t SIZE = 32000 / sizeof(uint16_t);

        uint32_t scr1;
        uint32_t scr2;

        void (*blank_routine)(void);

        AtariScreen() { blank_routine = 0L; scr1 = scr2 = reinterpret_cast<uint32_t>(Physbase()); }
        AtariScreen(uint16_t* second_screen) { AtariScreen(); scr2 = reinterpret_cast<uint32_t>(second_screen); }
        
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
            static int active = 0;
            
            active = !active;
            if (active)
                Setscreen(scr2, scr1, -1);
            
            else
                Setscreen(scr1, scr2, -1);
            
            printf("active = %d\r\n", active);
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
    constexpr int SCREEN_SIZE = 32000;

    uint8_t *screen1 = new uint8_t[SCREEN_SIZE + 256];

    // adjust to a suitable address on a 256 bytes boundary
    uint16_t *vscreen = reinterpret_cast<uint16_t *>((reinterpret_cast<long>(screen1) + 256UL) & 0xffffff00);

    printf("vscreen now: 0x%lx\r\n", vscreen);

    AtariScreen screen(vscreen);

    // old_screen = screen.address();


    // screen.set_address(reinterpret_cast<uint32_t>(vscreen));

    /*
    for (int i = 0; i < 100; i++)
    {
        if (i & 1)
            screen.clear();
        else
            screen.set();
    }
    */
    for (int i = 0; i < 100; i++)
        screen.flip();

    while (Cconis())
        Cconin();
    Cconws("press ANY key"); (void) Cconin();

    delete screen1;
    // screen.set_address(old_screen);
}

int main()
{
    Supexec(anim);
}


    
