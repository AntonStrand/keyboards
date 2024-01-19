#include "antonstrand.h"

uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        // To make the switch to the hold state feel more responsive the
        // check for interuption has been removed. This became an issue
        // when you quickly wanted to switch from typing to using the arrow keys.
        if (!state->pressed)
            return SINGLE_TAP;
        else
            return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TRIPLE_TAP;
        else
            return TRIPLE_HOLD;
    } else
        return 8;  // Magic number. At some point this method will expand to work for more presses
}

// Create an instance of 'tap'.
static tap rs_spc_ent_tap_state = {.is_press_action = true, .state = 0};

void rs_spc_ent_finished(qk_tap_dance_state_t *state, void *user_data) {
    rs_spc_ent_tap_state.state = cur_dance(state);
    switch (rs_spc_ent_tap_state.state) {
        case SINGLE_TAP:
            tap_code(KC_SPC);
            break;
        case SINGLE_HOLD:
            layer_on(_RAISE);
            break;
        case DOUBLE_TAP:
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_ENT);
            break;
        case DOUBLE_HOLD:
            tap_code(KC_ENT);
            layer_on(_RAISE);
            break;
    }
}

void rs_spc_ent_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (rs_spc_ent_tap_state.state) {
        case SINGLE_HOLD:
            layer_off(_RAISE);
            break;
        case DOUBLE_HOLD:
            layer_off(_RAISE);
            break;
    }
    rs_spc_ent_tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {[RS_SPC_ENT] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, rs_spc_ent_finished, rs_spc_ent_reset, 250)};