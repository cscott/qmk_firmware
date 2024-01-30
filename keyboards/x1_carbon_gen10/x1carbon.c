#include "x1carbon.h"
#include "quantum.h"

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutputPushPull(LED_CAPSLOCK);
  setPinOutputPushPull(LED_MICMUTE);
  setPinOutputPushPull(LED_FNLOCK);
  setPinOutputPushPull(LED_MUTE);
  writePinHigh(LED_CAPSLOCK);
  writePinHigh(LED_MICMUTE);
  writePinHigh(LED_FNLOCK);
  writePinHigh(LED_MUTE);

  setPinInputHigh(SLEEP_GPIO);
  setPinInputHigh(KBD_BL_DET);
  setPinOutputPushPull(KBD_BL_PWM);
  writePinLow(KBD_BL_PWM);
}


void keyboard_post_init_user(void) {
  debug_enable = true;
  //debug_matrix = true;
  debug_keyboard = true;
  //debug_mouse = true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  static uint8_t bl_on = 0;

  process_record_user(keycode, record);


  switch (keycode) {
        // Implement step brightness for backlight
        case BL_STEP:
            if (record->event.pressed) {
              // XX step through brightness levels
              bl_on = !bl_on;
              writePin(KBD_BL_PWM, bl_on);
            }
            return true;

        case KC_SCRN:
            // Simulate press WIN+P
            // Works (at least) on Windows and GNOME
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_P);
            } else {
                unregister_code(KC_P);
                unregister_code(KC_LGUI);
            }
            return false; // Skip all further processing of this key
        default:
            return true; // Process all other keycodes normally
    }
}
