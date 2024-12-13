#ifndef Motor_H
#define Motor_H
#include <Arduino.h>
class Motor{
  public:
    Motor(int forward, int backward, int pulse);
    void rotate(int speed);
    int forward;
    int backward;
    int pulse;
};
#endif