// Copyright 2022 zvecr<git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "mcp23018.h"
#ifdef MCP23S18
# include "spi_master.h"
#else
# include "i2c_master.h"
#endif
#include "wait.h"
#include "debug.h"

#define SLAVE_TO_ADDR(n) (n << 1)
#define I2C_TIMEOUT 100
#define MCP_SPI_MODE 0 /* SPI Mode 0,0 */
#define MCP_DIVISOR 13 /* min 13 = 9.61 MHz */

enum {
    CMD_IODIRA = 0x00, // i/o direction register
    CMD_IODIRB = 0x01,
    CMD_GPPUA  = 0x0C, // GPIO pull-up resistor register
    CMD_GPPUB  = 0x0D,
    CMD_GPIOA  = 0x12, // general purpose i/o port register (write modifies OLAT)
    CMD_GPIOB  = 0x13,
};

void mcp23018_init(DECLARE_MCP_ADDR) {
    static uint8_t s_init = 0;
    if (!s_init) {
#ifdef MCP23S18
        spi_init();
#else
        i2c_init();
#endif
        wait_ms(100);

        s_init = 1;
    }
}

#ifdef MCP23S18

/* SPI interface */
typedef spi_status_t mcp_status_t;
#define MCP_STATUS_SUCCESS SPI_STATUS_SUCCESS
#define MCP_STATUS_ERROR SPI_STATUS_ERROR

static mcp_status_t writeReg8(pin_t cs_pin, uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint16_t len) {
  uint8_t preamble[3] = { SLAVE_TO_ADDR(slave_addr) & 0xFE, reg_addr };
  if (!spi_start(cs_pin, false /* !lsb first */, MCP_SPI_MODE, MCP_DIVISOR)) {
    return MCP_STATUS_ERROR;
  }
  mcp_status_t st;
  if (len==1) {
    preamble[2] = data[0];
    st = spi_transmit(preamble, 3);
  } else {
    st = spi_transmit(preamble, 2);
    if (st == MCP_STATUS_SUCCESS) {
      st = spi_transmit(data, len);
    }
  }
  spi_stop();
  return st;
}

static mcp_status_t readReg8(pin_t cs_pin, uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint16_t len) {
  uint8_t preamble[2] = { SLAVE_TO_ADDR(slave_addr) | 0x01, reg_addr };
  spi_start(cs_pin, false /* !lsb first */, MCP_SPI_MODE, MCP_DIVISOR);
  mcp_status_t st = spi_transmit(preamble, sizeof(preamble));
  if (st == MCP_STATUS_SUCCESS) {
    st = spi_receive(data, len);
  }
  spi_stop();
  return st;
}

#else

/* I2C interface */
typedef i2c_status_t mcp_status_t;
#define MCP_STATUS_SUCCESS I2C_STATUS_SUCCESS

static mcp_status_t writeReg8(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint16_t len) {
    uint8_t addr         = SLAVE_TO_ADDR(slave_addr);
    return i2c_writeReg(addr, reg_addr, data, len, I2C_TIMEOUT);
}

static mcp_status_t readReg8(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint16_t len) {
    uint8_t addr         = SLAVE_TO_ADDR(slave_addr);
    return i2c_readReg(addr, reg_addr, data, len, I2C_TIMEOUT);
}

#endif

bool mcp23018_set_config(DECLARE_MCP_ADDR, mcp23018_port_t port, uint8_t conf) {
    uint8_t cmdDirection = port ? CMD_IODIRB : CMD_IODIRA;
    uint8_t cmdPullup    = port ? CMD_GPPUB : CMD_GPPUA;

    mcp_status_t ret = writeReg8(mcp_addr, cmdDirection, &conf, sizeof(conf));
    if (ret != MCP_STATUS_SUCCESS) {
        dprintf("mcp23018_set_config::directionFAILED::%u\n", ret);
        return false;
    }

    ret = writeReg8(mcp_addr, cmdPullup, &conf, sizeof(conf));
    if (ret != MCP_STATUS_SUCCESS) {
        dprintf("mcp23018_set_config::pullupFAILED::%u\n", ret);
        return false;
    }

    return true;
}

bool mcp23018_set_dir(DECLARE_MCP_ADDR, mcp23018_port_t port, uint8_t conf) {
    uint8_t cmd  = port ? CMD_IODIRB : CMD_IODIRA;

    mcp_status_t ret = writeReg8(mcp_addr, cmd, &conf, sizeof(conf));
    if (ret != MCP_STATUS_SUCCESS) {
        dprintf("mcp23018_set_dir::FAILED::%u\n", ret);
        return false;
    }

    return true;
}

bool mcp23018_set_output(DECLARE_MCP_ADDR, mcp23018_port_t port, uint8_t conf) {
    uint8_t cmd  = port ? CMD_GPIOB : CMD_GPIOA;

    mcp_status_t ret = writeReg8(mcp_addr, cmd, &conf, sizeof(conf));
    if (ret != MCP_STATUS_SUCCESS) {
        dprintf("mcp23018_set_output::FAILED::%u\n", ret);
        return false;
    }

    return true;
}

bool mcp23018_set_output_all(DECLARE_MCP_ADDR, uint8_t confA, uint8_t confB) {
    uint8_t conf[2] = {confA, confB};

    mcp_status_t ret = writeReg8(mcp_addr, CMD_GPIOA, &conf[0], sizeof(conf));
    if (ret != MCP_STATUS_SUCCESS) {
        dprintf("mcp23018_set_output_all::FAILED::%u\n", ret);
        return false;
    }

    return true;
}

bool mcp23018_readPins(DECLARE_MCP_ADDR, mcp23018_port_t port, uint8_t* out) {
     uint8_t cmd  = port ? CMD_GPIOB : CMD_GPIOA;

    mcp_status_t ret = readReg8(mcp_addr, cmd, out, sizeof(uint8_t));
    if (ret != MCP_STATUS_SUCCESS) {
        dprintf("mcp23018_readPins::FAILED::%u\n", ret);
        return false;
    }

    return true;
}

bool mcp23018_readPins_all(DECLARE_MCP_ADDR, uint16_t* out) {

    typedef union {
        uint8_t  u8[2];
        uint16_t u16;
    } data16;

    data16 data = {.u16 = 0};

    mcp_status_t ret = readReg8(mcp_addr, CMD_GPIOA, &data.u8[0], sizeof(data));
    if (ret != MCP_STATUS_SUCCESS) {
        dprintf("mcp23018_readPins::FAILED::%u\n", ret);
        return false;
    }

    *out = data.u16;
    return true;
}
