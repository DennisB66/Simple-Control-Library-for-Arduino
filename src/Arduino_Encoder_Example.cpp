#include <Arduino.h>
#include "SimpleScheduler.h"
#include "SimpleRotary.h"
#include "SimpleButton.h"

SimpleScheduler scheduler( 5000);
SimpleRotary    rotary( A1, A2);
SimpleButton    button( A0, false);

void setup() {
  Serial.begin( 9600);

  rotary.setMinMax( -3, 3);

  scheduler.begin();

  Serial.println( "# ready for encoder reading"); // ready for looping
}

void loop()
{
  if ( rotary.changed()) {                     // check on new value for rotation
    Serial.print  ( "# encoder value = ");
    Serial.println( rotary.position());
  }

  if ( button1.available()) {                     // check on new value for press
    switch( button1.read()) {
      case BUTTON_NORMAL:
      Serial.println( "# button 1 normal click");
      break;
      case BUTTON_DOUBLE:
      Serial.println( "# button 1 double click");
      break;
      case BUTTON_HOLD:
      Serial.println( "# button 1 click & hold");
      break;
    }
  }

  if ( button2.available()) {                     // check on new value for press
    switch( button2.read()) {
      case BUTTON_NORMAL:
      Serial.println( "# button 2 normal click");
      break;
      case BUTTON_DOUBLE:
      Serial.println( "# button 2 double click");
      break;
      case BUTTON_HOLD:
      Serial.println( "# button 2 click & hold");
      break;
    }
  }
}
