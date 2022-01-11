/**
 @file MCP3421.cpp
 @brief This is a library for MCP3421 analog digital converter
 @author Dirk Ohme <dirk_ohme@hotmail.com>
*/

#include "Wire.h"
#include "MCP3421.h"

/**
 @brief Constructor
*/
CMCP3421::CMCP3421(const float   fFactor /*= 1.0*/,
                   const uint8_t u8Addr  /*= DefaultAddress*/)
{
	fFactor_m = fFactor;
	u8Addr_m  = u8Addr;
	Wire.begin();
}

/**
 @brief Initialize device
 @param [in] config Configure Parameter
*/
void CMCP3421::Init(const bool        boRepeat /*= false*/,
                    const ESampleRate eSR      /*= eSR_18Bit*/,
		    const EGain       eGain    /*= eGain_x1*/,
		          TwoWire*    coI2C    /*= &Wire*/)
{
	coI2C_m          = coI2C;
	suCfg_m.reg      = 0x00;
	suCfg_m.bit.GAIN = ((uint8_t)eGain & 0x03);
	suCfg_m.bit.SR   = ((uint8_t)eSR   & 0x03);
	suCfg_m.bit.OC   = (boRepeat) ? 1 : 0;
	_WriteI2c(suCfg_m.reg);
}

/**
 @brief Check if next value is ready
 @param [out] bool true if ready or false if not
*/
bool CMCP3421::IsReady()
{
	if (_ReadI2c() < 0)
		return false;
	
	return (suStatus_m.bit.RDY == 0) ? true : false;
}

/**
 @brief Trigger one conversion
*/
void CMCP3421::Trigger()
{
	_WriteI2c(suCfg_m.reg | 0x80);
}

/**
 @brief Read I2C
 @param [out] 0 on success or -1 on error
*/
int CMCP3421::_ReadI2c()
{
	uint8_t u8Data;
	uint8_t u8Len = (suCfg_m.bit.SR == eSR_18Bit) ? 4 : 3;
	
	if ((u8Len != coI2C_m->requestFrom(u8Addr_m, u8Len)) ||
	    (u8Len < 3))
		return -1;
	
	u8Data     = (uint8_t)coI2C_m->read();
	s32Value_m = ((u8Data & 0x80) != 0) ? -1 : 0;
	s32Value_m = (s32Value_m & 0xFFFFFF00) | u8Data;
	
	for (u8Len--; u8Len > 1; u8Len--)
	{
		s32Value_m <<= 8;
		s32Value_m  |= (uint8_t)coI2C_m->read();
	}
	
	suStatus_m.reg = (uint8_t)coI2C_m->read();
	return 0;
}

/**
 @brief Write I2C
 @param [in] value write data
*/
void CMCP3421::_WriteI2c(uint8_t u8Value)
{
	coI2C_m->begin();
	coI2C_m->beginTransmission(u8Addr_m);
	coI2C_m->write(u8Value);
	coI2C_m->endTransmission();
}

//===| eof - end of file |====================================================
