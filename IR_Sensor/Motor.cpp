#include "Motor.h"

Motor::Motor(int forward, int backward, int pulse){
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(pulse, OUTPUT);
  Motor::forward = forward;
  Motor::backward = backward;
  Motor::pulse = pulse;
}

void Motor::rotate(int speed){
  if(speed > 0){
    digitalWrite(forward, HIGH);
    digitalWrite(backward, LOW);
    analogWrite(pulse, speed);
  }
  else if(speed < 0){
    digitalWrite(forward, LOW);
    digitalWrite(backward, HIGH);
    analogWrite(pulse, abs(speed));
  }
  else{
    digitalWrite(forward, LOW);
    digitalWrite(backward, LOW);
  }
}