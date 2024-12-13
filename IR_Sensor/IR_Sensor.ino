#include "Motor.h"
#define LIR 2
#define RIR 3

Motor left(10,11,6);
Motor right(8,9,5);

void setup() {
  // put your setup code here, to run once:
  pinMode(LIR,INPUT);
  pinMode(RIR,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int left_ir = digitalRead(LIR);
  int right_ir = digitalRead(RIR);
  if(left_ir == 0 && right_ir == 0){
    left.rotate(150);
    right.rotate(150);
  }
  if(left_ir == 0 && right_ir == 1){
    left.rotate(150);
    right.rotate(-150);
  }
  if(left_ir == 1 && right_ir == 0){
    left.rotate(-150);
    right.rotate(150);
  }
  if(left_ir == 1 && right_ir == 1){
    left.rotate(0);
    right.rotate(0);
  }
  Serial.print("LIR:");
  Serial.println(left_ir);
  Serial.print("RIR:");
  Serial.println(right_ir);
}
