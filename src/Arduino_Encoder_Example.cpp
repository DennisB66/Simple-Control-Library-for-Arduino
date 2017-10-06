#include <Arduino.h>
#include "SimpleScheduler.h"
#include "SimpleRotary.h"
#include "SimpleButton.h"

SimpleScheduler scheduler( 1000);
SimpleRotary    rotary( A1, A2);
SimpleButton    button( A0, false);

void setup() {
  Serial.begin( 9600);

  Serial.println( "# ready for encoder reading"); // ready for looping

  scheduler.attachHandler( rotary.handle);
  scheduler.attachHandler( button.handle);
  scheduler.start();
}

void loop()
{
  rotary.handle();
  button.handle();

  if ( rotary.changed()) {                     // check on new value for rotation
    Serial.print  ( "# encoder value = ");
    Serial.println( rotary.position());
  }

  if ( button.available()) {                     // check on new value for press
    switch( button.read()) {
      case BUTTON_NORMAL:
      Serial.println( "# button normal click");
      break;
      case BUTTON_DOUBLE:
      Serial.println( "# button double click");
      break;
      case BUTTON_HOLD:
      Serial.println( "# button click & hold");
      break;
    }
  }
}
