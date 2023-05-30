/* Copyright 2020 eswai
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
#include "twpair_on_jis.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
#define NAGINATA_TIMEOUT 15000
// 薙刀式

// Defines names for use in layer keycodes and the keymap
enum layer_names {
   _MAC,
   _WIN,
// 薙刀式
  _NAGINATA, // 薙刀式入力レイヤー
// 薙刀式
  _LOWER,
  _RAISE,
  _ADJUST,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    KANAON = NG_SAFE_RANGE,
    EISUON,
    PASTE,
};

uint32_t oled_sleep_timer;
uint32_t naginata_timer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_WIN] = LAYOUT(
    KC_TAB        ,KC_Y   ,KC_R   ,KC_O    ,KC_U   ,KC_COMM, C(KC_X)  , C(KC_Z) ,KC_DOT ,KC_BSPC,KC_L   ,KC_F   ,KC_P    ,KC_QUOT , 
    CTL_T(KC_ESC) ,KC_D   ,KC_S   ,KC_A    ,KC_I   ,KC_G   , C(KC_C)  , C(KC_S) ,KC_J   ,KC_E   ,KC_H   ,KC_T   ,KC_K    ,KC_SCLN , 
    KC_LSFT       ,KC_V   ,KC_Z   ,KC_X    ,KC_M   ,KC_C   , C(KC_V)  , C(KC_Y) ,KC_N   ,KC_W   ,KC_B   ,KC_Q   ,KC_SLSH ,KC_RSFT   , 
    KC_LCTL       ,KC_LALT,KC_LWIN,KC_LCTL,MO(_LOWER),LSFT_T(KC_SPC)  ,LSFT_T(KC_ENT)   ,MO(_RAISE),KC_LEFT,KC_DOWN,KC_UP,KC_RGHT
    ),

  [_MAC] = LAYOUT(
    KC_TAB        ,KC_K   ,KC_D   ,KC_N    ,KC_F   ,KC_Q   , G(KC_X)  , G(KC_Z) ,KC_J   ,KC_BSPC,KC_R   ,KC_U   ,KC_P    ,KC_QUOT , \
    CMD_T(KC_ESC) ,KC_W   ,KC_I   ,KC_S    ,KC_A   ,KC_G   , G(KC_C)  , G(KC_S) ,KC_Y   ,KC_E   ,KC_T   ,KC_H   ,KC_B    ,KC_SCLN , \
    KC_LSFT       ,KC_Z   ,KC_X   ,KC_V    ,KC_C   ,KC_L   , PASTE    , G(KC_Y) ,KC_M   ,KC_O   ,KC_COMM,KC_DOT ,KC_SLSH ,KC_RSFT , \
    KC_LCTL       ,KC_LALT,KC_LCTL,KC_LCMD,MO(_LOWER),LSFT_T(KC_SPC)  ,LSFT_T(KC_ENT)   ,MO(_RAISE),KC_LEFT,KC_DOWN,KC_UP,KC_RGHT
    ),

  // [_QWERTY] = LAYOUT(
  //   KC_TAB        ,KC_Q   ,KC_W   ,KC_E    ,KC_R   ,KC_T   ,G(KC_X)   ,G(KC_Z)  ,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P    ,KC_QUOT , 
  //   CTL_T(KC_ESC) ,KC_A   ,KC_S   ,KC_D    ,KC_F   ,KC_G   ,G(KC_C)   ,G(KC_S)  ,KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN ,KC_SCLN , 
  //   KC_LSFT       ,KC_Z   ,KC_X   ,KC_C    ,KC_V   ,KC_B   ,G(KC_V)   ,G(KC_Y)  ,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH ,KC_RSFT   , 
  //   KC_LCTL       ,KC_LALT,KC_LWIN,KC_LCTL,MO(_LOWER),LSFT_T(KC_SPC)  ,LSFT_T(KC_ENT)   ,MO(_RAISE),KC_LEFT,KC_UP,KC_DOWN ,KC_RGHT
  //   ),

  [_LOWER] = LAYOUT(
    _______ ,XXXXXXX ,XXXXXXX ,KC_COLN ,KC_SCLN ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_SLSH ,KC_7   ,KC_8   ,KC_9   ,KC_MINS ,KC_DEL , \
    _______ ,XXXXXXX ,KC_LBRC ,KC_LCBR ,KC_LPRN ,KC_LT   ,XXXXXXX ,XXXXXXX ,KC_ASTR ,KC_4   ,KC_5   ,KC_6   ,KC_PLUS ,_______, \
    _______ ,XXXXXXX ,KC_RBRC ,KC_RCBR ,KC_RPRN ,KC_GT   ,XXXXXXX ,XXXXXXX ,KC_0    ,KC_1   ,KC_2   ,KC_3   ,KC_EQL  ,_______, \
    QK_BOOT ,_______ ,_______ ,_______ ,_______ ,_______,                   KANAON  ,_______,_______,_______,_______ ,_______
  ),

  [_RAISE] = LAYOUT(
    _______   ,KC_TILD   ,KC_AT     ,KC_HASH   ,KC_DLR    ,XXXXXXX,      XXXXXXX, XXXXXXX ,XXXXXXX   ,KC_HOME   ,KC_UP     ,KC_END    ,XXXXXXX   ,KC_DEL    , \
    _______   ,KC_CIRC   ,KC_AMPR   ,KC_QUES   ,KC_PERC   ,KC_INT3,      XXXXXXX, XXXXXXX ,XXXXXXX   ,KC_LEFT   ,KC_DOWN   ,KC_RGHT   ,XXXXXXX   ,XXXXXXX   , \
    _______   ,KC_GRV    ,KC_PIPE   ,KC_EXLM   ,KC_UNDS   ,LALT(KC_INT3),XXXXXXX, XXXXXXX ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,_______   , \
    _______   ,_______   ,_______   ,_______   ,_______   ,EISUON      ,           _______        ,_______   ,_______   ,_______   ,_______   ,_______
  ),

  [_ADJUST] = LAYOUT(
    _______,EE_CLR ,QK_BOOT,KC_F1   ,KC_F2  ,KC_F3   ,KC_F4,  NG_TAYO,NGSW_WIN,XXXXXXX,XXXXXXX,QK_BOOT,XXXXXXX,_______, \
    _______,XXXXXXX,KC_SLEP,KC_F5   ,KC_F6  ,KC_F7   ,KC_F8,  NG_KOTI,NGSW_MAC,NG_MLV ,XXXXXXX,XXXXXXX,XXXXXXX,_______, \
    _______,XXXXXXX,KC_WAKE,KC_F9   ,KC_F10 ,KC_F11  ,KC_F12, NG_SHOS,NGSW_LNX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______, \
    _______,_______,_______,_______,_______,     XXXXXXX,        XXXXXXX,_______,_______,_______,_______,_______
  ),
//     _______,XXXXXXX,KC_WAKE,KC_F9   ,KC_F10 ,KC_F11  ,KC_F12, NG_SHOS,NGSW_LNX,XXXXXXX,DF(_BASE),DF(_QWERTY),DF(_MAC),_______, 

  [_NAGINATA] = LAYOUT(
    _______,NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,_______, _______,NG_Y   ,NG_U   ,NG_I   ,NG_O   ,NG_P   ,_______, \
    _______,NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,_______, _______,NG_H   ,NG_J   ,NG_K   ,NG_L   ,NG_SCLN,_______, \
    _______,NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,_______, _______,NG_N   ,NG_M   ,NG_COMM,NG_DOT ,NG_SLSH,_______, \
    _______,_______,_______,_______,_______,   NG_SHFT,         NG_SHFT2,_______,_______,_______,_______,_______
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  oled_sleep_timer = timer_read32() + OLED_TIMEOUT;
  naginata_timer = timer_read32() + NAGINATA_TIMEOUT;

  switch (keycode) {
    case EISUON:
      if (record->event.pressed) {
        // 薙刀式
        naginata_off();
        // 薙刀式
      }
      return false;
      break;
    case KANAON:
      if (record->event.pressed) {
        // 薙刀式
        naginata_on();
        // 薙刀式
      }
      return false;
      break;
    case PASTE: // VS Codeのプチフリ対策
      if (record->event.pressed) {
        register_code(KC_LCMD);
        wait_ms(40);
        tap_code(KC_V);
        unregister_code(KC_LCMD);
      }
      return false;
      break;
  }

  // 薙刀式
  if (!process_naginata(keycode, record))
    return false;
  // 薙刀式

  // typewriter pairing on jis keyboard
  if (!twpair_on_jis(keycode, record))
    return false;

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void keyboard_post_init_user(void) {
  // 薙刀式
  uint16_t ngonkeys[] = {KC_Y, KC_E};
  uint16_t ngoffkeys[] = {KC_A, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
  // 薙刀式

  wait_ms(400);
  switch (detected_host_os()) {
    case OS_WINDOWS:
      layer_move(_WIN);
      switchOS(NG_WIN);
      break;
    case OS_MACOS:
    case OS_IOS:
      layer_move(_MAC);
      switchOS(NG_MAC);
      break;
    case OS_LINUX:
      layer_move(_WIN);
      switchOS(NG_LINUX);
      break;
    default:
      layer_move(_WIN);
      switchOS(NG_WIN);
  }

  oled_sleep_timer = timer_read32() + OLED_TIMEOUT;
  naginata_timer = timer_read32() + NAGINATA_TIMEOUT;
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}

/*
    薙刀式ロゴの著作権は大岡俊彦氏に帰属します。
    http://oookaworks.seesaa.net
*/
static void naginata_logo(void) {
    static const char PROGMEM ng_logo[] = {
      0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x40, 0x30, 0xf0, 0xf0, 0xe8, 0xe8, 0xc, 0xc, 0x4, 0x4, 0x4, 0xc, 0xc, 0xc8, 0xe8, 0xe8, 0xf0, 0x30, 0x40, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xe0, 0xe0, 0xa0, 0x80, 0x80, 0x80, 0xe0, 0xe0, 0xa0, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0x80, 0x0, 0x0, 0x0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe0, 0xe0, 0x20, 0x40, 0xc0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x79, 0x9b, 0xe3, 0xf3, 0xf3, 0xf3, 0xf7, 0x77, 0x8f, 0xcf, 0x3, 0x43, 0x43, 0x3, 0x83, 0xef, 0xff, 0xf7, 0xf7, 0xb3, 0xd3, 0xe3, 0xb3, 0x9b, 0xa9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x60, 0x38, 0x1e, 0xf6, 0xf0, 0x13, 0x1b, 0x50, 0x60, 0xf8, 0xfe, 0x97, 0x91, 0xf8, 0xfe, 0x94, 0x90, 0xd8, 0x90, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0xfe, 0x7f, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0x1, 0x0, 0x0, 0x0, 0x0, 0x2, 0x42, 0x42, 0x42, 0x42, 0xc2, 0xc2, 0x42, 0x62, 0x72, 0x62, 0xf, 0xff, 0xc2, 0x2, 0x2, 0x2, 0x3, 0x3, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x87, 0xd9, 0x35, 0x5b, 0xcc, 0x86, 0x3, 0x37, 0x76, 0x76, 0x62, 0x0, 0x3, 0x7f, 0x3f, 0x1f, 0x60, 0x6a, 0xff, 0x6f, 0x6a, 0x60, 0x6e, 0x60, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x82, 0x62, 0x32, 0x1f, 0xf, 0x12, 0x73, 0x63, 0x2, 0xff, 0xff, 0x88, 0x88, 0xff, 0xff, 0x88, 0x88, 0xcc, 0xc8, 0x80, 0x0, 0x0, 0x80, 0xc0, 0x40, 0x20, 0x38, 0xe, 0x7, 0x1, 0x0, 0x0, 0x40, 0x40, 0xc0, 0xc0, 0xf0, 0x7f, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0xe0, 0x60, 0x60, 0x20, 0x3f, 0x3f, 0x10, 0x10, 0x8, 0x8, 0x0, 0x1, 0xf, 0x1e, 0x78, 0xe0, 0xc0, 0xf0, 0x9c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x22, 0x37, 0x32, 0x18, 0xc, 0x6, 0x3, 0x1, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x3, 0x3, 0x2, 0x2, 0x2, 0x2, 0x2, 0x3, 0x3, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
    };
    oled_write_raw_P(ng_logo, sizeof(ng_logo));
}

