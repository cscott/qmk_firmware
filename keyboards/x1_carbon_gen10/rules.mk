VPATH += drivers/gpio
SRC += mcp23018.c matrix.c
CUSTOM_MATRIX = lite
I2C_DRIVER_REQUIRED = yes

# For debugging!
CONSOLE_ENABLE = yes
