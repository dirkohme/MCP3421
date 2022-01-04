/**
 @file MCP3421.h
 @brief This is a library for MCP3421 analog digital converter
 @author Dirk Ohme <dirk_ohme@hotmail.com>
*/

#ifndef MCP3421_H
#define MCP3421_H

#include <Arduino.h>
#include <Wire.h>

#define MCP3421_SLAVE_ADDRESS 0x69 ///< Default I2C Slave Address

/// @name Config Parameter
/// @{
#define MCP3421_CONFIG_RDY_ON 0b10000000
#define MCP3421_CONFIG_RDY_OFF 0b00000000
#define MCP3421_CONFIG_CONV_CONTINUOUS 0b00010000
#define MCP3421_CONFIG_CONV_ONE_SHOT 0b00000000
#define MCP3421_CONFIG_RATE_240SPS 0b0000
#define MCP3421_CONFIG_RATE_60SPS 0b0100
#define MCP3421_CONFIG_RATE_15SPS 0b1000
#define MCP3421_CONFIG_RATE_3_75SPS 0b1100
#define MCP3421_CONFIG_GAIN_X1 0b00
#define MCP3421_CONFIG_GAIN_X2 0b01
#define MCP3421_CONFIG_GAIN_X4 0b10
#define MCP3421_CONFIG_GAIN_X8 0b11
/// @}


/**
 @class CMCP3421
 @brief MCP3421 basic functions
*/
class CMCP3421 {
  public:
		CMCP3421(uint8_t addr = MCP3421_SLAVE_ADDRESS);
	void	init(void);
	int32_t	readADC();
  private:
	uint8_t	_i2caddr;
	void	writeI2c(uint8_t value);
	void	readI2c(uint8_t num, uint8_t *buffer);
};

#endif // MCP3421_H
