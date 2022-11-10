/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    rwkb
#define PRODUCT         teensy

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

// Planck PCB default pin-out
// Change this to how you wired your keyboard
// COLS: Left to right, ROWS: Top to bottom
#define MATRIX_ROW_PINS { D4, D5, D6, D7 }
#define MATRIX_COL_PINS { D3, D2, D1, D0, B7, B6, B5, B4, B3, B2, B1, B0}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW


/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define USB_MAX_POWER_CONSUMPTION 100

/* key combination for magic key command */
/* defined by default; to change, uncomment and set to the combination you want */
// #define IS_COMMAND() (get_mods() == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)))

/* Bootmagic Lite key configuration */
// #define BOOTMAGIC_LITE_ROW 0
// #define BOOTMAGIC_LITE_COLUMN 0