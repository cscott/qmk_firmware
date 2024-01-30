#include "x1carbon.h"
#include "matrix.h"
#include "mcp23018.h"
#include "debug.h"

#define I2C_ADDR 0x20

static pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static void init_pins(void) {
  for (uint8_t i = 0; i < MATRIX_COLS; i++) {
    setPinInputHigh(col_pins[i]);
  }
  setPinInputHigh(HOTKEY_GPIO);
}

static void init_pins_MCP23018(void) {
  mcp23018_set_config(I2C_ADDR, mcp23018_PORTA, ALL_INPUT);
  mcp23018_set_config(I2C_ADDR, mcp23018_PORTB, ALL_INPUT);
  mcp23018_set_output_all(I2C_ADDR, 0x00, 0x00);
}

void matrix_init_custom(void) {
  setPinInputHigh(IOEXP_INT);
  setPinOutputPushPull(IOEXP_RESET);
  writePinLow(IOEXP_RESET);
  wait_ms(100);
  writePinHigh(IOEXP_RESET);
  mcp23018_init(I2C_ADDR);

  init_pins();
  init_pins_MCP23018();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
  bool matrix_has_changed = false;

  for (uint8_t row = 0; row < 16; row++) {
    matrix_row_t last_row_value = current_matrix[row];
    matrix_row_t new_row_value = 0;
    mcp23018_set_dir(I2C_ADDR, row < 8 ? mcp23018_PORTA : mcp23018_PORTB, ~(1 << (row&7)));
    // XXX: We could do this in a single cycle read, rather than this inefficient for-loop
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
      if (!readPin(col_pins[col])) {
        new_row_value |= MATRIX_ROW_SHIFTER << col;
      }
    }
    if (new_row_value != last_row_value) {
      matrix_has_changed = true;
      current_matrix[row] = new_row_value;
    }
    if (row == 7 || row == 15) {
      mcp23018_set_dir(I2C_ADDR, row < 8 ? mcp23018_PORTA : mcp23018_PORTB, ALL_INPUT);
    }
  }

  uint8_t old_hotkey = current_matrix[16];
  uint8_t new_hotkey = readPin(HOTKEY_GPIO) ? 0 : MATRIX_ROW_SHIFTER;
  if (old_hotkey != new_hotkey) {
    matrix_has_changed = true;
    current_matrix[16] = new_hotkey;
  }

  return matrix_has_changed;
}

void keyboard_post_init_user(void) {
  debug_enable = true;
  //debug_matrix = true;
  //debug_keyboard = true;
  //debug_mouse = true;
}
