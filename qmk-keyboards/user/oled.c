#include "antonstrand.h"
#include "oled.h"

static uint16_t                       oled_timer = 0;
__attribute__((weak)) oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_corne_logo(void) {
    static const char PROGMEM font_logo[16] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(font_logo, false);
};

void render_qmk_logo(void) {
    static const char PROGMEM font_qmk_logo[16] = {0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0};
    oled_write_P(font_qmk_logo, false);
};

void render_mod_status(void) {
#ifdef NO_ACTION_ONESHOT
    uint8_t modifiers = get_mods();
#else
    uint8_t modifiers = get_mods() | get_oneshot_mods();
#endif
    oled_write_P(PSTR(">"), false);
    (modifiers & MOD_MASK_CTRL) ? oled_write_P(PSTR("C"), false) : oled_write_P(PSTR("_"), false);
    (modifiers & MOD_MASK_SHIFT) ? oled_write_P(PSTR("S"), false) : oled_write_P(PSTR("_"), false);
    (modifiers & MOD_MASK_ALT) ? oled_write_P(PSTR("A"), false) : oled_write_P(PSTR("_"), false);
    (modifiers & MOD_MASK_GUI) ? oled_write_P(PSTR("G"), false) : oled_write_P(PSTR("_"), false);
}

void render_active_layer(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwert"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Setup"), false);
            break;
        case _NUMBER:
            oled_write_ln_P(PSTR("Nums "), false);
            break;
        case _FN:
            oled_write_ln_P(PSTR("Fn   "), false);
            break;
        case _RAPID:
            oled_write_ln_P(PSTR("Rapid"), false);
            break;
        case _GAME:
            oled_write_ln_P(PSTR("Game "), false);
            break;
        case _GAME_NUMS:
            oled_write_ln_P(PSTR("G Num"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undfd"), false);
    }
}

void render_led_state(void) {
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.num_lock ? PSTR("NUM") : PSTR(""), false);
    oled_write_ln_P(led_state.caps_lock ? PSTR("CAPS") : PSTR(""), false);
    oled_write_ln_P(led_state.scroll_lock ? PSTR("SCRL") : PSTR(""), false);
}

char wpm_str[11];
void render_wpm(void) {
    sprintf(wpm_str, "WPM:\n  %03d", get_current_wpm());
    oled_write(wpm_str, false);
}

void write_empty_line(void) { oled_write_ln("", false); }

void render_layer_icon(void) {
    static const char PROGMEM font_layer[4][6] = {
        {0x85, 0x86, 0x87, 0x88, 0x89, 0},
        {0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0},
        {0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0},
        {0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0},
    };
    uint8_t layer = 0;
    if (layer_state_is(_ADJUST)) {
        layer = 3;
    } else if (layer_state_is(_RAISE)) {
        layer = 2;
    } else if (layer_state_is(_LOWER)) {
        layer = 1;
    }
    oled_write_P(font_layer[layer], false);
};

void render_logo(void) {
    switch (get_highest_layer(layer_state)) {
        case _ADJUST:
            render_qmk_logo();
            break;
        default:
            render_corne_logo();
    }
}

void render_main(void) {
    render_logo();
    write_empty_line();

    render_active_layer();
    render_layer_icon();

    render_led_state();

    oled_write_P(PSTR("Anton"), false);
    write_empty_line();

    render_wpm();
    write_empty_line();

    render_mod_status();
}

void oled_task_user(void) {
    if (timer_elapsed(oled_timer) > 30000) {
        oled_off();
        return;
    } else {
        oled_on();
    }
    if (is_keyboard_master()) {
        render_main();
    }
}

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_timer = timer_read32();
    }
    return true;
}
