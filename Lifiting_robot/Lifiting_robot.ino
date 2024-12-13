// #define m1_en1 A0
// #define m1_en2 A1
// #define m2_en1 A3
// #define m2_en2 A4
#define m1_ain1 13
#define m1_ain2 2
#define m1_bin1 3
#define m1_bin2 4
#define m1_pwma 5
#define m1_pwmb 6
#define m2_ain1 7
#define m2_ain2 8
#define m2_bin1 11
#define m2_bin2 12
#define m2_pwma 9
#define m2_pwmb 10
#define m3_relay1 A2
#define m3_relay2 A5


char data;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  // pinMode(m1_en1, OUTPUT);
  // pinMode(m1_en2, OUTPUT);
  pinMode(m1_ain1, OUTPUT);
  pinMode(m1_ain2, OUTPUT);
  pinMode(m1_bin1, OUTPUT);
  pinMode(m1_bin2, OUTPUT);
  pinMode(m1_pwma, OUTPUT);
  pinMode(m1_pwmb, OUTPUT);
  // pinMode(m2_en1, OUTPUT);
  // pinMode(m2_en2, OUTPUT);
  pinMode(m2_ain1, OUTPUT);
  pinMode(m2_ain2, OUTPUT);
  pinMode(m2_bin1, OUTPUT);
  pinMode(m2_bin2, OUTPUT);
  pinMode(m2_pwma, OUTPUT);
  pinMode(m2_pwmb, OUTPUT);
  digitalWrite(m3_relay1, OUTPUT);
  digitalWrite(m3_relay2, OUTPUT);
  // digitalWrite(m1_en1, HIGH);
  // digitalWrite(m1_en2, HIGH);
  // digitalWrite(m2_en1, HIGH);
  // digitalWrite(m2_en2, HIGH);
  digitalWrite(m1_pwma, HIGH);
  digitalWrite(m1_pwmb, HIGH);
  analogWrite(m2_pwma, 240);
  analogWrite(m2_pwmb, 253);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0)
  {
    data = Serial.read();
    if(data == 'F')
    {
      forward();
    }
    if(data == 'B')
    {
      backward();
    }
    if(data == 'L')
    {
      left();
    }
    if(data == 'R')
    {
      right();
    }
    if(data == 'S')
    {
      stopp();
    }
    if(data == 'U')
    {
      uplift();
    }
    if(data == 'D')
    {
      downlift();
    }
    if(data == 'C')
    {
      clockwise();
    }
    if(data == 'A')
    {
      anticlockwise();
    }
  }
}

void forward()
{
  digitalWrite(m1_ain1, LOW);
  digitalWrite(m1_bin1, LOW);
  digitalWrite(m1_ain2, HIGH);
  digitalWrite(m1_bin2, HIGH);
  Serial.println("forward");
}

void backward()
{
  digitalWrite(m1_ain1, HIGH);
  digitalWrite(m1_bin1, HIGH);
  digitalWrite(m1_ain2, LOW);
  digitalWrite(m1_bin2, LOW);
  Serial.println("backward");
}

void left()
{
  digitalWrite(m1_ain1, LOW);
  digitalWrite(m1_bin1, HIGH);
  digitalWrite(m1_ain2, HIGH);
  digitalWrite(m1_bin2, LOW);
  Serial.println("left");
}

void right()
{
  digitalWrite(m1_ain1, HIGH);
  digitalWrite(m1_bin1, LOW);
  digitalWrite(m1_ain2, LOW);
  digitalWrite(m1_bin2, HIGH);
  Serial.println("right");
}

void stopp()
{
  digitalWrite(m1_ain1, LOW);
  digitalWrite(m1_bin1, LOW);
  digitalWrite(m1_ain2, LOW);
  digitalWrite(m1_bin2, LOW);
  digitalWrite(m2_ain1, LOW);
  digitalWrite(m2_bin1, LOW);
  digitalWrite(m2_ain2, LOW);
  digitalWrite(m2_bin2, LOW);
  digitalWrite(m3_relay1, LOW);
  digitalWrite(m3_relay2, LOW);
  Serial.println("stop");
}

void uplift()
{
  digitalWrite(m2_ain1, LOW);
  digitalWrite(m2_bin1, LOW);
  digitalWrite(m2_ain2, HIGH);
  digitalWrite(m2_bin2, HIGH);
  Serial.println("uplift");
}

void downlift()
{
  digitalWrite(m2_ain1, HIGH);
  digitalWrite(m2_bin1, HIGH);
  digitalWrite(m2_ain2, LOW);
  digitalWrite(m2_bin2, LOW);
  Serial.println("downlift");
}
void clockwise()
{
  digitalWrite(m3_relay1, HIGH);
  digitalWrite(m3_relay2, LOW);
  Serial.println("clockwise");
}

void anticlockwise()
{
  digitalWrite(m3_relay1, LOW);
  digitalWrite(m3_relay2, HIGH);
  Serial.println("anticlockwise");
}