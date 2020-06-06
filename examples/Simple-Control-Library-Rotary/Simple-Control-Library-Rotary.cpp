#include <Arduino.h>
#include "SimpleScheduler.h"
#include "SimpleRotary.h"
#include "SimpleButton.h"
#include "SimplePrint.h"

#define ESP8266

SimpleScheduler scheduler( 1);
SimpleButton    button( D0, false);
SimpleRotary    rotary( D1, D2);

String buttonLabel[] = { "NO CLICK", "NORMAL CLICK", "DOUBLE CLICK", "CLICK HOLD"};

void printValues();

void setup()
{
  BEGIN( 9600);

  rotary.setMinMax( 0, 6, true);

  PRINT( "Ready for reading") LF;

  printValues();
}

void loop()
{
  if ( rotary.changed()) {                     // check on new value for rotation
    printValues();
  }

  while ( button.available()) {                     // check on new value for press
    button.read();
    printValues();
  }

  //yield();
}

void printValues()
{
  LABEL( "Rotary position", rotary.position());
  PRINT( " / ");
  LABEL( "Button status", buttonLabel[ button.lastValue()]) LF;
}
