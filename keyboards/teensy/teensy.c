/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2018 Kenneth A. <github.com/krusli>

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

#include "teensy.h"
#include "ledmatrix.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
    ledMatrixInit();
}

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)
  ledMatrixDraw();

}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = 0;
    if (1UL<<1 & state) layer = 1;
    if (1UL<<2 & state) layer = 2;
    if (1UL<<3 & state) layer = 3;
    if (1UL<<4 & state) layer = 4;

    ledMatrixSetLayer(layer);
    return state;
}

void suspend_power_down_user(void) {
    ledMatrixSetOn(0);
}

void suspend_wakeup_init_user(void) {
    ledMatrixSetOn(1);
}
