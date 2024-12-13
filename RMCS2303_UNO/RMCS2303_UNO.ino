/*
Connections of Drive and Arduino
Serial Port 0 is not used to connect to drive because its connected to USB-Serial and used to show information on console.

For Arduino Uno Software serial needs to be used as there is only one hardware serial port and its connected to USB-Serial. 
   Drive to Arduino UNO/Nano connections
   GND         -      GND
   RXD         -      D3
   TXD         -      D2

For arduino mega and other arduinos with multiple hardware serial port, any port other than 0 can be selected to connect the drive.

   Drive to Arduino Mega2560 connections
   GND         -      GND
   RXD         -      Tx1/Tx2/Tx3
   TXD         -      Rx1/Rx2/Rx3
   
*	This mode can be used when multiple motors are to be used to run at exactly the same RPM and same torque even though the voltage supply might be different.
*	Also in this mode the direction of the motor can be controlled digitally via modbus ASCII commands to run the dc servo motor in both directions

* For more information see : https://robokits.co.in/motor-drives-drivers/encoder-dc-servo/rhino-dc-servo-driver-50w-compatible-with-modbus-uart-ascii-for-encoder-dc-servo-motor


*/

#include<RMCS2303drive.h>

RMCS2303 rmcs;                    //object for class RMCS2303

SoftwareSerial myserial(2,3);     //Software Serial port For Arduino Uno. Comment out if using Mega.

//parameter Settings "Refer datasheet for details"
byte slave_id=0b111;
int INP_CONTROL_MODE=260;           
int PP_gain=32;
int PI_gain=20;
int VF_gain=32;
int LPR=260;
int acceleration=50;
int speed=90;


long int Current_position;
long int Current_Speed;

void setup()
{
   rmcs.Serial_selection(1);       //Serial port selection:0-Hardware serial,1-Software serial
   rmcs.Serial0(9600);             //Set baudrate for usb serial to monitor data on serial monitor
   Serial.println("RMCS-2303 Speed control mode demo\r\n\r\n");

   //rmcs.begin(&Serial1,9600);    //Uncomment if using hardware serial port for mega2560:Serial1,Serial2,Serial3 and set baudrate. Comment this line if Software serial port is in use
   rmcs.begin(&myserial,9600);     //Uncomment if using software serial port. Comment this line if using hardware serial.
   rmcs.WRITE_PARAMETER(slave_id,INP_CONTROL_MODE,PP_gain,PI_gain,VF_gain,LPR,acceleration,speed);    //Uncomment to write parameters to drive. Comment to ignore.
   rmcs.READ_PARAMETER(slave_id);
   rmcs.SET_HOME(slave_id);
}

void loop(void)
{
  if(Serial.available()>0){
    char data = Serial.read();
    if(data == 'F'){
      // Serial.println("Forward");
      rmcs.Enable_Digital_Mode(slave_id,0);        //To enable motor in digital speed control mode. 0-fwd,1-reverse direction. 
    }
    if(data == 'B'){
      // Serial.println("Backward");
      rmcs.Enable_Digital_Mode(slave_id,1);           //To enable motor in digital speed control mode. 0-fwd,1-reverse direction. 
    }
    if(data == 'V'){
      int speed = Serial.parseInt();
      // Serial.print("Sending speed command - ");
      // Serial.print(speed);
      // Serial.println("RPM");
      rmcs.Speed(slave_id,speed);                   //Set speed within range of 0-65535 or 0-(maximum speed of base motor)
      // delay(1000);
    }
    if(data == 'S'){
      // Serial.println("Break Motor");
      rmcs.Brake_Motor(slave_id,0);                 //Brake motor. 0-fwd,1-reverse direction. 
      rmcs.Brake_Motor(slave_id,1);
    }
    if(data == 'P'){
      int count = Serial.parseInt();
      rmcs.Absolute_position(slave_id,count );
      while(1)       //Keep reading positions. Exit when reached.
   {
      Current_position=rmcs.Position_Feedback(slave_id); //Read current encoder position 
      Current_Speed=rmcs.Speed_Feedback(slave_id);       //Read current speed
      Serial.print("Position Feedback :\t");
      Serial.print(Current_position);
      Serial.print("\t\tSpeed Feedback :\t");
      Serial.println(Current_Speed);

      delay(100);
      if(Current_position==count)
      {
         Serial.println("Position reached.");
         break;
      }
   }
      rmcs.Disable_Position_Mode(slave_id);
    }
  }
   
   Current_Speed=rmcs.Speed_Feedback(slave_id); 
   Serial.print("Current Speed feedback : ");
   Serial.println(Current_Speed);
   Current_position = rmcs.Position_Feedback(slave_id);
   Serial.print("Current Position feedback : ");
   Serial.println(Current_position);

   
  //  rmcs.READ_PARAMETER(slave_id);
}
