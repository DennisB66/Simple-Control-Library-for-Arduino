// Copyright  : Dennis Buis (2017)
// License    : MIT
// Platform   : Arduino
// Library    : Simple Control Library for Arduino
// File       : SimpleScheluder.h
// Purpose    : Receiving input from buttons (incuding auto-repeat)
// Repository : https://github.com/DennisB66/Simple-Control-Library-for-Arduino

#ifndef _SIMPLE_SCHEDULER_H
#define _SIMPLE_SCHEDULER_H

typedef void ( *TaskHandler)();

class SimpleTask
{
public:
  SimpleTask( TaskHandler, int = 1);

  void        setTaskHandler( TaskHandler);
  TaskHandler getTaskHandler();

  void        setNextTask( SimpleTask*);
  SimpleTask* getNextTask();

private:
  TaskHandler _thisTaskHandler;
  int         _freq;
  SimpleTask* _nextTask;
};

#include <TimerOne.h>

class SimpleScheduler
{
public:
  SimpleScheduler( long = 5000000);

  void attachHandler( TaskHandler, int = 0);
  void detachhandler();

  void begin();

  void start();
  void stop();

  void print();

private:
  static SimpleTask* _rootSimpleTaskList;
  int                _count;

  static void _handle();
};

#endif
