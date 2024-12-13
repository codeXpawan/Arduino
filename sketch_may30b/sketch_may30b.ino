
int dpdtPin1=8;
int dpdtPin2=7;
int stopSwitch1=6;
int stopSwitch2=5;
int relayPin1=4;
int relayPin2=3;

int a,b,c,d,e,f;

void setup()
{
  pinMode(dpdtPin1,INPUT);
  pinMode(dpdtPin2,INPUT);
  pinMode(stopSwitch1,INPUT);
  pinMode(stopSwitch2,INPUT);
  pinMode(relayPin1,OUTPUT);
  pinMode(relayPin2,OUTPUT);
}

void loop()
{
  int a=digitalRead(dpdtPin1);
  int b=digitalRead(dpdtPin2);
  int c=digitalRead(stopSwitch1);
  int d=digitalRead(stopSwitch2);
    
  if(a==HIGH)
{
  digitalWrite(relayPin1,HIGH); 
  digitalWrite(relayPin2,LOW);
  
  if(c==HIGH)
  {
  digitalWrite(relayPin1,LOW);
  digitalWrite(relayPin2,LOW);
  }
}
  if(b==HIGH)
  {
    digitalWrite(relayPin1,HIGH);
    digitalWrite(relayPin2,LOW);
  
  if(d==HIGH)
  {
    digitalWrite(relayPin1,LOW);
    digitalWrite(relayPin2,LOW); 
  } 
 }   
}




