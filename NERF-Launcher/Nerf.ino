
#include <Servo.h>

Servo myservo;

int pos =90;

//Back position 150
//front position 45

void setup() {

  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  
  myservo.attach(9);
  myservo.write(180);
  delay(500);
}

void loop() {

  if(digitalRead(2) == 0){
    myservo.write(35);
    digitalWrite(13,HIGH);
    delay(250);
    myservo.write(180);
    delay(400);
  }
  

}
