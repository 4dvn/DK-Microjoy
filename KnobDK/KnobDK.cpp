/*
  KnobDK.cpp - Library for MIDI potentiometers
*/

#include "Arduino.h"
#include "KnobDK.h"

#define minCC 0
#define maxCC 127 + 1
#define maxInt 65535

// Set controller averaging to smooth output (range 0.1-1, lower is smoother)
#define smoothing 0.4
// Untouched controls require a higher change amount to output midi (idle jitter suppression)
#define idleDelay 100

// Standard knob without shift capability
KnobDK::KnobDK(byte pin, int cc, int min, int max)
{
    _pin = pin;
    _ccNum = cc;
    _min = min;
    _max = max;
    _idle = idleDelay;

    // Get initial value of analog control to avoid a burst of midi when powering up
    _val = analogRead(_pin);
    _ccVal = map(_val, _min, _max, minCC, maxCC);
}

// Extended knob with secondary shift capability
KnobDK::KnobDK(byte pin, int cc, int cc2, int min, int max)
{
    _pin = pin;
    _ccNum = cc;
    _ccNum2 = cc2;
    _min = min;
    _max = max;
    _idle = idleDelay;

    // Get initial value of analog control to avoid a burst of midi when powering up
    _val = analogRead(_pin);
    _ccVal = map(_val, _min, _max, minCC, maxCC);
}

// bool refresh()
// Returns true when MIDI CC value has changed
bool KnobDK::refresh() 
{
    _val = analogRead(_pin);
    
    // Increment idle timer for jitter suppression on untouched controls
    _idle++;
    if(_idle >= maxInt) {
        _idle = idleDelay;
    }

    // Scale analog knob range to midi range 
    int inputScaled = map(_val, _min, _max, minCC, maxCC);
    

    // Smooth controller with weighted averaging
    inputScaled = smoothing * inputScaled + (1-smoothing) * _ccVal;

    // Update MIDI CC - require a larger change if the control has been idle for a while
    if((_ccVal != inputScaled && _idle < idleDelay) || abs(_ccVal - inputScaled) > 1)
    {        
        _ccVal = inputScaled;
        _idle = 0;
        return true;
    }
    
    return false;
}

int KnobDK::val()
{
    return _val;
}

int KnobDK::ccNum()
{ 
    return _ccNum;
}

int KnobDK::ccNum(bool shifted)
{
    if(shifted) return _ccNum2;    
    return _ccNum;
}

int KnobDK::ccVal()
{
    return _ccVal;
}