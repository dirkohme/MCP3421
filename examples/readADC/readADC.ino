/**
 @file readADC.ino
 @brief Example for accessing the MCP3421 analog-digital converter
 @author Dirk Ohme <dirk_ohme@hotmail.com>
 Input voltage is divided by two resistors R1 and R2:
 ~~~~~
   Uadc = Uin * R1 / (R1 + R2)
 ~~~~~
 with R1 = 1k, R2 = 4k7 + 4k7 = 9k4
*/

#undef  TEST
#define TEST

#include <Wire.h>
#include <MCP3421.h>
#ifdef TEST
#  include <i2cdetect.h>
#endif

CMCP3421 coMCP3421(0.1692);

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println("RESET");
  Serial.println();
  
#ifdef TEST
  // scan i2c
  Serial.println("i2cdetect");
  i2cdetect();  // default range from 0x03 to 0x77
  Serial.println();
#endif

  coMCP3421.Init();
  Serial.println("Init");
  coMCP3421.Trigger();
}

void loop() {
  float   fValue;
  int32_t s32Value;
	
  if (coMCP3421.IsReady())
  {
    fValue   = coMCP3421.ReadValue();
    s32Value = coMCP3421.ReadRaw();
    Serial.printf("\nADC: 0x%08lX (%ld) -> %.3f\n", s32Value, s32Value, fValue);
    coMCP3421.Trigger();
  }
  else
  {
    Serial.printf(".");
  }

  delay(100);
}
