/**
 @file readADC.ino
 @brief Example for accessing the MCP3421 analog-digital converter
 @author Dirk Ohme <dirk_ohme@hotmail.com>
*/

#include <Wire.h>
#include <MCP3421.h>

CMCP3421 coMCP3421;

void setup() {
  Serial.begin(9600);
  Serial.println("RESET");
  Serial.println();
  
  coMCP3421.Init();
  coMCP3421.Trigger();
  Serial.println("Init");
}

void loop() {
  int32_t s32Value;
	
  if (coMCP3421.IsReady())
  {
    s32Value = coMCP3421.ReadValue();
    Serial.printf("\nADC: 0x%08lX (%ld)\n", s32Value, s32Value);
    coMCP3421.Trigger();
  }
  else
  {
    Serial.printf(".");
  }

  delay(100);
}
