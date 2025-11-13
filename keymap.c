/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
#include "features/upside_down.h"
#include "features/git_shorthand.h"

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 10
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 20
#undef MOUSEKEY_MOVE_DELTA
#define MOUSEKEY_MOVE_DELTA 8
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 10
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 120
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 10
#undef MOUSEKEY_WHEEL_INTERVAL
#define MOUSEKEY_WHEEL_INTERVAL 80
#undef MOUSEKEY_WHEEL_DELTA
#define MOUSEKEY_WHEEL_DELTA 1
#undef MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

// clang-format off

enum layers{
    _L0,
    _L1,
    _L2,
    _L3,
    _L4
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

enum custom_keycodes {
    M1 = SAFE_RANGE,
    UD_TEXT,
    GIT_SH,
    RGB_MOD,
    RGB_TOG,
    RGB_VAI,
    RGB_VAD,
    RGB_SPI,
    RGB_SPD,
    RGB_HUI,
    RGB_HUD,
    RGB_SAI,
    RGB_SAD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L0] = LAYOUT_iso_73(
        KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,    KC_NO,             KC_NO,   QK_BOOT,
        KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,                       KC_NO,   KC_NO,
        KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,    KC_NO,             KC_NO,   KC_NO,
        KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,             KC_NO,             KC_NO,   KC_NO,
        KC_NO,   KC_NO,    KC_NO,                               KC_NO,                              KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO),

    [_L1] = LAYOUT_iso_73(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,   KC_BSPC,           KC_INS,  KC_NO,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC,                     KC_END,  KC_DEL,
        KC_CAPS, KC_A,     KC_S,     KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, KC_NUHS,  KC_ENT,            KC_HOME, KC_PGUP,
        KC_LSFT, KC_NUBS,  KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,           KC_RSFT,           KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI,  KC_LALT,                             KC_SPC,                             KC_RALT,  KC_RCTL, MO(_L2),  MO(_L3),  KC_LEFT, KC_DOWN, KC_RGHT),

    [_L2] = LAYOUT_iso_73(
        KC_GRV,  KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,   _______,           _______, TG(_L2),
        _______, KC_MPRV,  KC_MPLY,  KC_MNXT, _______, _______, _______, _______, _______, _______, KC_PSCR,  _______, _______,                     _______, _______,
        CW_TOGG, KC_VOLD,  KC_MUTE,  KC_VOLU, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______,           _______, _______,
        _______, _______,  _______,  _______, _______, _______, _______, KC_NUM,  _______, _______, _______,  _______,           _______,           _______, _______,
        _______, _______,  _______,                             KC_P2,                              _______,  _______, _______,  MO(_L4),  _______, _______, _______),

    [_L3] = LAYOUT_iso_73(
        KC_GRV,  KC_F13,   KC_F14,   KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,   KC_F23,  KC_F24,   _______,           _______, TG(_L3),
        RGB_MOD, RGB_VAI,  RGB_SPI,  RGB_HUI, RGB_SAI, _______, _______, _______, _______, _______, _______,  _______, _______,                     _______, _______,
        RGB_TOG, RGB_VAD,  RGB_SPD,  RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,  _______, _______,  _______,           _______, _______,
        _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______,  _______,           _______,           _______, _______,
        _______, _______,  _______,                             KC_P3,                              _______,  _______, MO(_L4),  _______,  _______, _______, _______),

    [_L4] = LAYOUT_iso_73(
        KC_GRV,  M1,       _______,  _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______,           _______, TG(_L4),
        _______, MS_BTN1,  MS_UP,    MS_BTN2, _______, _______, _______, _______, _______, _______, _______,  _______, _______,                     _______, _______,
        _______, MS_LEFT,  MS_DOWN,  MS_RGHT, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______,           _______, _______,
        UD_TEXT, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______,  _______,           _______,           MS_WHLU, _______,
        _______, AC_TOGG,  GIT_SH,                              KC_P4,                              _______,  _______, _______,  _______,  MS_WHLL, MS_WHLD, MS_WHLR),
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    static bool upside_down_text = false;
    static bool git_shorthand = false;

    if (upside_down_text && !process_upside_down(keycode, record)) { return false; }
    if (git_shorthand && !process_git_shorthand(keycode, record)) { return false; }

    switch (keycode) {
        case M1: {
            if (record->event.pressed) {
                switch (detected_host_os()) {
                    case OS_LINUX:
                        SEND_STRING("LINUX");
                        return false;
                    case OS_WINDOWS:
                        SEND_STRING("WINDOWS");
                        return false;
                    case OS_MACOS:
                        SEND_STRING("MACOS");
                        return false;
                    case OS_IOS:
                        SEND_STRING("IOS");
                        return false;
                    case OS_UNSURE:
                        SEND_STRING("UNSURE");
                        return false;
                }
            }
        }
        case UD_TEXT: {
            if (record->event.pressed) {
                upside_down_text = !upside_down_text;
            }
            return false;
        }
        case GIT_SH: {
            if (record->event.pressed) {
                git_shorthand = !git_shorthand;
            }
            return false;
        }
        case RGB_MOD: {
            if (record->event.pressed) {
                rgblight_step();
            }
            return false;
        }
        case RGB_TOG: {
            if (record->event.pressed) {
                rgblight_toggle();
            }
            return false;
        }
                case RGB_VAI: {
            if (record->event.pressed) {
                rgblight_increase_val();
            }
            return false;
        }
        case RGB_VAD: {
            if (record->event.pressed) {
                rgblight_decrease_val();
            }
            return false;
        }
        case RGB_SPI: {
            if (record->event.pressed) {
                rgblight_increase_speed();
            }
            return false;
        }
        case RGB_SPD: {
            if (record->event.pressed) {
                rgblight_decrease_speed();
            }
            return false;
        }
        case RGB_HUI: {
            if (record->event.pressed) {
                rgblight_increase_hue();
            }
            return false;
        }
        case RGB_HUD: {
            if (record->event.pressed) {
                rgblight_decrease_hue();
            }
            return false;
        }
        case RGB_SAI: {
            if (record->event.pressed) {
                rgblight_increase_sat();
            }
            return false;
        }
        case RGB_SAD: {
            if (record->event.pressed) {
                rgblight_decrease_sat();
            }
            return false;
        }
    }
    return true;
}
