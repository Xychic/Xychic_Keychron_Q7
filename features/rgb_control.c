#include "rgb_control.h"
#include "custom_keycode.h"

bool process_rgb(uint16_t keycode, keyrecord_t* record) {
    static bool write_rgb_to_eeprom = false;

    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case RGB_MOD: {
            if (write_rgb_to_eeprom) {
                rgblight_step();
            } else {
                rgblight_step_noeeprom();
            }
            return false;
        }
        case RGB_TOG: {
            if (write_rgb_to_eeprom) {
                rgblight_toggle();
            } else {
                rgblight_toggle_noeeprom();
            }
            return false;
        }
        case RGB_VAI: {
            if (write_rgb_to_eeprom) {
                rgblight_increase_val();
            } else {
                rgblight_increase_val_noeeprom();
            }
            return false;
        }
        case RGB_VAD: {
            if (write_rgb_to_eeprom) {
                rgblight_decrease_val();
            } else {
                rgblight_decrease_val_noeeprom();
            }
            return false;
        }
        case RGB_SPI: {
            if (write_rgb_to_eeprom) {
                rgblight_increase_speed();
            } else {
                rgblight_increase_speed_noeeprom();
            }
            return false;
        }
        case RGB_SPD: {
            if (write_rgb_to_eeprom) {
                rgblight_decrease_speed();
            } else {
                rgblight_decrease_speed_noeeprom();
            }
            return false;
        }
        case RGB_HUI: {
            if (write_rgb_to_eeprom) {
                rgblight_increase_hue();
            } else {
                rgblight_increase_hue_noeeprom();
            }
            return false;
        }
        case RGB_HUD: {
            if (write_rgb_to_eeprom) {
                rgblight_decrease_hue();
            } else {
                rgblight_decrease_hue_noeeprom();
            }
            return false;
        }
        case RGB_SAI: {
            if (write_rgb_to_eeprom) {
                rgblight_increase_sat();
            } else {
                rgblight_increase_sat_noeeprom();
            }
            return false;
        }
        case RGB_SAD: {
            if (write_rgb_to_eeprom) {
                rgblight_decrease_sat();
            } else {
                rgblight_decrease_sat_noeeprom();
            }
            return false;
        }
        case RGB_SAV: {
            write_rgb_to_eeprom = !write_rgb_to_eeprom;
            return false;
        }
    }

    return true;
}