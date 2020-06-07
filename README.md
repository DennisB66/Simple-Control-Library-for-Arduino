# Simple Control Library for Arduino and ESP8266
Library for operating an Arduino or ESP8266 controlled by buttons, rotary encoders, etc.

## Functionality

The functions in the class SimpleScheduler include:
```
SimpleButton    // button constructor
available()     // return available clicks in buffering
read()          // read next click value from buffer
lastValue()     // return last read click value

SimpleRotary    // rotary constructor
setMinMax()     // set rotary position value boundaries
setPosition()   // set rotary position
changed()       // true = rotary value has changed
position()      // read current rotary position

SimpleOutput    // pattern based output pin
on()            // activate output
off()           // deactivate output
toggle()        // toggle output
blink()         // togglw output continuously
setPattern()    // set output pattern
void start()    // start output pattern sequence
void stop()     // stop  output pattern sequence
```

## Library Dependencies

- https://github.com/DennisB66/Simple-Utility-Library-for-Arduino

Version history:
```
0.1             // initial version
0.11            // some cleanup