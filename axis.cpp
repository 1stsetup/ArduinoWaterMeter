#include "Arduino.h"
#include "axis.h"

#define CALCOUNT 30

Axis::Axis(char letter)
{
  _min=32767;
  _max=-32767;
  _minchanged=1;
  _maxchanged=1;
  _count=CALCOUNT;
  _caldir=-1;
  _dir=0;
  _calibrating=1;
  _firstcal = 1;
  _letter = letter;
  _width = -1;
  _prevvalue = 0;
  _firstvalue = 1;
}

int Axis::prevValue()
{
  return _prevvalue;
}

void Axis::Set(int value)
{
  //Serial.print(_letter);
  //Serial.print(": ");
  //Serial.println(value);

    if (value == _prevvalue) {
      return;
    }
    _minchanged = 0;
    _maxchanged = 0;

    if (value < _min) {
      _min = value;
      _minchanged=1;
      //Serial.print(_letter);
      //Serial.print(" : New min: ");
      //Serial.println(_newmin);
    }

    if (value > _max) {
      _max = value;
      _maxchanged=1;
      //Serial.print(_letter);
      //Serial.print(" : New max: ");
      //Serial.println(_newmax);
    }

    if ((_minchanged ==1) || (_maxchanged == 1)) {

      int tmpwidth = abs(_max - _min);
      if ((tmpwidth >= _width) && (tmpwidth > 10)) {
        _width = tmpwidth;

        _newmin = _min + (_width / 10);
        _newmax = _max - (_width / 10);
        
        _mid = _min + ((_max - _min) /2);
        Serial.print(_letter); Serial.print(" | ");
        Serial.print("_min:"); Serial.print(_min);
        Serial.print(" _max:"); Serial.print(_max);
        Serial.print(" _width:"); Serial.print(_width);
        Serial.print(" _mid:"); Serial.println(_mid);
        _firstcal = 0;
      }
    }
  
  if (_firstcal == 0) {
    if ((value < _newmin) && (_dir > -1)) {
      _dir = -1;
      Serial.print("Toggle down: ");
      Serial.print(_letter);
      Serial.print(" : ");
      Serial.println(value);
    }
    if ((value > _newmax) && (_dir < 1)) {
      _dir = 1;
      Serial.print("Toggle up: ");
      Serial.print(_letter);
      Serial.print(" : ");
      Serial.println(value);
    }
  }

  _prevvalue = value;
}

