
#pragma once

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "action.h"
#include "version.h"
#include "combos_config.h"
#ifdef TAP_DANCE_ENABLE
#    include "tap_dance.h"
#endif

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _RAPID,
    _ADJUST,
    _NUMBER,
    _FN,
    _SNAKE,
    _CAMEL,
    _GAME,
    _GAME_NUMS
    //
};
#define ______ KC_TRNS

#define CK_CUT LGUI(KC_X)
#define CK_COPY LGUI(KC_C)
#define CK_PASTE LGUI(KC_V)
#define CK_UNDO LGUI(KC_Z)
#define CK_REDO S(CK_UNDO)
#define VSC_PREV C(SE_MINS)
#define VSC_NEXT S(VSC_PREV)
#define PRNT_ALL S(LGUI(KC_3))
#define PRNT_SEL S(LGUI(KC_4))
#define PRNT_MENU S(LGUI(KC_5))

#define LCTL_A LCTL_T(KC_A)
#define LSFT_S LSFT_T(KC_S)
#define LALT_D LALT_T(KC_D)
#define LGUI_F LGUI_T(KC_F)

#define RC_ODIA RCTL_T(SE_ODIA)
#define RS_L RSFT_T(KC_L)
#define RA_K RALT_T(KC_K)
#define RG_J RGUI_T(KC_J)
#define NUM_V LT(_NUMBER, KC_V)

#define SFT_QUOT RSFT_T(SE_QUOT)
#define SLEEP G(A(KC_EJCT))
#define TG_CMT G(SE_SLSH)

#define TD_RAISE TD(RS_SPC_ENT)

#define RSE_ENT LT(_RAISE, KC_ENT)
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define NUMBER TT(_NUMBER)
#define RAPID MO(_RAPID)
#define TG_NUM TG(_NUMBER)
#define TT_FN TT(_FN)
#define G_NUM MO(_GAME_NUMS)
#define GAME TG(_GAME)

// Define all of
enum custom_keycodes {
    NO_KEY_PRESS = (UINT16_MAX - 1),
    PIPE         = SAFE_RANGE,
    COMPOSE,
    SKINNY_ARROW,
    FAT_ARROW,
    APP,
    R_LEFT,
    R_DOWN,
    R_UP,
    R_RIGHT,
    COMPILE,
    FLASH,
    MAKE_ALL,
    CK_BASE,
    GUI_QM,
    GH_PR,
    GH_PBRN,
    GH_OBRN,
    GH_OPEN,
    KEYMAP_RANGE  // use "KEYMAP_RANGE" for keymap specific codes
};

void repeat_pressed_key(void);
void set_color(int from, int to, int r, int g, int b);
void set_pressed_key(uint16_t key, bool is_pressed, bool scroll_fast);
void handle_pressed_key(void);
void tap_hold_mod(uint16_t mod, uint16_t kc, bool is_pressed);
void mod_tap(uint16_t mod, uint16_t kc);
void compile_keyboard(void);
void flash_keyboard(void);
