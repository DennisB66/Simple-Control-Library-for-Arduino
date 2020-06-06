#include <Arduino.h>
#include "SimpleScheduler.h"
#include "SimplePrint.h"

SimpleScheduler scheduler( 1000);

void tick() { Serial.print("*"); }

void setup()
{
  BEGIN( 9600);

  scheduler.attachHandler( tick);
  scheduler.start();

  PRINT( "# Ready") LF;
}

void loop()
{
  //yield();
}
