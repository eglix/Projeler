
#define RELAY 10
#define DELAY 50 // motor çalışma süresi

const int LEDs[7] = {3,4,5,6,7,8,9};
unsigned int counter = 0;


void setup() {
  Serial.begin(9600);

  for(int i=0; i<7; i++){
    pinMode(LEDs[i], OUTPUT);
  }

  pinMode(RELAY,OUTPUT);

}

void loop() {
  digitalWrite(RELAY,LOW);
  LEDs_On(counter);

}

void serialEvent(){
  char inChar = (char)Serial.read(); //Porttan gelen veriyi oku
  if (inChar == '1')                 //Mouse'a tıklandıysa
  {
    digitalWrite(RELAY, HIGH);
    delay(DELAY);                   //Motor çalışma süresi
    counter++;
  }
  else if (inChar == '2')           //Mouse'a tıklanmıyorsa
  {
    if (counter >0) counter--;
  }
}

void LEDs_On(int c)
{
  if (c>6)                          //Tüm LED'led   *******
  {
    for(int i=0;i<7;i++)
      digitalWrite(LEDs[i],HIGH);
  }
  else if (c>4)                     //5 LED         -*****-
  {
    digitalWrite(LEDs[0], LOW);
    digitalWrite(LEDs[6], LOW);
    for(int i=0;i<5;i++)
      digitalWrite(LEDs[i+1], HIGH);
  }
  else if (c>2)                     //3 LED          --***--
  {
    for(int i=0;i<7;i++) 
      digitalWrite(LEDs[i],LOW);

    digitalWrite(LEDs[2],HIGH);
    digitalWrite(LEDs[3],HIGH);
    digitalWrite(LEDs[4],HIGH);
  }
  else if (c>0)                      //1 LED          ---*---
  {
    for(int i=0; i<7; i++)         
      digitalWrite(LEDs[i],LOW);

    digitalWrite(LEDs[3], HIGH);
  }
  else
  {
    for(int i=0; i<7; i++)          // LED'ler Kapalı -------
      digitalWrite(LEDs[i],LOW);
  }
}
