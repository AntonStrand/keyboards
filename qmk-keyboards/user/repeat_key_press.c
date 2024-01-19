#include "antonstrand.h"

uint16_t pressed_key = NO_KEY_PRESS;
uint16_t delay_timer = 0;
uint16_t delay       = 0;

void set_pressed_key(uint16_t key, bool is_pressed, bool scroll_fast) {
    if (is_pressed) {
        pressed_key = key;
    } else {
        pressed_key = NO_KEY_PRESS;
    }
    delay       = scroll_fast ? 10 : 25;
    delay_timer = 0;
}

/**
 * Use in matrix_scan_user to quickly repeat key presses.
 */
void repeat_pressed_key(void) {
    if (timer_elapsed(delay_timer) > delay) {
        switch (pressed_key) {
            case R_LEFT:
                tap_code16(KC_LEFT);
                break;
            case R_UP:
                tap_code16(KC_UP);
                break;
            case R_RIGHT:
                tap_code16(KC_RIGHT);
                break;
            case R_DOWN:
                tap_code16(KC_DOWN);
                break;
        }
        delay_timer = timer_read();
    }
}
