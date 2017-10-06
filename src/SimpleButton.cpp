// Copyright  : Dennis Buis (2017)
// License    : MIT
// Platform   : Arduino
// Library    : Simple Control Library for Arduino
// File       : SimpleButton.cpp
// Purpose    : Receiving input from buttons (incuding buffering and auto-repeat)
// Repository : https://github.com/DennisB66/Simple-Control-Library-for-Arduino

#include "SimpleButton.h"

byte SimpleButton::_pin         = 0;                      // connected pin
bool SimpleButton::_repeatMode  = false;                  // repeat mode activated
byte SimpleButton::_curr        = 0;                      // last read click value
byte SimpleButton::_last        = 0;                      // first available click value in buffer
byte SimpleButton::_next        = 0;                      // first free position in buffer
byte SimpleButton::_buffer[ CLICK_BUFFER_LENGTH];         // click value (ring) buffer

SimpleButton::SimpleButton( int pin, bool repeatMode)
{
  pinMode( _pin = pin, INPUT_PULLUP);

  _repeatMode = repeatMode;
}

void SimpleButton::handle()                               // simple state engine
{
  static int           state = WAIT_FOR_CLICK;            // state for state engine
  static unsigned long ticks = millis();                  // stopwatch for current  click
  static unsigned long count = 0;                         // number of unprocessed clicks

  if ( digitalRead( _pin) == LOW) {                       // if button is active
    switch ( state) {
    case WAIT_FOR_CLICK:
      ticks = millis();                                   // reset stopwatch for current click
      count++;                                            // keep number of unprocessed clicks
      state = CHECK_BOUNCING;                             // goto next state (bouncing check)
      break;

    case CHECK_BOUNCING:
      if ( millis() - ticks > BOUNCE_DELAY) {             // check if button is still down after 25 msec
        state = PREP_RETRIGGER;                           // goto next state (repeat mode preparation)
      }
      break;

     case PREP_RETRIGGER :
      if ( millis() - ticks > DOUBLE_DELAY) {             // extra wait to allow for double clicks
        if ( _repeatMode) {                               // repeat mode activated
          _addNextClick( CLICK_NORMAL);                   // insert (normal) click in buffer
          count = 0;
          state = WAIT_RETRIGGER;                         // goto next state (repeat mode check)
        } else {
          _addNextClick( CLICK_HOLD);                     // insert (normal) click in buffer
          count = 0;
          state = LOOP_ENDLESSLY;                         // goto next state (all done)
        }
      }
      break;

    case WAIT_RETRIGGER:
      if ( millis() - ticks > REPEAT_DELAY) {             // check if button is held long enough
        state = LOOP_RETRIGGER;                           // goto next state (repeat mode active)
      }
      break;

    case LOOP_RETRIGGER:
      if ( millis() - ticks > REPEAT_SPEED) {             // check if ready to repeat click
        _addNextClick( CLICK_NORMAL);                     // insert (normal) click in buffer
        ticks = millis();                                 // reset stopwatch for current click
      }
      break;

    case LOOP_ENDLESSLY:                                  // loop until buton is released
      break;
    }
  } else {                                                // button is released (potential double click)
    if ( count  && ( millis() - ticks > DOUBLE_DELAY)) {  // provide extra time to check double clicks
      _addNextClick(( count == 1) ? CLICK_NORMAL : CLICK_DOUBLE); // insert click in buffer
      count = 0;                                          // reset unprocessed clicks
    };
    state = WAIT_FOR_CLICK;                               // reset state engine
  }
}

#define buffered (( CLICK_BUFFER_LENGTH + _next - _last) % CLICK_BUFFER_LENGTH)
                                                          // calculate ring buffer population
byte SimpleButton::available()
{
  return buffered;                                        // return availabe clicks in buffer
}

byte SimpleButton::read()
{
  return _curr = _getNextClick();                         // read click from buffer
}

byte SimpleButton::lastValue()
{
  return _curr;                                           // return last read click
}

void SimpleButton::_addNextClick( byte c)
{
  if ( buffered < CLICK_BUFFER_LENGTH) {                  // if free slots available
    _buffer[ _next++] = c;                                // populate first free slot
    _next %= CLICK_BUFFER_LENGTH;                         // keep pointer within boundaries
  }
}

byte SimpleButton::_getNextClick()
{
  if ( buffered) {                                    // if clicks available
    byte c = _buffer[ _last++];                           // read oldest click

    _last %= CLICK_BUFFER_LENGTH;                         // keep pointer within boundaries

    return c;                                             // success: return click value
  } else {
    return 0;                                             // failure: return NOTHING
  }
}
