#include <MFRC522.h>
// #include <SoftwareSerial.h>
// #include <Wire.h>
#include <SPI.h> 
// #include <Keypad.h> 
// #include <Servo.h> 
// #include <LiquidCrystal_I2C.h> 

MFRC522 mfrc522 (21, 22);
// LiquidCrystal_I2C lcd(0x27, 16, 2);

// #define Password_Length 10

// char userInput[Password_Length];
// char Master[Password_Length] = "123123123";
// char customKey;
// byte pressCount = 0;
int position = 0;
// const int ButtonPin = 4;
// int buttonState = 0;
// int Doorrelay = 3;
// int RedPinLock = 5;
int BuzzPin = 4;

#define NOTE_G4  392
#define NOTE_C5  523
#define NOTE_G5  784
#define NOTE_C6  1047

int TrueMelody[] = {NOTE_G5, NOTE_C6};
int TrueNoteDurations[] = {12, 8};

int FalseMelody[] = {NOTE_C6, NOTE_G5};
int FalseNoteDurations[] = {12, 8};

#define playTrueMelody() playMelody(TrueMelody, TrueNoteDurations, 2)
#define playFalseMelody() playMelody(FalseMelody, FalseNoteDurations, 2)

// const byte ROWS = 4;
// const byte COLS = 3;

// char twelveKeys[ROWS][COLS] = {
//   {'1', '2', '3'},
//   {'4', '5', '6'},
//   {'7', '8', '9'},
//   {'*', '0', '#'} // * = CLEAR, # = ENTER
// };

// const byte rowPins[ROWS] = { 2, A3, A2, A1 };
// const byte colPins[COLS] = { A0, 6, 7 };   

// Keypad customKeypad = Keypad( makeKeymap(twelveKeys), rowPins, colPins, ROWS, COLS );

String tagUID = "77 DC 76 52";  // String to store UID of tag. 
boolean RFIDMode = true; // boolean to change modes
boolean NormalMode = true; // boolean to change modes

void setup()
{
    // lcd.init();
    // lcd.backlight();
    // lcd.clear();
    Serial.begin(9600);
    Serial.println("Scan your Tag..... ");
    // pinMode(ButtonPin, INPUT);
    // pinMode(RedPinLock, OUTPUT);
    pinMode(BuzzPin, OUTPUT);
    // pinMode(Doorrelay, OUTPUT);
    // LockedPosition(true);
    SPI.begin();      // Init SPI bus
    mfrc522.PCD_Init();   // Init MFRC522
    // lcd.begin(16, 2);
    // lcd.setCursor(0, 0);
    // lcd.print("  WELCOME !!");
    // lcd.setCursor(0, 1);
    // lcd.print(" SCAN THE TAG");
}

// MAIN PROGRAM LOOP
void loop()
{  
  // buttonState = digitalRead(ButtonPin);

  //   if (buttonState == HIGH)
  // {
  //   digitalWrite(Doorrelay, HIGH);
  //   delay(7000);
  //   digitalWrite(Doorrelay, LOW);
    mfrc522.PCD_Init();   // Init MFRC522
  // }
  // else
  // {
  //   digitalWrite(Doorrelay, LOW);
  // }
  
  if ( NormalMode == true ) //System will first look for mode
  {
    if ( RFIDMode == true ) //Function to receive message
    {
      // Look for new cards
      if ( ! mfrc522.PICC_IsNewCardPresent() ) 
      {
        return;
      }
      // Select one of the cards
      if ( ! mfrc522.PICC_ReadCardSerial() )
      {
        return;
      }
      // Reading from the card
      String tag = "" ;
      for ( byte j = 0; j < mfrc522.uid.size; j++)
      {
        tag.concat(String(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " " ));
        tag.concat(String(mfrc522.uid.uidByte[j], HEX));
      }
      tag.toUpperCase();
      // Checking the card
      if (tag.substring(1) == tagUID )
      {
        playTrueMelody();
        Serial.println();
        Serial.println("Tag Matched !!");
        Serial.println("Enter Your Password: ");
        Serial.println(" ");
        // lcd.clear();
        // lcd.setCursor(0,0);
        // lcd.print("Your Tag Matched");
        // lcd.setCursor(0,1);
        // lcd.print(" Access Granted");
        // delay(500);
        // lcd.clear();
        // lcd.setCursor(0,0);
        // lcd.print(" Type Password:");
        RFIDMode = true; // Make RFID mode false
      }
      else
      {
        playFalseMelody();
        Serial.println(" ");
        Serial.println("Wrong Tag Shown");
        Serial.println(" Access Denied");
        tone(BuzzPin, 400, 500);
        // lcd.clear();
        // lcd.setCursor(0,0);
        // lcd.print("  Wrong Tag !!");
        // lcd.setCursor(0,1);
        // lcd.print(" Access Denied");
        // delay(500);
        // lcd.clear();
        // lcd.setCursor(0, 0);
        // lcd.print("   WELCOME !!");
        // lcd.setCursor(0, 1);
        // lcd.print(" SCAN THE TAG");
        RFIDMode = true;
      }
    }
    
    // If RFID mode is false, it will look for keys from keypad

  //   if ( RFIDMode == false )
  //   {
  //     customKey = customKeypad.waitForKey();

  //     if ( customKey != NO_KEY && customKey != '*' && customKey != '#')
  //     {
  //       userInput[pressCount] = customKey;
  //       lcd.setCursor(pressCount + 4, 1);
  //       lcd.print("*");
  //       pressCount++;
  //       tone(BuzzPin, 400, 100);
  //     }
  //     else if ( customKey == '*' )
  //     {
  //       tone(BuzzPin, 400, 100);
  //       lcd.clear();
  //       clearData();
  //       RFIDMode = true;
  //     }
  //     else if ( customKey == '#' )
  //     {
  //       tone(BuzzPin, 400, 100);
  //       lcd.clear();
  //       lcd.setCursor(0,0);
  //       tone(BuzzPin, 800, 1000);
  //       lcd.print("PASSWORD INVALID"); 
  //       delay(2000);
  //       lcd.clear();
  //       clearData();
  //       RFIDMode = true;
  //     }
  //     if ( pressCount == 9 )
  //     {
  //       lcd.clear();
  //       waitHere();
  //     }
  //   }
  }
}

