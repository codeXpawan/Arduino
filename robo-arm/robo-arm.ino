
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN  100 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  450 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// our servo # counter
uint8_t servonum = 0;

char data;

int val1 = 150, val2 =150, val3 = 150, val4 = 150;

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}

void loop() {


  if(Serial.available()>0){

    data = Serial.read();
  }
  if(data == 'a'){
      Serial.print("Base Servo 1 (PIN 0)");
      Serial.println(val1);
      pwm.setPWM(0, 0, val1);
      val1++;
    }

    if(data == 'b'){
      Serial.print("Arm Servo back (PIN 2): ");
      Serial.println(val2);
      pwm.setPWM(2, 0, val2);
      val2++;
    }

    if(data == 'c'){
      Serial.print("Arm Servo front (PIN 4) ");
      Serial.println(val3);
      pwm.setPWM(4, 0, val3);
      val3++;
    }

    if(data == 'd'){
      Serial.print("Gripper (PIN 6) ");
      Serial.println(val4);
      pwm.setPWM(6, 0, val4);
      val4++;
    }

    if(data == 'w'){
      Serial.print("Base Servo 1 (PIN 0)");
      Serial.println(val1);
      pwm.setPWM(0, 0, val1);
      val1--;
    }

    if(data == 'x'){
      Serial.print("Arm Servo back (PIN 2): ");
      Serial.println(val2);
      pwm.setPWM(2, 0, val2);
      val2--;
    }
    
    if(data == 'y'){
       Serial.print("Arm Servo front (PIN 4) ");
      Serial.println(val3);
      pwm.setPWM(4, 0, val3);
      val3--;
    }


    if(data == 'z'){
      Serial.print("Gripper (PIN 6) ");
      Serial.println(val4);
      pwm.setPWM(6, 0, val4);
      val4--;
    }
    if(data == 's'){
      Serial.println("stop");
    }
}


