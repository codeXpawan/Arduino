#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Motor.h"

int address = 0; // Address in the EEPROM where you want to store the data
byte remaining_pad; 
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int reset_pin = 2;
int pad_pin = 13;
Motor motor1(0,9,10);
Motor motor2(0,11,12);
long time;

void setup()
{
  pinMode(reset_pin,INPUT);
  pinMode(pad_pin,INPUT);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
  remaining_pad = EEPROM.read(address);
  
}

void loop()
{
  Serial.println(digitalRead(pad_pin));
  if(digitalRead(reset_pin) == 1){
    remaining_pad = 50;
    EEPROM.update(address, remaining_pad);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Resetting...");
    delay(1000);
  }
  while(digitalRead(pad_pin) == 1){
    if(remaining_pad > 0){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Please wait...");
      if(remaining_pad%2 == 0){
        time = motor1.rotate(200,pad_pin);
      }
      else{
        time = motor2.rotate(-200, pad_pin);
      }
      remaining_pad -= 1;
      EEPROM.update(address, remaining_pad);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Collect Your PAD");
      delay(1000);
      if(remaining_pad <= 5){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Low Stock...");
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Please Refill...");
        delay(1000);
      }
      // int client_delay = 40; //sec
      // long starting_time = millis();
      // lcd.clear();
      // while((millis()-starting_time)/1000 < client_delay){
      //   lcd.setCursor(0, 0);
      //   lcd.print("Please wait for :");
      //   lcd.setCursor(5,1);
      //   lcd.print(client_delay-(millis()-starting_time)/1000);
      //   lcd.print("sec");
      // }
    }
    else{
      long start_time = millis();
      while(millis() - start_time < 1000){
        lcd.clear();
        delay(50);
        lcd.setCursor(2, 0);
        lcd.print("Please fill up");
        lcd.setCursor(5, 1);
        lcd.print("PADS...");
        delay(200);
      }
      start_time = millis();
      while(millis() - start_time < 1000){
        lcd.clear();
        delay(50);
        lcd.setCursor(2, 0);
        lcd.print("OR RESET IT");
        delay(200);
      }
    }
  }
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Push The Button");
  lcd.setCursor(3, 1);
  lcd.print("Time=");
  lcd.print(time);
  delay(200);
}