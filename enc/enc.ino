#include <Encoder.h>

#define m1_ain1 2  
#define m1_ain2 3   
#define m1_bin1 4   
#define m1_bin2 5   
#define m1_pwma 9    
#define m1_pwmb 10    
int speed_left=0, speed_right=0;

Encoder knobLeft(11, 12);
Encoder knobRight(7, 8);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(m1_ain1, OUTPUT);
  pinMode(m1_ain2, OUTPUT);
  pinMode(m1_bin1, OUTPUT);
  pinMode(m1_bin2, OUTPUT);
  pinMode(m1_pwma, OUTPUT);
  pinMode(m1_pwmb, OUTPUT);
  // digitalWrite(m1_pwma, HIGH);
  // digitalWrite(m1_pwmb, HIGH);
}

long positionLeft  = -999;
long positionRight = -999;

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    char command = Serial.read();
    if (command == 'L') {
      speed_left = Serial.parseInt();  // Set left motor speed using PWM
    } else if (command == 'R') {
      speed_right = Serial.parseInt();  // Set right motor speed using PWM
    }
  }
  analogWrite(m1_pwma,abs(speed_left));
  analogWrite(m1_pwmb,abs(speed_right));
  if(speed_left > 0){
    forward(m1_ain1,m1_bin1);
    Serial.print("Left_Forward---> ");
    Serial.println(speed_left);
  }
  else if(speed_left<0){
    backward(m1_ain1,m1_bin1);
    Serial.print("Left_Backward---> ");
    Serial.println(speed_left);
  }
  if(speed_right > 0){
    forward(m1_ain2,m1_bin2);
    Serial.print("Right_Forward---> ");
    Serial.println(speed_right);
  }
  else if(speed_left<0){
    backward(m1_ain2,m1_bin2);
    Serial.print("Right_Backward---> ");
    Serial.println(speed_right);
  }
}


void forward(int forward, int backward){
  digitalWrite(forward, HIGH);
  digitalWrite(backward, LOW);
}

void backward(int forward, int backward){
  digitalWrite(forward, LOW);
  digitalWrite(backward, HIGH);
}







