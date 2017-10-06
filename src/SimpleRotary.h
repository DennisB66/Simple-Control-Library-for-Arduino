// Copyright  : Dennis Buis (2017)
// License    : MIT
// Platform   : Arduino
// Library    : Simple Control Library for Arduino
// File       : SimpleRotary.h
// Purpose    : handle input from a rotary encoder
// Repository : https://github.com/DennisB66/Simple-Control-Library-for-Arduino

#ifndef _SIMPLE_ROTARY_H
#define _SIMPLE_ROTARY_H

class SimpleRotary
{
public:
  SimpleRotary( int, int);

  static void handle();

  bool changed();
  int  position();
  void setPosition( int);

  void setMinMax( int, int, bool = false);
  void setMinMax( int, int, int, bool = false);

private:
  static int _pinD0;                  // pin for rotate line D0 (must be 2 on Arduino Uno)
  static int _pinD1;                  // pin for rotate line D1 (must be 3 on Arduino Uno)

  static volatile int   _pos;         // encoder count value
  static volatile int   _posMin;      // encoder count minimal value
  static volatile int   _posMax;      // encoder count maxiaml value
  static volatile int   _posInc;
  static volatile bool  _loop;        // encoder count loop indicator

  static void _pulseDetect();
};

#endif
