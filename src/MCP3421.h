/**
 @file MCP3421.h
 @brief This is a library for MCP3421 analog digital converter
 @author Dirk Ohme <dirk_ohme@hotmail.com>
*/

#ifndef MCP3421_H
#define MCP3421_H

#include <Arduino.h>
#include <Wire.h>

/**
 @class CMCP3421
 @brief MCP3421 basic functions
*/
class CMCP3421 {
  public:
	static const uint32_t Version        = 0x01000000ul;
	static const uint8_t  DefaultAddress = 0x68;

	enum EGain {
		eGain_x1 = 0,
		eGain_x2,
		eGain_x4,
		eGain_x8,
	};
	
	enum ESampleRate {
		eSR_12Bit = 0,
		eSR_14Bit,
		eSR_16Bit,
		eSR_18Bit,
	};
  
  public:
			CMCP3421(const float   fFactor = 1.0,
			         const uint8_t u8Addr  = DefaultAddress);
	void		Init(const bool        boRepeat = false,
			     const ESampleRate eSR      = eSR_18Bit,
			     const EGain       eGain    = eGain_x1,
			           TwoWire*    coI2C    = &Wire);
	bool		IsReady();
	inline int32_t	ReadRaw()   { return s32Value_m; }
	inline float	ReadValue() { return (fFactor_m * (float)s32Value_m); }
	void		Trigger();

  private:
	typedef union {
	  struct {
	    uint8_t GAIN : 2;
	    uint8_t SR   : 2;
	    uint8_t OC   : 1;
	    uint8_t Cx   : 2;
	    uint8_t RDY  : 1;
	  } bit;
	  uint8_t reg;
	} Config;

	TwoWire*	coI2C_m;
	float		fFactor_m;
	int32_t		s32Value_m;
	Config		suCfg_m;
	Config		suStatus_m;
	uint8_t		u8Addr_m;
	
	int		_ReadI2c();
	void		_WriteI2c(uint8_t u8Value);
};

#endif // MCP3421_H

//===| eof - end of file |====================================================
