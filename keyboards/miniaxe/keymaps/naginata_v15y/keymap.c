/* Copyright 2018 ENDO Katsuhiro <ka2hiro@curlybracket.co.jp>
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
#include "os_detection.h"
#include "keymap_japanese.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

// Defines the keycodes used by our macros in process_record_user
enum layer_names {
    _QWERTY,
// 薙刀式
    _NAGINATA, // 薙刀式入力レイヤー
// 薙刀式
    _LOWER,
    _RAISE,
    _ADJUST
}; 

enum custom_keycodes {
  QWERTY = NG_SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define CTLSPC  CTL_T(KC_SPC)
#define CTLENT  CTL_T(KC_ENT)

const uint16_t PROGMEM ent_combo[] = {KC_V, KC_M, COMBO_END};
combo_t key_combos[] = {COMBO(ent_combo, KC_ENT)};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_split_3x5_3(
  KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,         KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,
  KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,         KC_H   ,KC_J   ,KC_K   ,KC_L   ,JP_MINS,
  MT(MOD_LCTL,KC_B),KC_Z   ,KC_C   ,KC_V   ,KC_X   ,         KC_N   ,KC_M   ,JP_COMM,JP_DOT ,JP_SLSH,
                    KC_LSFT, LOWER,KC_SPC ,KC_SPC , RAISE,KC_RSFT
),

[_LOWER] = LAYOUT_split_3x5_3(
  KC_ESC ,JP_TILD,JP_AT  ,JP_HASH,JP_PERC,         JP_SLSH,KC_7   ,KC_8   ,KC_9   ,JP_MINS,
  KC_TAB ,JP_CIRC,JP_AMPR,JP_QUOT,JP_DOT ,         JP_ASTR,KC_4   ,KC_5   ,KC_6   ,JP_PLUS,
  RCS(KC_8),LCTL(KC_Z),LCTL(KC_C),LCTL(KC_V),LCTL(KC_X),      KC_0   ,KC_1   ,KC_2   ,KC_3   ,JP_EQL ,
                    _______, _______, _______,      _______, _______, _______
),

[_RAISE] = LAYOUT_split_3x5_3(
  KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,         XXXXXXX,KC_BSPC ,KC_INT4,KC_DEL,XXXXXXX,
  KC_F7  ,KC_F10 ,JP_EXLM,JP_QUES,XXXXXXX,         KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,LSFT(KC_ENT),
  LCTL(KC_F),LCTL(KC_Z),LCTL(KC_C),LCTL(KC_V),LCTL(KC_X),         S(KC_LEFT),S(KC_DOWN),S(KC_UP  ),S(KC_RGHT),LALT(KC_ENT),
                    _______, _______, _______,      _______,  _______, _______
),

[_ADJUST] =  LAYOUT_split_3x5_3(
  XXXXXXX,NG_TAYO,NGSW_WIN,NG_KOTI,NG_SHOS,         NG_SHOS,NGSW_LNX,NGSW_MAC,XXXXXXX,XXXXXXX,
  KC_LGUI,JP_PIPE,JP_DQUO ,JP_LPRN,KC_LT  ,         KC_GT  ,JP_RPRN,JP_GRV ,JP_DLR ,KC_RALT,
  KC_LCTL,JP_UNDS,JP_COLN,JP_LBRC,JP_LCBR,         JP_RCBR,JP_RBRC,JP_COMM,JP_BSLS,KC_RCTL,
                    _______, _______, _______,      _______,  _______, _______
),

// 薙刀式
[_NAGINATA] = LAYOUT_split_3x5_3(
  NG_Q,    NG_W,    NG_E,    NG_R,    NG_T,         NG_Y,    NG_U,    NG_I,    NG_O,    NG_P,
  NG_A,    NG_S,    NG_D,    NG_F,    NG_G,         NG_H,    NG_J,    NG_K,    NG_L,    NG_SCLN,
  NG_Z,    NG_X,    NG_C,    NG_V,    NG_B,         NG_N,    NG_M,    NG_COMM, NG_DOT,  NG_SLSH,
                    _______, _______, NG_SHFT,      NG_SHFT,  _______, _______
),
// 薙刀式

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        // persistant_default_layer_set(1UL<<_QWERTY);
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }

  // 薙刀式
  if (!process_naginata(keycode, record))
    return false;
  // 薙刀式

  return true;
}

void keyboard_post_init_user(void) {
  // 薙刀式
  uint16_t ngonkeys[] = {KC_H, KC_J};
  uint16_t ngoffkeys[] = {KC_F, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
  // 薙刀式

  wait_ms(400);
  switch (detected_host_os()) {
    case OS_WINDOWS:
      switchOS(NG_WIN);
      break;
    case OS_MACOS:
    case OS_IOS:
      switchOS(NG_MAC);
      break;
    case OS_LINUX:
      switchOS(NG_LINUX);
      break;
    default:
      switchOS(NG_WIN);
  }

}
