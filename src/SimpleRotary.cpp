// Copyright  : Dennis Buis (2017)
// License    : MIT
// Platform   : Arduino
// Library    : Simple Control Library for Arduino
// File       : SimpleRotary.cpp
// Purpose    : handle input from a rotary encoder
// Repository : https://github.com/DennisB66/Simple-Control-Library-for-Arduino

#include <Arduino.h>
#include "SimpleRotary.h"

int SimpleRotary::_pinD0 = 2;
int SimpleRotary::_pinD1 = 3;

volatile int  SimpleRotary::_pos    =    0;
volatile int  SimpleRotary::_posMin = -127;
volatile int  SimpleRotary::_posMax =  127;
volatile int  SimpleRotary::_posInc =    1;
volatile bool SimpleRotary::_loop   =  false;

SimpleRotary::SimpleRotary( int pinD0, int pinD1)
{
  pinMode( _pinD0 = pinD0, INPUT_PULLUP); // line D0 = encoder rotate (-)
  pinMode( _pinD1 = pinD1, INPUT_PULLUP); // line D1 = encoder rotate (+)

  // noInterrupts();
  // attachInterrupt( digitalPinToInterrupt( _pinD0), _pulseDetect, RISING);
  // attachInterrupt( digitalPinToInterrupt( _pinD1), _pulseDetect, RISING);
  // interrupts();
}

// SimpleRotary::~SimpleRotary()
// {
//   // noInterrupts();
//   // detachInterrupt( digitalPinToInterrupt( _pinD0));
//   // detachInterrupt( digitalPinToInterrupt( _pinD1));
//   // interrupts();
// }

void SimpleRotary::handle()
{
  _pulseDetect();
}

void SimpleRotary::_pulseDetect()         // note this works only if pinD0 = 2 & pinD1 = 3
{                                         // (as for the Arduino Uno)
  static volatile byte last = 0b0000;   // bit 3 = current pinD0, bit 1 = previous pinD0
                                          // bit 4 = current pinD1, bit 2 = previous pinD1
  //noInterrupts();                         // block new interrupts during this thread

 last |= ( digitalRead( _pinD0) << 2) | ( digitalRead( _pinD1) << 3);

  //reader |= (( PIND & 0b00110000) >> 2);         // read current values for pinD0/pinD1 in bits 3/4

  _pos += ( _posInc * ( last == 0b1101));            // pinD0 / pinD1 HIGH & previously only pinD0 HIGH
  _pos -= ( _posInc * ( last == 0b1110));            // pinD0 / pinD1 HIGH & previously only pinD1 HIGH

  last >>= 2;                           // move current values for pinD0/pinD1 to bits 1/2

  if ( _pos < _posMin) {
    _pos = ( _loop) ? _posMax : _posMin;
  } else
  if ( _pos > _posMax) {
    _pos = ( _loop) ? _posMin : _posMax;
  }

  //interrupts();                           // allow new interrupts
}

bool SimpleRotary::changed()
{
  static int pos;                       // last encoderCount value

  if ( pos != _pos) {                 // if  new value
    pos = _pos;                       // set new value

    return true;                          // success:    new value available
  } else {
    return false;                         // failure: no new value available
  }
}

int SimpleRotary::position()
{
  return _pos;
}

void SimpleRotary::setPosition( int pos)
{
  _pos = pos;

  if ( _pos < _posMin) {
    _pos = ( _loop) ? _posMax : _posMin;
  } else
  if ( _pos > _posMax) {
    _pos = ( _loop) ? _posMin : _posMax;
  }

  changed();
}

void SimpleRotary::setMinMax( int min, int max, bool loop)
{
  setMinMax( min, max, 1, loop);
}

void SimpleRotary::setMinMax( int min, int max, int inc, bool loop)
{
  if ( min < max) {
    _posMin =  min;
    _posMax =  max;
    _posInc =  inc;
    _loop   =  loop;
  }  else {
    _posMin =  max;
    _posMax =  min;
    _posInc = -inc;
    _loop   =  loop;
  }
}
