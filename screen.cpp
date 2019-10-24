#include "screen.h"

namespace AtariGraphics
{
    AtariScreen::AtariScreen() : active(0),
                                 blank_routine(0L) {
    }

    AtariScreen::AtariScreen(uint32_t second_screen) : active(0),
                                                       blank_routine(0L) {
    }

    AtariScreen::~AtariScreen(void) {
        cleanup();
    }

    void AtariScreen::vblank(void) {
        if (blank_routine != NULL)
            (*blank_routine)();
    }

    void AtariScreen::set_blank(void (* blank)(void)) {
        blank_routine = blank;
    }

    void (* AtariScreen::get_blank(void))(void) {
        return blank_routine;
    }

    void AtariScreen::set_screen(const Image & img) {
        uint32_t address = reinterpret_cast<uint32_t>(img.image->picture_data);

        memory8(dbaseh) = (address >> 16) & 0xff;
        memory8(dbasel) = (address >> 8) & 0xff;
    }

    Image* AtariScreen::get_screen(void) {
        Image* address = reinterpret_cast<Image*>(memory8(dbaseh) << 16 | memory8(dbasel) << 8);
        return address;
    }

    void AtariScreen::clear() {
        memset((char *) log, 0, SIZE);
    }

    void AtariScreen::set() {
        memset((char *) log, 0xffffffff, SIZE);
    }

    void AtariScreen::cleanup(void) {
        // Setscreen(frontbuffer, frontbuffer, -1);
    }
}