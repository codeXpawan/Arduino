#include<ros.h>
#include <geometry_msgs/Twist.h>
#include<ros/time.h>
#define right_motor_forward 3
#define right_motor_backward 4
#define left_motor_forward 5
#define left_motor_backward 6
#define left_speed 9
#define right_speed 10


ros::NodeHandle  nh;

float demandx, demandz;
float length = 0.015;

void cmd_vel_cb( const geometry_msgs::Twist& twist){
  demandx = twist.linear.x;
  demandz = twist.angular.z;
  Serial.println("message received.");
}
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", cmd_vel_cb );

double speed_act_left = 0;                    //Actual speed for left wheel in m/s
double speed_act_right = 0;                   //Actual speed for right wheel in m/s

void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.subscribe(sub);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  speed_act_left = demandx - demandz *(length/2);
  speed_act_right = demandx + demandz *(length/2);
  if(speed_act_left > 0)
    forward(left_motor_forward,left_motor_backward,left_speed,speed_act_left);
  if(speed_act_left < 0)
    backward(left_motor_forward,left_motor_backward,left_speed,speed_act_left);
  if(speed_act_right > 0)
    forward(right_motor_forward,right_motor_backward,right_speed,speed_act_right);
  if(speed_act_right < 0)
    backward(right_motor_forward,right_motor_backward,right_speed,speed_act_right);
  

  nh.spinOnce();
}

void forward(int forward_pin, int backward_pin, int speed_pin, long speed)
{
  analogWrite(speed_pin,min(abs(speed),255));
  digitalWrite(forward_pin, HIGH);
  digitalWrite(backward_pin, LOW);
}

void backward(int forward_pin, int backward_pin, int speed_pin, long speed)
{
  analogWrite(speed_pin,min(abs(speed),255));
  digitalWrite(forward_pin, LOW);
  digitalWrite(backward_pin, HIGH);
}
