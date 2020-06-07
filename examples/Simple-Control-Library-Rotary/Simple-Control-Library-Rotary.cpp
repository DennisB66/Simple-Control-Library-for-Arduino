#include <Arduino.h>
#include "SimpleScheduler.h"
#include "SimpleRotary.h"
#include "SimpleButton.h"

SimpleDeviceHandler handler( 10);
SimpleButton        button( D0, false);
SimpleRotary        rotary( D1, D2);

String buttonLabel[] = { "NO CLICK", "NORMAL CLICK", "DOUBLE CLICK", "CLICK HOLD"};

void printValues();

void setup()
{
  Serial.begin( 9600);

  rotary.setMinMax( 0, 6, true);

  Serial.println( "Rotary device ready for reading");

  printValues();
}

void loop()
{
  if ( rotary.changed()) {                                  // check on new value for rotation
    printValues();
  }

  while ( button.available()) {                             // check on new value for press
    button.read();
    printValues();
  }

  //yield();
}

void printValues()
{
  Serial.print( "Rotary value = "); Serial.print( rotary.position());
  Serial.print( " / ");
  Serial.print( "Button state = "); Serial.print( buttonLabel[ button.lastValue()]);
  Serial.println();
}
