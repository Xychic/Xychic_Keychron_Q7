#include "autoclicker.h"
#include "custom_keycode.h"

#define MAX_CLICK_PERIOD 10 * 60 * 1000 // 10 mins
#define MIN_CLICK_PERIOD 50 // 50ms / 20 clicks per second
#define CLICK_DELTA 10 // 100ms / 10 clicks per second

static deferred_token click_token = INVALID_DEFERRED_TOKEN;
static uint8_t click_enabled = 0;
static bool left_click_registered = false;
static bool right_click_registered = false;
static uint32_t auto_click_period = 200; // 200ms / 5 clicks per second


static uint32_t autoclick_callback(uint32_t trigger_time, void* cb_arg) {
    if (left_click_registered) {
        unregister_code16(MS_BTN1);
        left_click_registered = false;
    } else if (click_enabled & 1) {
        left_click_registered = true;
        register_code16(MS_BTN1);
    }
    if (right_click_registered) {
        unregister_code16(MS_BTN2);
        right_click_registered = false;
    } else if (click_enabled & 2) {
        right_click_registered = true;
        register_code16(MS_BTN2);
    }
    return auto_click_period / 2;
}

// Starts Turbo Click, begins the `autoclick_callback()` callback.
static void autoclick_start(void) {
    if (click_token == INVALID_DEFERRED_TOKEN) {
        uint32_t next_delay_ms = autoclick_callback(0, NULL);
        click_token = defer_exec(next_delay_ms, autoclick_callback, NULL);
    }
}

static void autoclick_stop(void) {
    if (click_token != INVALID_DEFERRED_TOKEN) {
        cancel_deferred_exec(click_token);
        click_token = INVALID_DEFERRED_TOKEN;
        if (left_click_registered) {
            unregister_code16(MS_BTN1);
            left_click_registered = false;
        }
        if (right_click_registered) {
            unregister_code16(MS_BTN2);
            right_click_registered = false;
        }
        click_enabled = 0;
    }
}


bool process_autoclicker(uint16_t keycode, keyrecord_t* record) {
    static bool autoclicker_enabled = false;

    if (record->event.pressed) {
        switch (keycode) {
            case AUT_CLK: {
                if (autoclicker_enabled) {
                    autoclick_stop();
                    autoclicker_enabled = false;
                } else {
                    autoclicker_enabled = true;
                }
                return false;
            }
            case ACL_INC: {
                auto_click_period -= CLICK_DELTA;
                if (auto_click_period < MIN_CLICK_PERIOD) {
                    auto_click_period = MIN_CLICK_PERIOD;
                }
                return false;
            }
            case ACL_DEC: {
                auto_click_period += CLICK_DELTA;
                if (auto_click_period > MAX_CLICK_PERIOD) {
                    auto_click_period = MAX_CLICK_PERIOD;
                }
                return false;
            }
        }
    }

    if (!autoclicker_enabled) {
        return true;
    }

    switch (keycode) {
        case MS_BTN1: {
            if (record->event.pressed) {
                click_enabled |= 1;
                if (click_token == INVALID_DEFERRED_TOKEN) {
                    autoclick_start();
                }
            } else {
                click_enabled &= ~1;
                if (click_enabled && click_token != INVALID_DEFERRED_TOKEN) {
                    autoclick_stop();
                }
            }
            return false;
        }
        case MS_BTN2: {
            if (record->event.pressed) {
                click_enabled |= 2;
                if (click_token == INVALID_DEFERRED_TOKEN) {
                    autoclick_start();
                }
            } else {
                click_enabled &= ~2;
                if (click_enabled && click_token != INVALID_DEFERRED_TOKEN) {
                    autoclick_stop();
                }
            }
            return false;
        }
    }

    return true;
}