// Copyright  : Dennis Buis (2017)
// License    : MIT
// Platform   : Arduino
// Library    : Simple Control Library for Arduino
// File       : SimpleScheluder.cpp
// Purpose    : Receiving input from buttons (incuding auto-repeat)
// Repository : https://github.com/DennisB66/Simple-Control-Library-for-Arduino

#include <Arduino.h>
#include "TimerOne.h"
#include "SimpleScheduler.h"
#include "SimpleDevice.h"

SimpleTask* SimpleScheduler::_rootSimpleTaskList = nullptr;

SimpleTask::SimpleTask( TaskHandler func, int freq)
{
  _thisTaskHandler = func;
  _freq            = freq;
  _nextTask        = nullptr;
}

TaskHandler SimpleTask::getTaskHandler()
{
  return _thisTaskHandler;
}

void SimpleTask::setTaskHandler( TaskHandler func)
{
  _thisTaskHandler = func;
}

void SimpleTask::setNextTask( SimpleTask* task)
{
  _nextTask = task;
}

SimpleTask* SimpleTask::getNextTask()
{
  return _nextTask;
}

/****************************************************************************/

SimpleScheduler::SimpleScheduler( long t)
{
  Timer1.initialize( t);

  _rootSimpleTaskList = nullptr;
}

void SimpleScheduler::begin()
{
  attachHandler( SimpleDevice::handle);

  start();
}

void SimpleScheduler::start()
{
  Timer1.attachInterrupt( _handle);
}

void SimpleScheduler::stop()
{
  Timer1.detachInterrupt();
}

void SimpleScheduler::attachHandler( TaskHandler func, int freq)
{
  SimpleTask* task = new SimpleTask( func, freq);
  SimpleTask* last = _rootSimpleTaskList;

  if ( last == nullptr) {
    _rootSimpleTaskList = task;
  } else {
    while ( last->getNextTask() != nullptr) {

      last = last->getNextTask();
    }

    last->setNextTask( task);
  }
}

void SimpleScheduler::print()
{
  SimpleTask* next = _rootSimpleTaskList;
  int         step = 0;

  Serial.print  ( F( "print start"));
  while ( next != nullptr) {
    Serial.print( F( "/step "));
    Serial.print(  step++);
    next = next->getNextTask();
  }
  Serial.println( F( "/stop"));
}


void SimpleScheduler::_handle()
{
  SimpleTask* next = _rootSimpleTaskList;
  TaskHandler task;

  //Serial.print  ("handle start");
  while ( next != nullptr) {
    //Serial.print("/step ");
    //Serial.print(  step++);
    task = next->getTaskHandler();
    ( *task)();
    next = next->getNextTask();
  }
  //Serial.println("/stop");
}
