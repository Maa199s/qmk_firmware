// Copyright 2022 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    LAYOUT(
        LT(7, KC_Q), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
        KC_A, KC_S, LT(6, KC_D), KC_F, KC_G, KC_H, KC_J, LT(6, KC_K), KC_L, KC_ENT, 
        LSFT_T(KC_Z), LGUI_T(KC_X), KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, LCTL_T(KC_DOT), KC_BSPC, 
        KC_LCTL, KC_LGUI, LALT_T(KC_LNG2), LSFT_T(KC_TAB), LT(2, KC_SPC), LT(1, KC_LNG1), KC_PGUP, KC_PGDN
    ),
    
    // 薙刀式レイヤー
    LAYOUT(
        NG_Q, NG_W, NG_E, NG_R, NG_T, NG_Y, NG_U, NG_I, NG_O, NG_P, 
        NG_A, NG_S, NG_D, NG_F, NG_G, NG_H, NG_J, NG_K, NG_L, NG_SCLN, 
        NG_Z, NG_X, NG_C, NG_V, NG_B, NG_N, NG_M, NG_COMM, NG_DOT, NG_SLSH, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
        LCTL_T(KC_EQL), KC_LBRC, KC_SLSH, KC_MINS, KC_INT1, KC_SCLN, KC_QUOT, KC_RBRC, KC_NUHS, KC_INT3, 
        LSFT_T(KC_PLUS), KC_LCBR, KC_QUES, KC_UNDS, LSFT(KC_INT1), KC_COLN, KC_DQUO, KC_RCBR, LSFT(KC_NUHS), LSFT(KC_INT3), 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, LGUI(KC_INT3), 
        KC_PLUS, KC_LCBR, KC_QUES, KC_UNDS, LSFT(KC_INT1), KC_COLN, KC_DQUO, KC_RCBR, LSFT(KC_NUHS), LSFT(KC_INT3), 
        KC_LSFT, KC_LGUI, KC_LALT, KC_LNG2, KC_LSFT, KC_SPC, KC_LNG1, KC_TRNS, KC_TRNS, KC_DEL, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        LT(7, KC_Q), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
        KC_A, KC_S, LT(6, KC_D), KC_F, KC_G, KC_H, KC_J, LT(6, KC_K), KC_L, KC_ENT, 
        LSFT_T(KC_Z), LGUI_T(KC_X), KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, LCTL_T(KC_DOT), KC_BSPC, 
        KC_LCTL, KC_LGUI, LALT_T(KC_LNG2), LSFT_T(KC_TAB), LT(5, KC_SPC), LT(4, KC_LNG1), KC_PGUP, KC_PGDN
    ),
        
    LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
        KC_CIRC, KC_AT, KC_SLSH, KC_MINS, KC_UNDS, KC_SCLN, KC_COLN, KC_LBRC, KC_RBRC, KC_INT3, 
        LT(5, KC_TILD), KC_GRV, KC_QUES, KC_EQL, KC_UNDS, KC_PLUS, KC_ASTR, KC_LCBR, KC_RCBR, KC_PIPE, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        KC_EXLM, KC_DQUO, KC_HASH, KC_DLR, KC_PERC, KC_AMPR, KC_QUOT, KC_LPRN, KC_RPRN, KC_BSLS,
        KC_TILD, KC_GRV, KC_QUES, KC_EQL, KC_UNDS, KC_PLUS, KC_ASTR, KC_LCBR, KC_RCBR, KC_PIPE,
        KC_LSFT, KC_LGUI, KC_LALT, KC_LNG2, KC_LSFT, KC_SPC, KC_LNG1, KC_TRNS, KC_TRNS, KC_DEL,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        KC_ESC, KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, 
        KC_LCTL, KC_TRNS, KC_QUES, KC_EXLM, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, 
        KC_LSFT, KC_LGUI, KC_LALT, KC_LNG2, KC_TRNS, KC_NO, KC_LNG1, KC_NO, KC_NO, KC_DEL, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ), 
    
    LAYOUT(
        KC_NO, KC_TAB, KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, MO(8), MO(9), 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, KC_NO, KC_NO, DF(0), DF(3), 
        RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        RGB_M_K, RGB_M_X, RGB_M_G, KC_NO, KC_NO, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // 薙刀式
  if (!process_naginata(keycode, record))
    return false;
  // 薙刀式

  return true;
}

void keyboard_post_init_user(void) {
  // 薙刀式
  uint16_t ngoffkeys[] = {KC_F, KC_G};
  uint16_t ngonkeys[] = {KC_H, KC_J};
  set_naginata(1, ngonkeys, ngoffkeys);
  // 1は薙刀式レイヤーの番号
  // 薙刀式

}
