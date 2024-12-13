#define PWM1 5
#define m1_ain1 7
#define m1_ain2 8

#define PWM2 6
#define m1_bin1 4
#define m1_bin2 9

#define EN1 A0
#define EN2 A1
char data;


void setup(){
  Serial.begin(9600);
  pinMode(m1_bin1, OUTPUT);
  pinMode(m1_ain1, OUTPUT);
  pinMode(m1_ain2, OUTPUT);
  pinMode(m1_bin2, OUTPUT);

  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  analogWrite(PWM1,255);
  analogWrite(PWM2,255);

  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
}

void loop(){
  while(Serial.available()>0)
  {
    data = Serial.read();
    Serial.println(data);
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
  Serial.println("stop");
}
