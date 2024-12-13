#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor {
  public:
    //Constructor - Plus and Minus are the Motor output / en_a and en_b are the encoder inputs
    Motor(int pulse, int forward, int backward);
    //Spin the motor with a percentage value
    void rotate(int value,int time_in_milli_sec);
  private:
    int pulse;
    int forward;
    int backward;
};

#endif
