/* Copyright 2020 Anton Strand base on tominabox1's default layout
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keymap_swedish_mac.h"
#include "quantum.h"
#include "sendstring_swedish_mac.h"
#include "space_cadet.c"
#include "version.h"

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _RAPID,
  _ADJUST,
  _NUMBER,
  _NUM_PAD,
  _FN,
  _GAME,
  _GAME_NUMS
  //
};

#define ______ KC_TRNS

#define LWR_BSP LT(_LOWER, KC_BSPC)
#define NUM_SPC LT(_NUMBER, KC_SPC)

#define CTRL_ESC LCTL_T(KC_ESC)

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

#define LALT_D LALT_T(KC_D)
#define LGUI_F LGUI_T(KC_F)

#define RA_K RALT_T(KC_K)
#define RG_J RGUI_T(KC_J)

#define SFT_QUOT RSFT_T(SE_QUOT)
#define SLEEP G(A(KC_EJCT))
#define TG_CMT G(SE_SLSH)

#define RSE_ENT LT(_RAISE, KC_ENT)
#define RAPID MO(_RAPID)

// Hack since OSM changes which key is being triggered
#define OSM_CTRALT OSM(KC_RSFT)
#define OSM_MEH OSM(KC_RGUI)
#define OSM_HYPR OSM(KC_RALT)
#define OSM_SHFT OSM(KC_LALT)
#define OSM_CTRL OSM(KC_LSFT)

// Define all of
enum custom_keycodes {
  NO_KEY_PRESS = (UINT16_MAX - 1),
  PIPE = SAFE_RANGE,
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
  CK_BASE,
  GUI_QM,
  CARET,
  BACKTICK,
  TILDE,
  KEYMAP_RANGE // use "KEYMAP_RANGE" for keymap specific codes
};

#include "repeat_key_press.c"

/**
 * Hold modifier until is_pressed is false. The key is tapped once when
 * is_presses becomes true.
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

void set_color(int from, int to, int r, int g, int b) {
#ifdef RGB_MATRIX_ENABLE
  int i;
  for (i = from; i <= to; i++) {
    rgb_matrix_set_color(i, r, g, b);
  }
#endif
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
      send_string("make bm40hsrgb" SS_TAP(X_ENTER));
    }
    return false;

  case FLASH:
    if (record->event.pressed) {
      send_string("make flash-bm40hsrgb" SS_TAP(X_ENTER));
      reset_keyboard();
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

  case CARET:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT("^ "));
    }
    return false;

  case TILDE:
    if (record->event.pressed) {
      SEND_STRING(SS_ALGR("~ "));
    }
    return false;

  case BACKTICK:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT("` "));
    }
    return false;
  }

  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off

    /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   Å  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ö  |   Ä  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   -  | Shft'|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Num  | Ctrl | Alt  | GUI  |BK/LWR|  Num/Space  |Ent/RS| Enter|  Alt | Ctrl | GUI? |
     * `-----------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_planck_mit(
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,    SE_ARNG,
        CTRL_ESC,  KC_A,    KC_S,    LALT_D,  LGUI_F,  KC_G,    KC_H,    RG_J,  RA_K,    KC_L,    SE_ODIA, SE_ADIA,
        OSM_SHFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,  KC_COMM, KC_DOT,  SE_MINS, SFT_QUOT,
        OSM_CTRL, KC_LCTL, KC_LALT, OSM_CTRL, LWR_BSP,    NUM_SPC,    RSE_ENT,  OSM_SHFT, KC_RALT, KC_RCTL, GUI_QM
    ),

    /* Lower (Nav)
     * ,-----------------------------------------------------------------------------------.
     * |   ~  |   "  |   '  |   |  |   &  |   ´  |   $  |   {  |   (  |  )   |  }   |   ^  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |   @  |  >>  |  ->  |   /  |  =>  |   #  |   [  |   ]  |   ;  |   :  |   `  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |   +  |   -  |   *  |   =  |  |>  |   %  |   \  |   <  |   >  |   _  |   '  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |Adjust|      |      |      |   !  |
     * `-----------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT_planck_mit(
        TILDE, SE_DQUO, SE_QUOT, SE_PIPE,      SE_AMPR, KC_EQL,    SE_DLR,  SE_LCBR, SE_LPRN, SE_RPRN, SE_RCBR, CARET,
        ______,  SE_AT,   COMPOSE, SKINNY_ARROW, SE_SLSH, FAT_ARROW, SE_HASH, SE_LBRC, SE_RBRC, SE_SCLN, SE_COLN, BACKTICK,
        ______,  SE_PLUS, SE_MINS, SE_ASTR,      SE_EQL,  PIPE,      SE_PERC, SE_BSLS, SE_LABK, SE_RABK, SE_UNDS, SE_QUOT,
        ______,  ______,  ______,  ______,       ______,        ______,       ______,  ______,  ______,  ______,  KC_EXLM
    ),

    /* Raise (Nav)
     * ,-----------------------------------------------------------------------------------.
     * | <Tab |Rec 2 |Play 2|Rec 1 |Play 1|      |      | Undo |  Cut | Copy | Paste| Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Del  | Ctrl | Shift|  Alt | GUI  |  App |  cmt | Left | Down |  Up  | Right|   '  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shift|Prnt S|Prnt A|Prnt M| Rapid|      |      |      |  C+O | Arep | Rep  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Num  | Ctrl | Alt  | GUI  |Adjust|     Del     |      |  GUI |  Alt | Ctrl |  FN  |
     * `-----------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT_planck_mit(
        S(KC_TAB), DM_REC2,  DM_PLY2,  DM_PLY1,   DM_REC1,    _______, CK_REDO, CK_UNDO,    CK_CUT,  CK_COPY,  CK_PASTE, KC_BSPC,
        _______,   KC_LCTL,  KC_LSFT,  KC_LALT,   KC_LGUI,    APP,      TG_CMT, KC_LEFT,    KC_DOWN, KC_UP,    KC_RGHT,  KC_BSLS,
        _______,   PRNT_SEL, PRNT_ALL, PRNT_MENU, MO(_RAPID), _______, _______, OSM_CTRALT, OSM_MEH, OSM_HYPR, _______,  KC_ENT,
        _______,   _______, _______, _______, _______,             _______,     _______,    _______, _______, _______,  _______
    ),

    [_RAPID] = LAYOUT_planck_mit(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, R_LEFT,  R_DOWN,  R_UP,    R_RIGHT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______
    ),

    /* Adjust (Lower + Raise)
    *                      v------------------------RGB CONTROL--------------------v
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      | Awake| Sleep|      | N Pad| Game |      |      | VolD | VolU |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      | Flash| Comp | Reset|      |      | Mute |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      | Base |
    * `-----------------------------------------------------------------------------------'
    */
    [_ADJUST] = LAYOUT_planck_mit(
        _______, _______, _______, RGB_TOG, RGB_MOD,      RGB_HUI,   RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL ,
        KC_CAPS, KC_WAKE, SLEEP,   _______, TG(_NUM_PAD), TG(_GAME), _______, _______, KC_VOLD, KC_VOLU, _______, _______,
        _______, _______, FLASH,   COMPILE, QK_BOOT,      _______,   _______, KC_MUTE, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,            _______,      _______, _______, _______, _______, CK_BASE
    ),

    /* Numbers
    * ,-----------------------------------------------------------------------------------.
    * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |  -   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   +  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |  /   |      |      |      |   _  |      |      |   $  |      |      |      |   *  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_NUMBER] = LAYOUT_planck_mit(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        SE_MINS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SE_PLUS,
        KC_SLSH, _______, _______, _______, SE_UNDS, _______, _______, SE_DLR,  _______, _______, _______, SE_ASTR,
        _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______
    ),
    /* Number
    * ,-----------------------------------------------------------------------------------.
    * |      |  F1  |  F2  |  F3  |  F4  |   (  |  )   |   1  |   2  |   3  |   +  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |  F5  |  F6  |  F7  |  F8  |   €  |  $   |   4  |   5  |   6  |   -  |  Del |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |  F9  |  F10 |  F11 |  F12 | Lock |  %   |   7  |   8  |   9  |   /  | Enter|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |   .  |   0  |   ,  |   *  |   =  |
    * `-------------------------------------------------------------------------v----------'
    */
    // [_NUM_PAD] = LAYOUT_planck_mit(
    //     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   SE_LPRN,  SE_RPRN,   KC_1,   KC_2, KC_3,    SE_PLUS, KC_BSPC,
    //     _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   SE_EURO,  SE_DLR,    KC_4,   KC_5, KC_6,    SE_MINS, KC_DEL,
    //     _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  TG_NUM,   SE_PERC,   KC_7,   KC_8, KC_9,    SE_SLSH, KC_ENT,
    //     _______, _______, _______, _______, _______,       _______,       KC_DOT, KC_0, KC_COMM, SE_ASTR, SE_EQL
    // ),

     /* Game
    * ,-----------------------------------------------------------------------------------.
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |Enter |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | BLTog| Ctrl | Alt  | GUI  |Space |Game numbers |Raise | Base | Left | Down |Right |
    * `-----------------------------------------------------------------------------------'
    */
    [_GAME] = LAYOUT_planck_mit(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_ENT ,
        RGB_TOG, KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  MO(_NUMBER),   RSE_ENT, CK_BASE, KC_LEFT, KC_DOWN, KC_RGHT
    ),

};

