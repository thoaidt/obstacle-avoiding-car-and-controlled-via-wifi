#include <SoftwareSerial.h>

#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4

SoftwareSerial mySerial(10, 11);
String readString;

int flag = 0;
int stopCar = 0;
int goAhead = 88;
int goBack = 22;
int turnLeft = 44;
int turnRight = 66;
int customSpeed = 85;
int minSpeed = 111;
int mediumSpeed = 555;
int maxSpeed = 999;

void setup(){
  Serial.begin(9600);
  Serial.println("Da san sang");
  mySerial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void motorRight_Stop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void motorLeft_Stop(){
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void motorRight_goAhead(int speed){
  digitalWrite(IN1, HIGH);
  analogWrite(IN2, 255 - speed);
}

void motorRight_goBack(int speed){
  digitalWrite(IN1, LOW);
  analogWrite(IN2, speed);
}

void motorLeft_goAhead(int speed){
  analogWrite(IN3, 255 - speed);
  digitalWrite(IN4, HIGH);
}

void motorLeft_goBack(int speed){
  analogWrite(IN3, speed);
  digitalWrite(IN4, LOW);
}

void stopCarCM(){
  motorRight_Stop();
  motorLeft_Stop();
}

void goAheadCM(int speed){
  motorRight_goAhead(speed);
  motorLeft_goAhead(speed);
}

void goBackCM(int speed){
  motorRight_goBack(speed);
  motorLeft_goBack(speed);
}

void turnLeftCM(int speed){
  motorRight_goAhead(speed);
  motorLeft_goBack(speed);
}

void turnRightCM(int speed){
  motorRight_goBack(speed);
  motorLeft_goAhead(speed);
}

void receiveCMEsp8266(){
  if(mySerial.available() > 0){
    while(mySerial.available() > 0){
      char CM = mySerial.read();
      readString += CM;
      delay(3);
    }
    Serial.println();
    Serial.println(readString);
  }

  if(readString.length() > 0){
    if(readString.toInt() == stopCar){
      flag = 0;
      stopCarCM();
    }else if(readString.toInt() == goAhead){
      flag = 1;
      goAheadCM(customSpeed);
    }else if(readString.toInt() == goBack){
      flag = 2;
      goBackCM(customSpeed);
    }else if(readString.toInt() == turnLeft){
      flag = 3;
      turnLeftCM(customSpeed);
    }else if(readString.toInt() == turnRight){
      flag = 4;
      turnRightCM(customSpeed);
    }else if(readString.toInt() == minSpeed){
      customSpeed = 85;
    }else if(readString.toInt() == mediumSpeed){
      customSpeed = 170;
    }else if(readString.toInt() == maxSpeed){
      customSpeed = 255;
    }
    readString = "";
  }
}

void loop(){
  receiveCMEsp8266();
  if(flag == 0){
    stopCarCM();
    receiveCMEsp8266();
  }else if(flag == 1){
    goAheadCM(customSpeed);
    receiveCMEsp8266();
  }else if(flag == 2){
    goBackCM(customSpeed);
    receiveCMEsp8266();
  }else if(flag == 3){
    turnLeftCM(customSpeed);
    receiveCMEsp8266();
  }else if(flag == 4){
    turnRightCM(customSpeed);
    receiveCMEsp8266();
  }
}
