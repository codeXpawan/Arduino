// #include "Arduino.h"
#include "Motor.h"


Motor::Motor(int pulse, int forward, int backward) {
  pinMode(pulse,OUTPUT);
  pinMode(forward,OUTPUT);
  pinMode(backward,OUTPUT);
  Motor::pulse = pulse;
  Motor::forward = forward;
  Motor::backward = backward;
}

void Motor::rotate(int value, int time_in_milli_sec) {
  long start_time = millis();
  while(millis()- start_time < time_in_milli_sec){
    if(value>0){
      analogWrite(pulse,value);
      digitalWrite(forward, HIGH);
      digitalWrite(backward, LOW);
    }else if(value < 0){
      analogWrite(pulse,abs(value));
      digitalWrite(forward, LOW);
      digitalWrite(backward, HIGH);
    }
    else{
      digitalWrite(forward, LOW);
      digitalWrite(backward, LOW);
    }
  }
  digitalWrite(forward, LOW);
  digitalWrite(backward, LOW);
}
