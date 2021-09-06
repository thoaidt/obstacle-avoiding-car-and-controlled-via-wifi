#Author Đào Trọng Thoại, facebook: fb.com/daotrongthoai
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#define goLeftFront 5      //in1 - d1 - 5
#define goLeftBack 4      //in2 - d2 - 4
#define goRightFront 0     //in3 - d3 - 0
#define goRightBack 2      //in4 - d4 - 2

#define trig_pin 14   //d5 - 14   
#define echo_pin 12   //d6 - 12
#define servo_pin 13   //d7 - 13
#include "index.h" // Giao diện web đc luu cùng thư mục với tệp .ino


Servo myServo; 
int flag = 0;
int speedCar = 400;

ESP8266WebServer server(80);
const char* ssid = "thoaib1609610";
const char* password = "thoaideptrai";
IPAddress staticIP(192,168,43,210);
IPAddress gateway(192,168,43,1);
IPAddress subnet(255,255,255,0);


String webPage = mainPage;

void setup(){
    pinMode(goLeftFront, OUTPUT);
    pinMode(goLeftBack, OUTPUT);
    pinMode(goRightFront, OUTPUT);
    pinMode(goRightBack, OUTPUT);
    pinMode(trig_pin, OUTPUT);
    pinMode(echo_pin, INPUT);
    delay(1000);
    
    myServo.attach(servo_pin); 
    myServo.write(90);
    
    Serial.begin(9600);
    WiFi.begin(ssid, password);
    WiFi.config(staticIP, gateway, subnet);
    
    while(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }
 
    server.on("/", [](){
        server.send(200, "text/html", webPage);
        flag = 0;
        Serial.println(flag);
    });
    server.on("/TIEN", [](){
        server.send(200, "text/html", webPage);
        flag = 1;
        Serial.println(flag);
    });
    server.on("/LUI", [](){
        server.send(200, "text/html", webPage);
        flag = 2;
        Serial.println(flag);
    });
    server.on("/TRAI", [](){
        server.send(200, "text/html", webPage);
        flag = 3;
        Serial.println(flag);
    });
    server.on("/PHAI", [](){
        server.send(200, "text/html", webPage);
        flag = 4;
        Serial.println(flag);
    });
    server.on("/AUTO", [](){
        server.send(200, "text/html", webPage);
        flag = 5;
        speedCar = 400;
        Serial.println(flag);
    });
    server.on("/STOP", [](){
        server.send(200, "text/html", webPage);
        flag = 0;
        myServo.write(90);
        Serial.println(flag);
    });
    
    server.on("/MOT", [](){
        server.send(200, "text/html", webPage);
        speedCar = 400;
    });
    server.on("/HAI", [](){
        server.send(200, "text/html", webPage);
        speedCar = 720;
    });
    server.on("/BA", [](){
        server.send(200, "text/html", webPage);
        speedCar = 1023;
    });
    
    server.begin();
    Serial.println("HTTP server started");
}

void loop(){
    if(flag == 0){
        Stop();
        server.handleClient();
    }
    if(flag == 1){
        Tien();
        server.handleClient();
    }
    if(flag == 2){
        Lui();
        server.handleClient();
    }
    if(flag == 3){
        Trai();
        server.handleClient();
    }
    if(flag == 4){
        Phai();
        server.handleClient();
    }
    if(flag == 5){
        Auto();
        server.handleClient();
    }
}

void Tien(){
    digitalWrite(goLeftFront, HIGH);
    analogWrite(goLeftBack, 1023 - speedCar);
    
    digitalWrite(goRightFront, HIGH);
    analogWrite(goRightBack, 1023 - speedCar);
}

void Lui(){
    digitalWrite(goLeftFront, LOW);
    analogWrite(goLeftBack, speedCar);
    
    digitalWrite(goRightFront, LOW);
    analogWrite(goRightBack, speedCar);
}

void Phai(){
    digitalWrite(goLeftFront, LOW);
    analogWrite(goLeftBack, speedCar);
    
    digitalWrite(goRightFront, HIGH);
    analogWrite(goRightBack, 1023 - speedCar);
}

void Trai(){
    digitalWrite(goLeftFront, HIGH);
    analogWrite(goLeftBack, 1023 - speedCar);
    
    digitalWrite(goRightFront, LOW);
    analogWrite(goRightBack, speedCar);
}

void Stop(){
    digitalWrite(goLeftFront, LOW);
    digitalWrite(goLeftBack, LOW);
    
    digitalWrite(goRightFront, LOW);
    digitalWrite(goRightBack, LOW);
}

void Auto(){
  for(int i = 30; i <= 180; i+= 30){
    myServo.write(i);
    delay(100);
    long distance = getDistance();
    if(distance < 25.0){
      long distanceRight = 0;
      long distanceLeft = 0;
      Stop();
      delay(300);
      distanceRight = lookRight();
      delay(300);
      distanceLeft = lookLeft();
      delay(300);
      if(distance >= distanceLeft){
        Phai();
        int rdMS = returnMs();
        delay(rdMS);
      }else{
        Trai();
        int rdMS = returnMs();
        delay(rdMS);
      }
      break;
    }else Tien();
  }

  for(int i = 180; i >= 30; i -= 30){
    myServo.write(i);
    delay(100);
    long distance = getDistance();
    if(distance < 25.0){
      long distanceRight = 0;
      long distanceLeft = 0;
      Stop();
      delay(300);
      distanceRight = lookRight();
      delay(300);
      distanceLeft = lookLeft();
      delay(300);
      if(distance >= distanceLeft){
        Phai();
        int rdMS = returnMs();
        delay(rdMS);
      }else{
        Trai();
        int rdMS = returnMs();
        delay(rdMS);
      }
      break;
    }else Tien();
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
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
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
 
