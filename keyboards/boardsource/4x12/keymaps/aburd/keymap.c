// Copyright 2022 @waffle87
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum layers {
    _MAIN,
    _RAISE,
    _LOWER,
    _NUMBER,
    _MOUSE,
};

enum keycodes {
  ARROW // "->"
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define NUMBER MO(_NUMBER)
#define MOUSE  MO(_MOUSE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT_ortho_4x12(
      KC_ESC        , KC_Q,       KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,    KC_U,    KC_I,           KC_O,    KC_P,    KC_BSPC,
      LCTL_T(KC_TAB), KC_A,       KC_S,    KC_D,    KC_F,    KC_G,   KC_H,    KC_J,    KC_K,           KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT       , KC_Z,       KC_X,    KC_C,    KC_V,    KC_B,   KC_N,    KC_M,    KC_COMM,        KC_DOT,  KC_SLSH, KC_ENT ,
      NUMBER        , KC_MS_BTN1, KC_LALT, KC_LGUI, LOWER,   MOUSE,  KC_SPC,  RAISE,   SFT_T(KC_LEFT), KC_DOWN, KC_UP,   KC_RGHT
  ),
  [_LOWER] = LAYOUT_ortho_4x12(
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC,  KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
      _______,  _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
      _______, _______, _______, _______, _______, _______, KC_HOME,  KC_PGDN, KC_PGUP,  KC_END, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
  ),
  [_RAISE] = LAYOUT_ortho_4x12(
      KC_GRV,  _______, _______, _______, _______, _______, _______, KC_LCBR, KC_RCBR, ARROW,   _______, KC_BSPC,
      _______, _______, _______, KC_MINS, KC_EQL,  KC_GRV,  _______, KC_LPRN, KC_RPRN, _______, KC_PIPE, KC_DEL,
      _______, _______, _______, KC_UNDS, KC_PLUS, _______, _______, KC_LBRC, KC_RBRC, _______, KC_BSLS, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  /* Number,
   * ,----------------------------------l-------------------------------------------------.
   * |      |      |  F1  |  F2  |  F3  | Mute | Pl/Ps|  7   |  8   |  9   |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |  F4  |  F5  |  F6  | Vol- | Vol+ |  4   |  5   |  6   |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |  F7  |  F8  |  F9  | Prev | Next |  1   |  2   |  3   |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |  F10 |  F11 |  F12 |  .   |  .   |  0   |  .   |  .   |      |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_NUMBER] = LAYOUT_ortho_4x12(
      _______, _______, KC_F1,   KC_F2,   KC_F3,  KC_MUTE, KC_MPLY, KC_7, KC_8,   KC_9,    _______, _______,
      _______, _______, KC_F4,   KC_F5,   KC_F6,  KC_VOLD, KC_VOLU, KC_4, KC_5,   KC_6,    _______, _______,
      _______, _______, KC_F7,   KC_F8,   KC_F9,  KC_MPRV, KC_MNXT, KC_1, KC_2,   KC_3,    _______, _______,
      _______, _______, KC_F10,  KC_F11,  KC_F12, KC_DOT,  KC_DOT,  KC_0, KC_DOT, KC_DOT,  _______, _______
  ),
  [_MOUSE] = LAYOUT_ortho_4x12(
      _______, _______, _______, _______, _______, _______, _______,    _______,    _______,  _______, _______, _______,
      _______, _______, _______, _______, _______, _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,    _______,    _______,  _______, _______, _______,
      _______, _______, _______, _______, _______, _______, KC_MS_BTN1, KC_MS_BTN2, _______,  _______, _______, _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ARROW:
      if (record->event.pressed) {
        uint8_t mod_state = get_mods();
        // send fat arrow if shift is held
        if (mod_state & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT);
          SEND_STRING("=>");
          set_mods(mod_state);
        } else {
          SEND_STRING("->");
        }
      }
      break;
  }
  return true;
}
