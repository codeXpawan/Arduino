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

long Motor::rotate(int value, int pin) {
  long start_time = millis();
  while(digitalRead(pin) == 0){
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
  return millis()-start_time;
}
