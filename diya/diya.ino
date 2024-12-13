int relay = 4;
char data;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    data = Serial.read();
    if(data == 'A')
    {
      digitalWrite(relay, LOW);
    }
    if(data == 'S')
    {
      digitalWrite(relay, HIGH);
    }
    Serial.println(data);
  }
}
