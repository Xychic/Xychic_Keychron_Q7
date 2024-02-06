/* 
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

#include "upside_down.h"
#include "os_detection.h"

#define shift(a, b) ((mods | oneshot_mods) & MOD_MASK_SHIFT) ? b : a
#define handle_key(key, result) case key:{send_unicode_string(result);del_oneshot_mods(MOD_MASK_SHIFT);unregister_mods(MOD_MASK_SHIFT); tap_code(KC_LEFT);register_mods(mods);return false;}


bool process_upside_down(uint16_t keycode, keyrecord_t* record) {
    switch (detected_host_os()) {
        case OS_LINUX:
            set_unicode_input_mode(UNICODE_MODE_LINUX);
            break;
        case OS_WINDOWS:
            set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
            break;
        case OS_MACOS:
            set_unicode_input_mode(UNICODE_MODE_MACOS);
            break;
        case OS_IOS:
        case OS_UNSURE:
            break;
    }

    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();
    if (record->event.pressed) {
        switch (keycode) {
            handle_key(KC_A, shift("ɐ", "∀"))
            handle_key(KC_B, shift("q", "B"))
            handle_key(KC_C, shift("ɔ", "Ɔ"))
            handle_key(KC_D, shift("p", "D"))
            handle_key(KC_E, shift("ǝ", "Ǝ"))
            handle_key(KC_F, shift("ɟ", "Ⅎ"))
            handle_key(KC_G, shift("ƃ", "פ"))
            handle_key(KC_H, shift("ɥ", "H"))
            handle_key(KC_I, shift("ᴉ", "I"))
            handle_key(KC_J, shift("ɾ", "ſ"))
            handle_key(KC_K, shift("ʞ", "K"))
            handle_key(KC_L, shift("l", "˥"))
            handle_key(KC_M, shift("ɯ", "W"))
            handle_key(KC_N, shift("u", "N"))
            handle_key(KC_O, shift("o", "O"))
            handle_key(KC_P, shift("d", "Ԁ"))
            handle_key(KC_Q, shift("b", "Q"))
            handle_key(KC_R, shift("ɹ", "R"))
            handle_key(KC_S, shift("s", "S"))
            handle_key(KC_T, shift("ʇ", "┴"))
            handle_key(KC_U, shift("n", "∩"))
            handle_key(KC_V, shift("ʌ", "Λ"))
            handle_key(KC_W, shift("ʍ", "M"))
            handle_key(KC_X, shift("x", "X"))
            handle_key(KC_Y, shift("ʎ", "⅄"))
            handle_key(KC_Z, shift("z", "Z"))
            handle_key(KC_1, shift("Ɩ", "¡"))
            handle_key(KC_2, shift("ᄅ", ",,"))
            handle_key(KC_3, shift("Ɛ", "£"))
            handle_key(KC_4, shift("ㄣ", "$"))
            handle_key(KC_5, shift("ϛ", "%"))
            handle_key(KC_6, shift("9", "v"))
            handle_key(KC_7, shift("ㄥ", "⅋"))
            handle_key(KC_8, shift("8", "*"))
            handle_key(KC_9, shift("6", ")"))
            handle_key(KC_0, shift("0", "("))
            case KC_BSPC: {
                tap_code(KC_DEL);
                return false;
            }
            case KC_DEL: {
                tap_code(KC_BSPC);
                return false;
            }
            case KC_NUBS:
            case KC_SPC:
            case KC_MINS:
            case KC_EQL:
            case KC_LBRC:
            case KC_RBRC:
            case KC_QUOT:
            case KC_NUHS:
            case KC_COMM:
            case KC_DOT:
            case KC_ENT:
            case KC_SLSH: {
                tap_code(keycode);
                tap_code(KC_LEFT);
                return false;
            }
        }
    }
    return true;
}