// Copyright 2024 C. Scott Ananian (@cscott)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SPI_DRIVER SPID0
#define SPI_MISO_PIN GP0
#define SPI_CS_PIN GP1
#define SPI_SCK_PIN GP2
#define SPI_MOSI_PIN GP3

#define MCP23S18 1
#define LED_CAPS_LOCK_PIN GP8
#define LED_PIN_ON_STATE 0

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
