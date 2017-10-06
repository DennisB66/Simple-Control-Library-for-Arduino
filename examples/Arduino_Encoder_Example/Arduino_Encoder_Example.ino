#include <Arduino.h>
#include "SimpleEncoder.h"

SimpleRotary rotary( A1, A2);
SimpleButton button( A0);

void setup() {
  Serial.begin( 9600);
  
  Serial.println( "# ready for encoder reading"); // ready for looping
}

void loop(){

  if ( rotary.changed()) {                     // check on new value for rotation
    Serial.print  ( "# encoder value = ");
    Serial.println( encoder.getCount());
  }

  if ( button.pressed()) {                     // check on new value for press
    Serial.println( "# button pressed");
  }
}
