#pragma once

#include "quantum.h"

enum x1carbon_keycodes {
    // Custom keycode to change screen modes (e.g. enable external screen)
    KC_SCRN = SAFE_RANGE,
    FN_LOCK,
    MICROPHONE_MUTE, // apparently not a standard keycode?
};

#define SLEEP_GPIO GP4
#define KBD_BL_PWM GP11
#define KBD_BL_DET GP24 // XXX should be GP25
#define LED_CAPSLOCK GP8
#define LED_MICMUTE GP9
#define LED_FNLOCK GP10
#define LED_MUTE GP15
#define HOTKEY_GPIO GP14

#define IOEXP_RESET GP2 // XXX should be GP24
#define IOEXP_INT GP3
