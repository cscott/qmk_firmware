// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "x1carbon.h"

// clang-format off
enum _layers {
  _BASE,
  _FN,
  _FN_LOCK,
  _FM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐
     * │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │Hom│End│Ins│Del│
     * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift │
     * ├────┬───┴┬──┴─┬─┴─┬─┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┼───┬───┐
     * │Fn  │Ctrl│GUI │Alt│                    │ Alt│PrtS│Ctrl│PgUp│ ↑ │PgD│
     * └────┴────┴────┴───┴────────────────────┴────┴────┴────┴┬───┼───┼───┤
     *                                                         │ ← │ ↓ │ → │
     *                                                         └───┴───┴───┘
     */
    [_BASE] = LAYOUT(
       KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_HOME, KC_END, KC_INS, KC_DEL,
       KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQL, KC_BSPC,
       KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
       KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOTE, KC_ENTER,
       KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
       MO(_FN), KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, KC_PSCR, KC_RCTL, KC_PGUP, KC_UP, KC_PGDN,
       KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    /* Function Layer */
    [_FN] = LAYOUT(
       FN_LOCK, KC_MUTE, KC_VOLD, KC_VOLU, MICROPHONE_MUTE, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_SCRN, KC_F8, KC_F9, KC_F10, KC_F11, QK_BOOT, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, BL_STEP, _______, _______, _______, _______, _______, _______,
       _______, _______, _______
    ),
    /* Function Lock Layer: everything on F-row locked to function layer, except ESC */
    [_FN_LOCK] = LAYOUT(
       _______, KC_MUTE, KC_VOLD, KC_VOLU, MICROPHONE_MUTE, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_SCRN, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       MO(_FM), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______
    ),
    [_FM] = LAYOUT(
       FN_LOCK, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, QK_BOOT, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, BL_STEP, _______, _______, _______, _______, _______, _______,
       _______, _______, _______
    )
};
// clang-format on

// Make sure to keep FN Lock even after reset
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case FN_LOCK:
            if (record->event.pressed) {
                if (layer_state_is(_FN)) {
                    set_single_persistent_default_layer(_FN_LOCK);
                }
                if (layer_state_is(_FM)) {
                    set_single_persistent_default_layer(_BASE);
                }
            }
            return false;
            break;
        default:
            break;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  writePin(LED_FNLOCK, layer_state_cmp(state|default_layer_state, _FN_LOCK) ? 0 : 1);
  return state;
}
