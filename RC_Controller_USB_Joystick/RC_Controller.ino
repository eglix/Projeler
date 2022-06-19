#include "Joystick.h"

#define ch1 5
#define ch2 6
#define ch3 7
#define ch4 8

Joystick_ Joystick;

int ch1_value, ch2_value, ch3_value, ch4_value;

void setup() {
  
  //Serial.begin(9600);
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);
  pinMode(ch3, INPUT);
  pinMode(ch4, INPUT);

  Joystick.setThrottleRange(0, 255);
  Joystick.setXAxisRange(0, 255);
  Joystick.setYAxisRange(0, 255);
  Joystick.setZAxisRange(0, 255);
  Joystick.setRxAxisRange(0,255);

  Joystick.begin();
}

void loop() {

  ch1_value = pulseIn(ch1,HIGH);
  ch2_value = pulseIn(ch2,HIGH);
  ch3_value = pulseIn(ch3,HIGH);
  ch4_value = pulseIn(ch4,HIGH);


  Joystick.setXAxis(map(ch1_value, 1000,2000, 0,255));
  Joystick.setThrottle(map(ch2_value, 1500,2000, 0,255));
  Joystick.setYAxis(map(ch3_value, 1000,2000, 0,255));
  Joystick.setZAxis(map(ch4_value, 1000,2000, 0,255));
  Joystick.setRxAxis(map(ch2_value,1450,1000,0,255));
  delay(5);

//  Serial.print(ch1_value);
//  Serial.print(", ");
//  Serial.print(ch2_value);
//  Serial.print(", ");
//  Serial.print(ch3_value);
//  Serial.print(", ");
//  Serial.println(ch4_value);
  
  

}
