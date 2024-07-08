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
#define KBD_BL_DET GP25
#define LED_CAPSLOCK GP8
#define LED_MICMUTE GP9
#define LED_FNLOCK GP10
#define LED_MUTE GP15
#define HOTKEY_GPIO GP14

#define IOEXP_RESET GP24
#define IOEXP_MISO GP0
#define IOEXP_CS GP1
#define IOEXP_SCK GP2
#define IOEXP_MOSI GP3
#undef IOEXP_INT /* n/c */

#define TP4_FW_WR_EN GP5
#define TP4CLK GP7
#define TP4DATA GP6
#define TP4ACT GP12
#define TP4RESET GP13
