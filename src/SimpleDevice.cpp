// Copyright  : Dennis Buis (2017,2020)
// License    : MIT
// Platform   : Arduino
// Library    : Simple Control Library for Arduino
// File       : SimpleDevice.cpp
// Purpose    : base class for button, rotaty, etc.
// Repository : https://github.com/DennisB66/Simple-Control-Library-for-Arduino

#include "SimpleDevice.h"
// #include "SimplePrint.h"

SimpleDevice* SimpleDevice::_device[ MAX_DEVICES] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int           SimpleDevice::_deviceCount = 0;

SimpleDevice::SimpleDevice()
{
  if ( _deviceCount < MAX_DEVICES) {
    _device[ _deviceCount] = this;
    _deviceEntry           = _deviceCount++;
  }
}

void SimpleDevice::handle()
{
  for ( int i = 0; i < _deviceCount; i++) {
    _device[i]->_handleDevice();
  }
}

void SimpleDevice::_handleDevice()                          // device logic
{
  // virtual function
}

SimpleDeviceHandler::SimpleDeviceHandler( unsigned long msec) : SimpleScheduler( msec)
{
  attachHandler( SimpleDevice::handle);
  start();
}