#include <Arduino.h>
#include "SimpleEncoder.h"

RotaryEncoder encoder( PIN_D0_DEFAULT, PIN_D1_DEFAULT, PIN_D2_DEFAULT)

void setup() {
  Serial.begin  ( 9600);
  Serial.println("Ready for encoder reading");  // ready for looping
}

void loop(){

  if ( encoder.rotated()) {                     // check on new value for rotation
    Serial.print  ( "Encoder Value = ");
    Serial.println( encoder.getCount());
  }

  if ( encoder.pressed()) {                     // check on new value for press
    Serial.println( "Encoder Press");
  }
}
