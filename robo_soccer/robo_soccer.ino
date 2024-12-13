#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

int forward_left = 16, backward_left = 2, forward_right = 4, backward_right = 12;
int forward_left1 = 5, backward_left1 = 14, forward_right1 = 0, backward_right1 = 13;

const char* SSID = "Engineering Girls";
const char* PSWD = "Girls123";

ESP8266WebServer server(80);

void handleRoot()
{
  server.send(200, "text/html", sendhtml());
}

void move()
{
  if (server.arg("dir") == "F")
  {
    forward();
  }
  if (server.arg("dir") == "FL")
  {
    forwardleft();
  }
  if (server.arg("dir") == "FR")
  {
    forwardright();
  }
  if (server.arg("dir") == "B")
  {
    backward();
  }
  if (server.arg("dir") == "RL")
  {
    reverseleft();
  }
  if (server.arg("dir") == "RR")
  {
    reverseright();
  }
  if (server.arg("dir") == "L")
  {
    left();
  }
  if (server.arg("dir") == "CW")
  {
    clockwise();
  }
  if (server.arg("dir") == "CCW")
  {
    counterclockwise();
  }
  if (server.arg("dir") == "R")
  {
    right();
  }
  if (server.arg("dir") == "S")
  {
    stops();
  }
}
void forward()
{
  digitalWrite(forward_left, HIGH);
  digitalWrite(forward_right, HIGH);
  digitalWrite(backward_left, HIGH);
  digitalWrite(backward_right, HIGH);
  digitalWrite(forward_left1, LOW);
  digitalWrite(forward_right1, LOW);
  digitalWrite(backward_left1, LOW);
  digitalWrite(backward_right1, LOW);
  Serial.println("forward");
}

void backward()
{
  digitalWrite(forward_left, LOW);
  digitalWrite(forward_right, LOW);
  digitalWrite(backward_left, LOW);
  digitalWrite(backward_right, LOW);
  digitalWrite(forward_left1, HIGH);
  digitalWrite(forward_right1, HIGH);
  digitalWrite(backward_left1, HIGH);
  digitalWrite(backward_right1, HIGH);
  Serial.println("backward");
}

void left()
{
  digitalWrite(forward_left, HIGH);
  digitalWrite(forward_right, LOW);
  digitalWrite(backward_left, HIGH);
  digitalWrite(backward_right, LOW);
  digitalWrite(forward_left1, LOW);
  digitalWrite(forward_right1, HIGH);
  digitalWrite(backward_left1, LOW);
  digitalWrite(backward_right1, HIGH);
  Serial.println("left");
}

void right()
{
  digitalWrite(forward_left, LOW);
  digitalWrite(forward_right, HIGH);
  digitalWrite(backward_left, LOW);
  digitalWrite(backward_right, HIGH);
  digitalWrite(forward_left1, HIGH);
  digitalWrite(forward_right1, LOW);
  digitalWrite(backward_left1, HIGH);
  digitalWrite(backward_right1, LOW);
  Serial.println("right");
}

void stops()
{
  digitalWrite(forward_left, LOW);
  digitalWrite(forward_right, LOW);
  digitalWrite(backward_left, LOW);
  digitalWrite(backward_right, LOW);
  digitalWrite(forward_left1, LOW);
  digitalWrite(forward_right1, LOW);
  digitalWrite(backward_left1, LOW);
  digitalWrite(backward_right1, LOW);
  Serial.println("stop");
}

void forwardleft()
{
  digitalWrite(forward_left, LOW);
  digitalWrite(forward_right, HIGH);
  digitalWrite(backward_left, HIGH);
  digitalWrite(backward_right, LOW);
  digitalWrite(forward_left1, LOW);
  digitalWrite(forward_right1, LOW);
  digitalWrite(backward_left1, LOW);
  digitalWrite(backward_right1, LOW);
  Serial.println("forward left");
}

void forwardright()
{
  digitalWrite(forward_left, HIGH);
  digitalWrite(forward_right, LOW);
  digitalWrite(backward_left, LOW);
  digitalWrite(backward_right, HIGH);
  digitalWrite(forward_left1, LOW);
  digitalWrite(forward_right1, LOW);
  digitalWrite(backward_left1, LOW);
  digitalWrite(backward_right1, LOW);
  Serial.println("forward right");
}

void reverseleft()
{
  digitalWrite(forward_left, LOW);
  digitalWrite(forward_right, LOW);
  digitalWrite(backward_left, LOW);
  digitalWrite(backward_right, LOW);
  digitalWrite(forward_left1, HIGH);
  digitalWrite(forward_right1, LOW);
  digitalWrite(backward_left1, LOW);
  digitalWrite(backward_right1, HIGH);
  Serial.println("reverse left");
}

void reverseright()
{
  digitalWrite(forward_left, LOW);
  digitalWrite(forward_right, LOW);
  digitalWrite(backward_left, LOW);
  digitalWrite(backward_right, LOW);
  digitalWrite(forward_left1, LOW);
  digitalWrite(forward_right1, HIGH);
  digitalWrite(backward_left1, HIGH);
  digitalWrite(backward_right1, LOW);
  Serial.println("reverse right");
}

void clockwise()
{
  digitalWrite(forward_left, HIGH);
  digitalWrite(forward_right, LOW);
  digitalWrite(backward_left, HIGH);
  digitalWrite(backward_right, LOW);
  digitalWrite(forward_left1, LOW);
  digitalWrite(forward_right1, HIGH);
  digitalWrite(backward_left1, LOW);
  digitalWrite(backward_right1, HIGH);
  Serial.println("clockwise");
}

void counterclockwise()
{
  digitalWrite(forward_left, LOW);
  digitalWrite(forward_right, HIGH);
  digitalWrite(backward_left, LOW);
  digitalWrite(backward_right, HIGH);
  digitalWrite(forward_left1, HIGH);
  digitalWrite(forward_right1, LOW);
  digitalWrite(backward_left1, HIGH);
  digitalWrite(backward_right1, LOW);
  Serial.println("counterclockwise");
}

String sendhtml()
{
  String html = "<!DOCTYPE html> <html> <body> <h1>Ready to Drive</h1></body> </html>";
  return html;
}

void setup()
{
  Serial.begin(115200);

  // Connect to WiFi
  if (WiFi.softAP(SSID, PSWD))
  {
    Serial.println("WiFi AP started");
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("Access Point IP: ");
    Serial.println(myIP);
  }
  else
  {
    Serial.println("Error starting WiFi AP!");}
  pinMode(forward_left, OUTPUT);
  pinMode(forward_right, OUTPUT);
  pinMode(backward_left, OUTPUT);
  pinMode(backward_right, OUTPUT);
  pinMode(forward_left1, OUTPUT);
  pinMode(forward_right1, OUTPUT);
  pinMode(backward_left1, OUTPUT);
  pinMode(backward_right1, OUTPUT);
  digitalWrite(forward_left, LOW);
  digitalWrite(forward_right, LOW);
  digitalWrite(backward_left, LOW);
  digitalWrite(backward_right, LOW);
  digitalWrite(forward_left1, LOW);
  digitalWrite(forward_right1, LOW);
  digitalWrite(backward_left1, LOW);
  digitalWrite(backward_right1, LOW);
}

void loop()
{
  server.handleClient();
}

