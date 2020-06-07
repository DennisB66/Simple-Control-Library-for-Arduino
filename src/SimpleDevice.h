// Copyright  : Dennis Buis (2017,2020)
// License    : MIT
// Platform   : Arduino
// Library    : Simple Control Library for Arduino
// File       : SimpleDevice.h
// Purpose    : base class for button, rotaty, etc.
// Repository : https://github.com/DennisB66/Simple-Control-Library-for-Arduino

#ifndef _SIMPLE_DEVICE_H
#define _SIMPLE_DEVICE_H

#include <Arduino.h>
#include "SimpleScheduler.h"

#define MAX_DEVICES             8

// #define SIMPLE_DEVICE_LIST(T)  SimpleScheduler scheduler( T, SimpleDevice::handle);

class SimpleDevice
{
public:
  SimpleDevice();                       // constructor

  static void handle();                 // handle device actions

protected:
  static SimpleDevice* _device[MAX_DEVICES];
  static int           _deviceCount;
  int                  _deviceEntry;

  virtual void _handleDevice();
};

class SimpleDeviceHandler : public SimpleScheduler
{
public:
  SimpleDeviceHandler( unsigned long);
};

#endif
