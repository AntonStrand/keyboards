#include "keymap_swedish_mac.h"
#include "config.h"

static uint16_t space_cadet_timer[1] = {0};

void hold_tap(int idx, uint16_t hold, uint16_t tap, bool is_pressed) {
    if (is_pressed) {
        space_cadet_timer[idx] = timer_read();
        register_code16(hold);
    } else {
        unregister_code16(hold);
        if (timer_elapsed(space_cadet_timer[idx]) < TAPPING_TERM) {
            tap_code16(tap);
        }
    }
}

void gui_qm(bool is_pressed) { hold_tap(0, KC_LGUI, SE_QUES, is_pressed); }