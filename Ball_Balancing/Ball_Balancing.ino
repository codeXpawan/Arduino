// #include<Servo.h>
#include <SharpIR.h>
// Define model and input pin:
#define IRPin A0
#define model 1080

SharpIR mySensor = SharpIR(IRPin, model);
// Servo myservo;
// int trigpin = 5;
// int echopin = 6;
// int servopin = 3;
float compare_time = 0;
//pid value
float Kp = 1.5;
float Ki = 4;
float Kd = 0.0005;
float setpoint = 15;
float prev_error = 0;
//max rotation and min rotation
// min_degree = 0;
// long time = millis();
float error_prior = 0;
float iteration_time = 0.001;

// max_degree = 180;

// //max distance and min distance
// max_distance = 40;
// min_distance = 0;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // pinMode(trigpin, OUTPUT);
  // pinMode(echopin, INPUT);
  // myservo.attach(servopin);
}

void loop() {
  // put your main code here, to run repeatedly:
  float start_time = millis()/1000.00;
  // digitalWrite(trigpin, LOW);
  // delayMicroseconds(20);
  // digitalWrite(trigpin, HIGH);
  // delayMicroseconds(100);
  // float duration = pulseIn(echopin, HIGH);
  // float distance = duration * 0.0344 / 2;
  // float distance = mySensor.distance();
  // if((millis()/1000.00 )-compare_time > 2 && distance >16 && distance < 17){
  //   distance = 0;
  // }
  // if(distance < 12)
  //   compare_time = millis()/1000.00;
    
  if(distance > 100)
    distance = 0;
  Serial.print(distance);
  Serial.print("x");
  float error = setpoint - distance;

  float P_gain = Kp * error;

  float I_gain = Ki*(error + prev_error)*iteration_time;

  float D_gain = (Kd * (error - prev_error))/ iteration_time;

  
  float output = P_gain + D_gain + I_gain;
  prev_error = error;
  // Serial.println(output);


  float fval = map(output, -16.2, 16.2, 0, 180);



  if(fval < 0)
    fval = 0;
  if(fval > 180)
    fval = 180;

  Serial.print(fval);
  Serial.print("x");
  
  myservo.write(fval);
  // iteration_time = millis()/1000.00 - start_time;
  float time = (float)millis()/1000;
  Serial.println(time);
  // Serial.print(" ");
  // Serial.println(iteration_time);
  //delay(100);
}