
#include "Keyboard.h"

// set pin numbers for the five buttons:

void setup() { // initialize the buttons' inputs:
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);

  Keyboard.begin();
}

void loop() {
 
  if (digitalRead(2) == LOW) {
    Keyboard.write('e');
    delay(100);
    while(digitalRead(2)== LOW);
  }  
  if (digitalRead(3) == LOW) {
    Keyboard.write('r');
    delay(100);
    while(digitalRead(3)== LOW);
  }
  if (digitalRead(4) == LOW) {
    Keyboard.write('a');
    delay(100);
    while(digitalRead(4)== LOW);
  }
  if (digitalRead(5) == LOW) {
    Keyboard.write('q');
    delay(100);
    while(digitalRead(5)== LOW);
  }
  if (digitalRead(6) == LOW) {
    Keyboard.write('w');
    delay(100);
    while(digitalRead(6)== LOW);
  }
  if (digitalRead(7) == LOW) {
    Keyboard.write('d');
    delay(100);
    while(digitalRead(7)== LOW);
  }

}