// clang-format on

/**
 * Colors based on Catppuccin Mocha
 * https://www.figma.com/community/file/1275541990963543565/catppuccin-mocha
 * https://github.com/catppuccin/palette/blob/main/palette.json
 */
#define MAUVE 0x88, 0x39, 0xEF
#define PEACH 0xFE, 0x64, 0xB0
#define MAROON 0xE6, 0x45, 0x53
#define YELLOW 0xDF, 0x8E, 0x1D
#define RED 0xD2, 0xF0, 0x39
#define SKY 0x89, 0xDC, 0xEB

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_kb(void) {
  switch (get_highest_layer(layer_state)) {
  case _RAISE:
    rgb_matrix_set_color_all(PEACH);
    break;
  case _LOWER:
    rgb_matrix_set_color_all(MAROON);
    break;
  case _NUMBER:
    rgb_matrix_set_color_all(MAUVE);
    set_color(13, 22, SKY);
    set_color(25, 34, SKY);
    break;
  case _ADJUST:
    rgb_matrix_set_color_all(RED);
    break;
  default:
    rgb_matrix_set_color_all(MAUVE);
    break;
  }
  const uint8_t mods = get_mods() | get_oneshot_mods() | get_weak_mods();
  if (mods == MOD_BIT(KC_LSFT) || (mods == MOD_BIT(KC_RSFT))) {
    set_color(1, 10, YELLOW);
    set_color(13, 22, YELLOW);
    set_color(25, 34, YELLOW);
    set_color(36, 45, YELLOW);
    return true;
  }
  return true;
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
