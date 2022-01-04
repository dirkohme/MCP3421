/**
 @file readADC.ino
 @brief Example for accessing the MCP3421 analog-digital converter
 @author Dirk Ohme <dirk_ohme@hotmail.com>
*/

#include <Wire.h>
#include <MCP3421.h>

CMCP3421 coADC;

void setup() {
  Serial.begin(9600);
  Serial.println("RESET");
  Serial.println();

  coADC.init();
}

void loop() {
  int32_t s32Value_l = coADC.readADC();
  Serial.printf("ADC: 0x%08lX (%ld)\n", s32Value_l, s32Value_l);
  delay(500);
}
