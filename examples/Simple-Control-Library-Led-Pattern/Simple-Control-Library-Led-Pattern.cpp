#include <Arduino.h>
#include "SimpleScheduler.h"
#include "SimpleOutput.h"

#define SOS_CODE 0b10101011011011010101000000
#define SOS_MSEC 150

SimpleDeviceHandler handler( 10);
SimpleOutput        led( LED_BUILTIN);

void setup()
{
  Serial.begin( 9600);
  Serial.println( "READY");
  
  Serial.println( "Blink pattern (500 msec) repeating for 5 secs");
  led.blink( 500);
  delay( 5000);
  led.off();

  delay( 3000);

  Serial.println( "S.O.S pattern (150 msec) repeating forever...");
  led.setPattern( SOS_CODE, SOS_MSEC, OUTPUT_REPEAT);
}

void loop()
{
}
