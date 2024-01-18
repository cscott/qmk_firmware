/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2019 Hiroyuki Okada
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

// If board has a debug LED, you can enable it by defining this
#ifdef HACKERBOARD
# define DEBUG_LED_PIN C7
#else
// #define DEBUG_LED_PIN F7
#endif

#define ADNS5050_SCLK_PIN         B7
#define ADNS5050_SDIO_PIN         C6
#ifdef HACKERBOARD
# define ADNS5050_CS_PIN          F7
# define ADNS5050_OE_PIN          F5
# define ADNS5050_RST_PIN         F6
#else
# define ADNS5050_CS_PIN          B4
#endif

#define POINTING_DEVICE_ROTATION_270

#ifdef HACKERBOARD
#define BLUEFRUIT_LE_RST_PIN       D4
#define BLUEFRUIT_LE_CS_PIN        B4
#define BLUEFRUIT_LE_IRQ_PIN       E6
#define BLUEFRUIT_LE_SCK_DIVISOR   2 // 8MHz CPU
//#define BLUEFRUIT_LE_SCK_DIVISOR 4 // 16MHz CPU
#define BATTERY_LEVEL_PIN          B5
#define SCROLLWHEEL_LED_PIN        F1
#endif

//            ------ PINOUT GUIDE ------
//  Ploopy        Hackerboard
// Arduino Port   Arduino Port   Function
//    -      B0                                            GND
//   SCK     B1                  SCLK
//   MOSI    B2                  MOSI
//   MISO    B3                  MISO
//    8      B4     A0    F7     ADNS_/CS                        *
//    9      B5                  (battery level)           GND*
//   10      B6     10    B6     ButtonBack
//   11      B7     11    B7     ADNS_SCLK
//    5      C6      5    C6     ADNS_SDIO
//   13      C7                  (debug LED)               GND*
//    3      D0      3    D0     SCL (i2c, but no pullup)  GND
//    2      D1      2    D1     SDA (i2c, but no pullup)  GND
//    0      D2      0    D2     RX ButtonScrollWheel
//    1      D3                  TX  (used by hackerboard) GND*
//    4      D4     12    D6     SWDIO/RST ButtonLeftClick       *
//    -      D5                                            GND
//   12      D6                  (used by hackerboard)     GND*
//    6      D7      6    D7     ButtonForward
//    -      E2                  (hardware bootloader, pulled high)
//    7      E6      1    D3     ButtonRightClick                *
//   A5      F0     A5    F0     ScrollWheelOpto0
//   A4      F1                  (used by hackerboard)     GND*
//   A3      F4     A3    F4     ScrollWheelOpto1
//   A2      F5                  (used by hackerboard)     GND*
//   A1      F6                  (used by hackerboard)     GND*
//   A0      F7                  (used by hackerboard)     GND*
//                  A4    F1     ScrollWheelLED                  *
//                  A1    F6     ADNS_RESET                      *
//                  A2    F5     ADNS_OE                         *
//                   4    D4     BLE_RST                         *
//                   8    B4     BLE_CS                          *
//                   7    E6     BLE_IRQ                         *
//                   9    B5     BATTERY_LEVEL
//                  13    C7     DEBUG_LED                       *
