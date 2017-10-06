// Copyright  : Dennis Buis (2017)
// License    : MIT
// Platform   : Arduino
// Library    : Simple Control Library for Arduino
// File       : SimpleButton.h
// Purpose    : Receiving input from buttons (incuding auto-repeat)
// Repository : https://github.com/DennisB66/Simple-Control-Library-for-Arduino

#ifndef _SIMPLE_BUTTON_H
#define _SIMPLE_BUTTON_H

#include <Arduino.h>

#define BOUNCE_DELAY   25           // min. time to filter contact bouncing (msec)
#define DOUBLE_DELAY  300           // max. time between double clicks      (msec)
#define REPEAT_DELAY 1000           // min. time before repeat activation   (msec)
#define REPEAT_SPEED  100           // min. time between repeated clicks    (msec)

#define WAIT_FOR_CLICK  0           // state 0: check for button down
#define CHECK_BOUNCING  1           // state 1: check for steady down
#define PREP_RETRIGGER  2           // state 2: prepare for button hold
#define WAIT_RETRIGGER  3           // state 3: check for button hold
#define LOOP_RETRIGGER  4           // state 4: repeat mode activated
#define LOOP_ENDLESSLY  5           // state 5: loop during button hold

#define CLICK_BUFFER_LENGTH   32    // max buffered clicks

#define CLICK_FAIL   0              // normal click
#define CLICK_NORMAL 1              // normal click
#define CLICK_DOUBLE 2              // double click
#define CLICK_HOLD   3              // double click

class SimpleButton
{
public:
  SimpleButton( int, bool = true);  // constructor

  static void handle();             // handle button actions

  byte available();                 // return available clicks in buffering
  byte read();                      // read oldest click from buffer
  byte lastValue();                 // return last read click value

private:
  static byte _pin;                 // connected pin
  static bool _repeatMode;          // true = activates click repeat
  static byte _curr;                // last read click value
  static byte _last;                // first available click value in buffer
  static byte _next;                // first free position in buffer
  static byte _buffer[ CLICK_BUFFER_LENGTH];
                                    // click value (ring) buffer
  static void _addNextClick( byte); // add (newest) click value to buffer
  static byte _getNextClick();      // get (oldest) click value from buffer
};

#endif
