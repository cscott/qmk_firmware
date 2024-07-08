VPATH += drivers/gpio
SRC += x1carbon.c mcp23018.c matrix.c
CUSTOM_MATRIX = lite
SPI_DRIVER_REQUIRED = yes
BACKLIGHT_DRIVER = software
