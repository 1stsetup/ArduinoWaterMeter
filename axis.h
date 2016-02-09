#ifndef axis_h
#define axis_h

#include "Arduino.h"

class Axis
{
  public:
    Axis(char letter);
    void Set(int value);
    int prevValue();
  private:
    int _max;
    int _min;
    int _mid;
    int _newmax;
    int _newmin;
    int _minchanged;
    int _maxchanged;
    int _count;
    int _dir;
    int _caldir;
    int _calibrating;
    int _firstcal;
    char _letter;
    int _width;
    int _prevvalue;
    int _firstvalue;
};

#endif