static void delete_char(uint16_t x, uint16_t w) {
  for (uint16_t i = x; i < x + w; i++) {
    oled_write_raw_byte(0x00, i);
  }
}

static void render_mode(void) {
    switch (naginata_config.os) {
      case NG_WIN:
        delete_char(12, 14);
        break;
      case NG_MAC:
        delete_char(5, 7);
        delete_char(19, 7);
        break;
      case NG_LINUX:
        delete_char(5, 14);
        break;
    }
    if (naginata_config.tategaki) {
      delete_char(128 + 12, 7);
    } else {
      delete_char(128 + 5, 7);
    }
    if (!naginata_config.kouchi_shift) {
      delete_char(2 * 128 + 5, 7);
    }
    if (!naginata_config.live_conv) {
      delete_char(3 * 128 + 5, 7);
    }
}

static void render_kana(void) {
    static const char PROGMEM kana_pic[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xc1, 0xbf, 0xc7, 0xbf, 0xc1, 0xff, 0xff, 0x81, 0xfb, 0xe7, 
      0xfb, 0x81, 0xff, 0xff, 0x81, 0xbf, 0xbf, 0xbf, 0xbf, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
      0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7e, 0x7e, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
      0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xfc, 0xf0, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf9, 0xfd, 0x81, 0xfd, 0xf9, 0xff, 0xff, 0xf9, 0xf7, 0x8f, 
      0xf7, 0xf9, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
      0xff, 0xff, 0xf3, 0xf3, 0xf3, 0x73, 0x23, 0x00, 0x00, 0x33, 0x33, 0x33, 0x03, 0x09, 0x19, 0x39, 
      0x79, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x81, 0xef, 0xd7, 0xbb, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
      0xff, 0xff, 0x03, 0x01, 0x38, 0x3c, 0x3c, 0x00, 0x80, 0xc7, 0x63, 0x70, 0x7c, 0x3e, 0x3e, 0x1e, 
      0x80, 0xc0, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x81, 0xbf, 0xbf, 0xbf, 0xbf, 0xff, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x3f, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
      0x7f, 0x7f, 0x7f, 0x7f, 0x7e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7f, 
      0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x1f, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(kana_pic, sizeof(kana_pic));
}

static void render_eisu(void) {
    static const char PROGMEM eisu_pic[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xc1, 0xbf, 0xc7, 0xbf, 0xc1, 0xff, 0xff, 0x81, 0xfb, 0xe7, 
      0xfb, 0x81, 0xff, 0xff, 0x81, 0xbf, 0xbf, 0xbf, 0xbf, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0x1c, 0x0e, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 
      0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 
      0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x0e, 0x1c, 0xfc, 0xf0, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf9, 0xfd, 0x81, 0xfd, 0xf9, 0xff, 0xff, 0xf9, 0xf7, 0x8f, 
      0xf7, 0xf9, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8, 0xfe, 0x7f, 0x1f, 0x7f, 0xfe, 0xf8, 0xe0, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x81, 0xef, 0xd7, 0xbb, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x80, 0xe0, 0xfc, 0xff, 0x7f, 0x1f, 0x1f, 0x1c, 0x1c, 0x1c, 0x1f, 0x1f, 0x7f, 0xff, 
      0xfc, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x81, 0xbf, 0xbf, 0xbf, 0xbf, 0xff, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x3f, 0x38, 0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
      0x60, 0x60, 0x61, 0x61, 0x61, 0x61, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x61, 
      0x61, 0x61, 0x61, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x70, 0x38, 0x3f, 0x0f, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(eisu_pic, sizeof(eisu_pic));
}

bool oled_task_user(void) {
    if (timer_expired32(timer_read32(), naginata_timer)) {
      if (naginata_state()) {
        naginata_off();
      }
    }

    // なぜかマスター側は明示的にOLEDのスリープ処理が必要
    if (is_keyboard_master()) {
      if (timer_expired32(timer_read32(), oled_sleep_timer)) {
        if (is_oled_on()) {
          oled_off();
        }
        return false;;
      } else {
        if (!is_oled_on())
          oled_on();
      }
    }

    if (is_keyboard_master()) {
      if (naginata_state()) {
        render_kana();
      } else {
        render_eisu();
      }
      render_mode();
    } else {
        naginata_logo();
    }
    return false;
}
#endif