# Simple Control Library for Arduino and ESP8266
Library for operating an Arduino or ESP8266 controlled by buttons, rotary encoders, etc.

## Functionality

The functions in the library include:
```
SimpleButton    // button constructor (1 pin)
available()     // return available clicks in buffering
read()          // read next click value from buffer
lastValue()     // return last read click value

SimpleRotary    // rotary constructor (2 pin)
setMinMax()     // set rotary position value boundaries
setPosition()   // set rotary position
changed()       // true = rotary value has changed
position()      // read current rotary position

SimpleOutput    // output constructor (1 pin)
on()            // activate output
off()           // deactivate output
toggle()        // toggle output
blink()         // togglw output continuously
setPattern()    // set output pattern
void start()    // start output pattern sequence
void stop()     // stop  output pattern sequence
```

## Library Dependencies

- https://github.com/DennisB66/Simple-Scheduler-Library-for-Arduino

Version history:
```
0.4             // initial published version
0.5             // move task schedular to a seperate library
