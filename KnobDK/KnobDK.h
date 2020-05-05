/*
  KnobDK.h - Library for MIDI potentiometers
*/
#ifndef KnobDK_h
#define KnobDK_h

#include "Arduino.h"

class KnobDK
{
  public:
    KnobDK(byte pin, int cc, int min, int max);  
    KnobDK(byte pin, int cc, int cc2, int min, int max);
    bool refresh();
    int val();
    int ccNum();
    int ccNum(bool shifted);    
    int ccVal();
  private:
    byte _pin;
    int _val;
    int _ccVal;
    int _ccNum;
    int _ccNum2;
    int _min;
    int _max;
    unsigned int _idle;
};

#endif