/* Copyright 2019
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

#define _QW 0
#define _LW 1
#define _RS 2
#define _OT 3 
#define _CP 4


//define TAPPING_TOGGLE 2 under config.h

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QW] = LAYOUT( /* Qwerty */
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT ,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_LSFT, KC_QUOT),
  KC_LCTL, TT(_OT), KC_LGUI, KC_LALT, 
      TT(_LW), 
      LT(_RS, KC_SPC),  
      KC_SPC,  
      LM(_CP, MOD_LCTL), 
   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT),
[_LW] = LAYOUT( /* lower */
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS, KC_7,    KC_8,    KC_9,    KC_TRNS, KC_TRNS,
  KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINUS,KC_TRNS,
  KC_TRNS, KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH, KC_EQL,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(_LW), KC_TRNS, KC_TRNS, KC_0,    KC_0,    KC_DOT,  KC_COMM, KC_ESC),
[_RS] = LAYOUT( /* raise */
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH,   KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
  KC_TRNS, KC_INS,  KC_HOME, KC_PGUP,   KC_TRNS, KC_TRNS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_UNDS, KC_TRNS, 
  KC_TRNS, KC_DELETE,KC_END, KC_PGDN,   KC_TRNS, KC_TRNS,  KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_BSLS, KC_PIPE,
  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(_RS), KC_HOME, KC_PGDN, KC_PGUP, KC_END),
[_OT] = LAYOUT( /* mouse */
  KC_TRNS, KC_TRNS, KC_MS_U, KC_WH_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS ,
  KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS ,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_D, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS ,
  KC_TRNS, TG(_OT), KC_TRNS, KC_TRNS, KC_MS_BTN1, KC_MS_BTN2, KC_TRNS, KC_MS_BTN3, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY),
[_CP] = LAYOUT( /* right hand copy paste */
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_C,    KC_V,    KC_X ,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS ,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS ,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS )

};