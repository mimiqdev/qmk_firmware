/*
Copyright 2020 Holten Campbell

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

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_bs_rshift(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_RSFT,
		KC_LCTL, KC_LGUI,                   KC_LALT, MO(1),   KC_SPC,  KC_RALT,                                     KC_RGUI, KC_RGUI, KC_RCTL
    ),
    [1] = LAYOUT_split_bs_rshift(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_BSPC,
        _______, _______, KC_PGUP, _______, _______, _______, _______, _______, KC_UP,   _______, KC_MPRV, KC_MPLY, KC_MNXT,          _______,
        _______, KC_HOME, KC_PGDN, KC_END,  _______, KC_VOLD, KC_VOLU, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_PSCR, _______,
        _______, _______, _______,          _______,          _______,          _______,                   _______, _______, _______
    )
};

// Custom initialization with LED startup effect
void keyboard_post_init_user(void) {
    // Flash all LEDs white briefly on startup
    rgblight_setrgb_at(255, 255, 255, 0);
    rgblight_setrgb_at(255, 255, 255, 1);
    rgblight_setrgb_at(255, 255, 255, 2);
    wait_ms(300);
    
    // Turn all off
    rgblight_setrgb_at(0, 0, 0, 0);
    rgblight_setrgb_at(0, 0, 0, 1);
    rgblight_setrgb_at(0, 0, 0, 2);
}

// Layer indicator using bottom LED (index 2)
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 0:  // Base layer - LED off
            rgblight_setrgb_at(0, 0, 0, 2);
            break;
        case 1:  // Function layer - Red LED
            rgblight_setrgb_at(255, 0, 0, 2);
            break;
        default:  // Any other layer - Purple LED
            rgblight_setrgb_at(128, 0, 255, 2);
            break;
    }
    return state;
}

// Keep Caps Lock indicator on top LED (index 0) with custom color
// Keep Num Lock indicator on middle LED (index 1) with custom color
bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        rgblight_setrgb_at(255, 0, 255, 0); // Top LED: Magenta for Caps Lock
    } else {
        rgblight_setrgb_at(0, 0, 0, 0);
    }
    
    if (led_state.num_lock) {
        rgblight_setrgb_at(255, 255, 0, 1); // Middle LED: Yellow for Num Lock
    } else {
        rgblight_setrgb_at(0, 0, 0, 1);
    }
    
    // Note: Scroll Lock is not used since bottom LED is used for layer indication
    
    return false; // Return false to prevent default LED behavior
}
