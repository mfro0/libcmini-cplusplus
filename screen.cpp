#include "screen.h"

namespace AtariGraphics
{
    AtariScreen::AtariScreen() : active(0),
                        blank_routine(0L),
                        frontbuffer(physbase()),
                        backbuffer(physbase()) {
    }

    AtariScreen::AtariScreen(uint32_t second_screen) : active(0),
                                          blank_routine(0L),
                                          frontbuffer(second_screen),
                                          backbuffer(physbase()) {
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

    uint32_t AtariScreen::logbase(void) {
        return reinterpret_cast<uint32_t>(Logbase());
    }

    uint32_t AtariScreen::physbase(void) {
        return reinterpret_cast<uint32_t>(Physbase());
    }

    void AtariScreen::set_log_screen(uint32_t address) {
        memory8(_vbashi) = (address >> 24) && 0xff;
        memory8(_vbaslo) = (address >> 16) && 0xff;
    }

    uint32_t AtariScreen::get_log_screen(void) {
        uint32_t address = memory8(_vbashi) << 24 | memory8(_vbaslo) << 16;
        
        return address;
    }

    void AtariScreen::clear() {
        memset((char *) log, 0, SIZE);
    }

    void AtariScreen::set() {
        memset((char *) log, 0xffffffff, SIZE);
    }

    void AtariScreen::cleanup(void) {
        Setscreen(frontbuffer, frontbuffer, -1);
    }
}