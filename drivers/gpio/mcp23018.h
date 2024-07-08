// Copyright 2022 zvecr<git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * Port ID
 */
typedef enum {
    mcp23018_PORTA,
    mcp23018_PORTB,
} mcp23018_port_t;

/**
 * Helpers for set_config
 */
enum {
    ALL_OUTPUT = 0,
    ALL_INPUT  = 0xFF,
};

/**
 * Helpers for set_output
 */
enum {
    ALL_LOW  = 0,
    ALL_HIGH = 0xFF,
};

#ifdef MCP23S18
# define DECLARE_MCP_ADDR uint8_t cs_pin, uint8_t addr
# define mcp_addr cs_pin, addr
#else
# define DECLARE_MCP_ADDR uint8_t addr
# define mcp_addr addr
#endif

/**
 * Init expander and any other dependent drivers
 */
void mcp23018_init(DECLARE_MCP_ADDR);

/**
 * Configure input/output to a given port
 */
bool mcp23018_set_config(DECLARE_MCP_ADDR, mcp23018_port_t port, uint8_t conf);

/**
 * Write IO direction to a given port
 */
bool mcp23018_set_dir(DECLARE_MCP_ADDR, mcp23018_port_t port, uint8_t conf);

/**
 * Write high/low to a given port
 */
bool mcp23018_set_output(DECLARE_MCP_ADDR, mcp23018_port_t port, uint8_t conf);

/**
 * Write high/low to both ports sequentially
 *
 *  - slightly faster than multiple set_output
 */
bool mcp23018_set_output_all(DECLARE_MCP_ADDR, uint8_t confA, uint8_t confB);

/**
 * Read state of a given port
 */
bool mcp23018_readPins(DECLARE_MCP_ADDR, mcp23018_port_t port, uint8_t* ret);

/**
 * Read state of both ports sequentially
 *
 *  - slightly faster than multiple readPins
 */
bool mcp23018_readPins_all(DECLARE_MCP_ADDR, uint16_t* ret);
