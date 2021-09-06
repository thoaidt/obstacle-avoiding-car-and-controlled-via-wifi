#include  <ESP8266WiFi.h>
#include  <ESP8266WebServer.h>
#include "index.h"

ESP8266WebServer server(80);
String webPage = mainPage;
const char* ssid = "TieuThon";
const char* password = "thoaideptrai";

IPAddress staticIP(192,168,43,230);
IPAddress gateway(192,168,43,1);
IPAddress subnet(255,255,255,0);

#include  <Servo.h>
#define SERVO_PIN 2
Servo myServo;

#define TRIG_PIN 5
#define ECHO_PIN 4

int flag = 0;

void setup(){
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(90);
  
  Serial.begin(9600);
  delay(100);

  Serial.println();
  Serial.println();

  WiFi.begin(ssid, password);
  WiFi.config(staticIP, gateway, subnet);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  server.on("/", [](){
    server.send(200, "text/html", webPage);
    Serial.println("0");
  });
  server.on("/up", [](){
    server.send(200, "text/html", webPage);
    Serial.println("88");
  });
  server.on("/down", [](){
    server.send(200, "text/html", webPage);
    Serial.println("22");
  });
  server.on("/left", [](){
    server.send(200, "text/html", webPage);
    Serial.println("44");
  });
  server.on("/right", [](){
    server.send(200, "text/html", webPage);
    Serial.println("66");
  });
  server.on("/onAuto", [](){
    server.send(200, "text/html", webPage);
    Serial.println("111");
    flag = 1;
  });
  server.on("/offAuto", [](){
    server.send(200, "text/html", webPage);
    flag = 2;
    Serial.println("0");
  });
  server.on("/minSpeed", [](){
    server.send(200, "text/html", webPage);
    Serial.println("111");
  });
  server.on("/mediumSpeed", [](){
    server.send(200, "text/html", webPage);
    Serial.println("555");
  });
  server.on("/maxSpeed", [](){
    server.send(200, "text/html", webPage);
    Serial.println("999");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void controlServo(){
  for(int i = 30; i <= 180; i+= 30){
    myServo.write(i);
    delay(100);
    long distance = getDistance();
    if(distance < 25.0){
      long distanceRight = 0;
      long distanceLeft = 0;
      Serial.println("0");
      delay(300);
      distanceRight = lookRight();
      delay(300);
      distanceLeft = lookLeft();
      delay(300);
      if(distance >= distanceLeft){
        Serial.println("66");
        int rdMS = returnMs();
        delay(rdMS);
      }else{
        Serial.println("44");
        int rdMS = returnMs();
        delay(rdMS);
      }
      break;
    }else Serial.println("88");
  }

  for(int i = 180; i >= 30; i -= 30){
    myServo.write(i);
    delay(100);
    long distance = getDistance();
    if(distance < 25.0){
      long distanceRight = 0;
      long distanceLeft = 0;
      Serial.println("0");
      delay(300);
      distanceRight = lookRight();
      delay(300);
      distanceLeft = lookLeft();
      delay(300);
      if(distance >= distanceLeft){
        Serial.println("66");
        int rdMS = returnMs();
        delay(rdMS);
      }else{
        Serial.println("44");
        int rdMS = returnMs();
        delay(rdMS);
      }
      break;
    }else Serial.println("88");
  }
}

long lookLeft(){  
  myServo.write(10);
  delay(500);
  long distance = getDistance();
  delay(100);
  myServo.write(90);
  return distance;
}

long lookRight(){
  myServo.write(170);
  delay(500);
  long distance = getDistance();
  delay(100);
  myServo.write(90);
  return distance;
}

long getDistance(){
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;

  server.handleClient();
  return distance;
}

int randomMS(){
  int minR = 3;
  int maxR = 11;
  return minR + rand() % (maxR + 1 - minR);
}

int returnMs(){
  srand((int)time(0));
  int r = randomMS();
  
  if(r == 3){return 300;}
  else if(r == 4){return 400;}
  else if(r == 5){return 500;}
  else if(r == 6){return 600;}
  else if(r == 7){return 700;}
  else if(r == 8){return 800;}
  else if(r == 9){return 900;}
  else if(r == 10){return 1000;}
  else if(r == 11){return 1100;}
}

void loop(){
  if(flag == 1){
    controlServo();
  }else if(flag == 2){
    delay(300);
    Serial.println("0");
    myServo.write(90);
    flag = 0;
  }else server.handleClient();
}
