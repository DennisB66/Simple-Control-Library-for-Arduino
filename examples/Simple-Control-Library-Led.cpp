#include <Arduino.h>
#include "SimpleScheduler.h"
#include "SimpleOutput.h"
#include "SimplePrint.h"

#define SOS_CODE 0b10101011011011010101000000
#define SOS_MSEC 150

SimpleScheduler scheduler( 1);
SimpleOutput    led( 13);

void setup()
{
  BEGIN( 9600);
  PRINT( "READY") LF;

  PRINT( "Blink pattern (500 msec) repeating for 5 secs") LF;
  led.blink( 500);
  delay( 5000);
  led.off();

  delay( 3000);

  PRINT( "S.O.S pattern (150 msec) repeating forever...") LF;
  led.setPattern( SOS_CODE, SOS_MSEC, OUTPUT_REPEAT);
}

void loop()
{
}