// THIS FUNCTION CHECKS THE PASSWORD STRING
// void waitHere()
// {
//   lcd.setCursor(0,0);
//   lcd.print(" Type Password:");
//   lcd.setCursor(0,1);
//   lcd.print("   *********   ");

//   customKey = customKeypad.waitForKey();  // Program will halt here until a key is pushed

//   if ( customKey != NO_KEY && customKey == '#' ) // The ENTER is pushed and the password goes through the routine
//   {
//     lcd.clear();
//     lcd.setCursor(0,0);

//     if ( !strcmp(userInput, Master))
//     {
//       lcd.setCursor(0,0);
//       lcd.print(" ACCESS GRANTED");
//       lcd.setCursor(0,1);
//       lcd.print("     WELCOME !!");
//       LockedPosition(false);
//       digitalWrite(Doorrelay, HIGH);
//       delay(7000);
//       lcd.clear();
//       clearData();
//       RFIDMode = true;
//     }
//     else if ( strcmp(userInput, Master))
//     {
//       lcd.setCursor(0,0);
//       lcd.print(" ACCESS DENIED");
//       LockedPosition(true);
//       digitalWrite(Doorrelay, LOW);
//       tone(BuzzPin, 800, 2000);
//       delay(500);
//       lcd.clear();
//       clearData();
//       RFIDMode = true;
//     }
//   }
  
//   if (customKey != NO_KEY && customKey == '*')  // If the CLEAR button is pushed, the data is cleared and the program starts over.
//   {
//     lcd.clear();
//     clearData(); 
//     RFIDMode = true;
//   }
//   if (customKey != NO_KEY && customKey == '0')  // This numberical button has no purpose and does nothing when pressed.
//   {
//     waitHere();
//   }
  
//   if (customKey != NO_KEY && customKey == '1')  // This numberical button has no purpose and does nothing when pressed.
//   {
//     waitHere();
//   }

//   if (customKey != NO_KEY && customKey == '2')  // This numberical button has no purpose and does nothing when pressed.
//   {
//     waitHere();
//   }

//   if (customKey != NO_KEY && customKey == '3')  // This numberical button has no purpose and does nothing when pressed.
//   {
//     waitHere();
//   }

//   if (customKey != NO_KEY && customKey == '4')  // This numberical button has no purpose and does nothing when pressed.
//   {
//     waitHere();
//   }

//   if (customKey != NO_KEY && customKey == '5')  // This numberical button has no purpose and does nothing when pressed.
//   {
//     waitHere();
//   }

//   if (customKey != NO_KEY && customKey == '6')  // This numberical button has no purpose and does nothing when pressed.
//   {
//     waitHere();
//   }
//   if (customKey != NO_KEY && customKey == '7')  // This numberical button has no purpose and does nothing when pressed.
//   {
//     waitHere();
//   }

//   if (customKey != NO_KEY && customKey == '8')  // This numberical button has no purpose and does nothing when pressed.
//   {
//     waitHere();
//   }

//   if (customKey != NO_KEY && customKey == '9')  // This numberical button has no purpose and does nothing when pressed.
//   {
//     waitHere();
//   }
// }


// void LockedPosition(int locked)
// {
//   if (locked)
//   {
//     digitalWrite(RedPinLock, HIGH);
//     digitalWrite(Doorrelay, LOW);
//   }
//   else
//   {
//     digitalWrite(RedPinLock, LOW);
//     digitalWrite(Doorrelay, HIGH);
//   }
//   delay(7000);
// }


// CLEARS THE ARRAY DATA, STARTS ALL OVER AGAIN
// void clearData()
// {
//   while ( pressCount != 0 )
//   {
//     userInput[pressCount--] = 0;  // Clears out the user input data, both digit and string data are reset to zero
//   }
//   setup();                         // Returns program back to the beginning
// }

void playMelody(int *melody, int *noteDurations, int notesLength)
{
  pinMode(BuzzPin, OUTPUT);

  for (int thisNote = 0; thisNote < notesLength; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BuzzPin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BuzzPin);
  }
}