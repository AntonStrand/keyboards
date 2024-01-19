#include "quantum.h"
#include "combos_config.h"
#include "antonstrand.h"

enum combo_events { COMBO_DOT_SPC, COMBO_DOT_ENT, COMBO_COPY, COMBO_PASTE };

const uint16_t PROGMEM combo_DOT_SPC[] = {KC_DOT, KC_SPC, COMBO_END};
const uint16_t PROGMEM combo_DOT_ENT[] = {KC_DOT, KC_ENT, COMBO_END};
const uint16_t PROGMEM combo_COPY[]    = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_PASTE[]   = {KC_X, KC_V, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {[COMBO_DOT_SPC] = COMBO_ACTION(combo_DOT_SPC), [COMBO_DOT_ENT] = COMBO_ACTION(combo_DOT_ENT), [COMBO_COPY] = COMBO_ACTION(combo_COPY), [COMBO_PASTE] = COMBO_ACTION(combo_PASTE)};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case COMBO_DOT_SPC:  // dot space shift
            if (pressed) {
                SEND_STRING(". ");
                set_oneshot_mods(MOD_LSFT);
            }
            break;
        case COMBO_DOT_ENT:  // dot enter shift
            if (pressed) {
                tap_code(KC_DOT);
                tap_code(KC_ENT);
                set_oneshot_mods(MOD_LSFT);
            }
            break;
        case COMBO_COPY:  // Copy
            if (pressed) {
                mod_tap(KC_LGUI, KC_C);
            }
            break;
        case COMBO_PASTE:  // Paste
            if (pressed) {
                mod_tap(KC_LGUI, KC_V);
            }
            break;
    }
}
