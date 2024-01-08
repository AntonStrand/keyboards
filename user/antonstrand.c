#include "quantum.h"
#include "rgblight_list.h"
#include "antonstrand.h"
#include "keymap_swedish_mac.h"
#include "sendstring_swedish_mac.h"
#include "config.h"
#include "space_cadet.c"
#include "repeat_key_press.c"
#include "git_command.h"
#ifdef OLED_DRIVER_ENABLE
#    include "oled.h"
#endif
/**
 * Hold modifier until is_pressed is false. The key is tapped once when is_presses becomes true.
 */
void tap_hold_mod(uint16_t mod, uint16_t kc, bool is_pressed) {
    if (is_pressed) {
        register_code16(mod);
        tap_code16(kc);
    } else {
        unregister_code16(mod);
    }
}

/**
 * Tap key while a modifier is held.
 */
void mod_tap(uint16_t mod, uint16_t kc) {
    register_code16(mod);
    tap_code16(kc);
    unregister_code16(mod);
}

void clear_keyboard_mods(void) {
    clear_mods();
    clear_oneshot_mods();
}

/**
 * Macro to compile the keyboard.
 */
void compile_keyboard(void) {
    clear_keyboard_mods();
    send_string("qmk compile -kb " QMK_KEYBOARD " -km " QMK_KEYMAP SS_TAP(X_ENTER));
}

/**
 * Macro to flash the keyboard.
 */
void flash_keyboard(void) {
    clear_keyboard_mods();
    send_string("qmk flash -kb " QMK_KEYBOARD " -km " QMK_KEYMAP SS_TAP(X_ENTER));
    reset_keyboard();
}

void set_color(int from, int to, int r, int g, int b) {
#ifdef RGB_MATRIX_ENABLE
    int i;
    for (i = from; i <= to; i++) {
        rgb_matrix_set_color(i, r, g, b);
    }
#endif
}

void suspend_power_down_kb(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
#endif
#ifdef OLED_DRIVER_ENABLE
    oled_off();
#endif
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(false);
#endif
#ifdef OLED_DRIVER_ENABLE
    oled_on();
#endif
    suspend_wakeup_init_user();
}

__attribute__((weak)) void matrix_init_keymap(void) {}

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable();
#endif
#ifdef COMBO_ENABLE
    combo_enable();
#endif
    matrix_init_keymap();
}

// To be able to use it in a keymap
__attribute__((weak)) void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
    repeat_pressed_key();
    matrix_scan_keymap();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_DRIVER_ENABLE
    if (record->event.pressed) {
        process_record_user_oled(keycode, record);
    }
#endif

    bool is_shifted = keyboard_report->mods & MOD_MASK_SHIFT;

    switch (keycode) {
        case PIPE:
            if (record->event.pressed) {
                send_string("|>");
            }
            break;

        case COMPOSE:
            if (record->event.pressed) {
                send_string(">>");
            }
            break;

        case SKINNY_ARROW:
            if (record->event.pressed) {
                send_string("->");
            }
            break;

        case FAT_ARROW:
            if (record->event.pressed) {
                send_string("=>");
            }
            break;

        case APP:
            tap_hold_mod(KC_LCMD, KC_TAB, record->event.pressed);
            break;

        case R_LEFT:
            set_pressed_key(R_LEFT, record->event.pressed, is_shifted);
            return false;
        case R_UP:
            set_pressed_key(R_UP, record->event.pressed, is_shifted);
            return false;
        case R_RIGHT:
            set_pressed_key(R_RIGHT, record->event.pressed, is_shifted);
            return false;
        case R_DOWN:
            set_pressed_key(R_DOWN, record->event.pressed, is_shifted);
            return false;

        case COMPILE:
            if (record->event.pressed) {
                compile_keyboard();
            }
            return false;

        case FLASH:
            if (record->event.pressed) {
                flash_keyboard();
            }
            return false;

        case MAKE_ALL:
            if (record->event.pressed) {
                send_string("qmk compile -kb all -km antonstrand" SS_TAP(X_ENTER));
            }
            return false;

        case CK_BASE:
            if (record->event.pressed) {
                layer_move(_QWERTY);
            }
            return false;

        case GUI_QM:
            gui_qm(record->event.pressed);
            break;

#ifdef GIT_COMMANDS
        case GH_PR:
            if (record->event.pressed) {
                open_new_github_pr();
            }
            break;

        case GH_PBRN:
            if (record->event.pressed) {
                push_new_branch();
            }
            break;

        case GH_OBRN:
            if (record->event.pressed) {
                open_branch_in_github();
            }
            break;

        case GH_OPEN:
            if (record->event.pressed) {
                open_in_github();
            }
            break;
#endif
    }

    return true;
};
