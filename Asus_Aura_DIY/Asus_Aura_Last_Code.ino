/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  Note: This only works on Android!
        iOS does not support Bluetooth 2.0 Serial Port Profile
        You may need to pair the module with your smartphone
        via Bluetooth settings. Default pairing password is 1234

  Feel free to apply it to any other example. It's simple!

  NOTE: Bluetooth support is in beta!

  Control a color gradient on NeoPixel strip using a slider!

  For this example you need NeoPixel library:
    https://github.com/adafruit/Adafruit_NeoPixel

  App project setup:
    Slider widget (0...500) on V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <SoftwareSerial.h>
    
#include <BlynkSimpleSerialBLE.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "54a7a860c09541a8b6c44226f66feeac";

SoftwareSerial SerialBLE(10, 11); // RX, TX

#define PIN 8
int rainbow_loop = 0;
int zebra_loop = 0;
int theater_loop=0;
int timer_1=0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(40, PIN, NEO_GRB + NEO_KHZ800);

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

BLYNK_WRITE(V1)
{
  rainbow_loop=1;
  theater_loop=0;
  zebra_loop=0;
}

BLYNK_WRITE(V3)
{
  rainbow_loop=0;
  theater_loop=1;
  zebra_loop=0;
}


BLYNK_WRITE(V2)
{

rainbow_loop=0;
zebra_loop =1;
theater_loop=0;
  
Serial.println("Veri Geldi");
int R = param[0].asInt();
int G = param[1].asInt();
int B = param[2].asInt();
Serial.println(R);
Serial.println(G);
Serial.println(B);

for(int i=0;i<strip.numPixels();i++){
strip.setPixelColor(i, strip.Color(R,G,B));
strip.show();
}

}



void setup()
{
  // Debug console
  Serial.begin(9600);

  SerialBLE.begin(9600);
  Blynk.begin(SerialBLE, auth);

  Serial.println("Waiting for connections...");

  strip.begin();
  strip.show();
}

void loop()
{
  Blynk.run();
  if(rainbow_loop ==1)
  rainbowCycle(10);
  //theaterChaseRainbow(50);
  if(theater_loop ==1)
  theaterChaseRainbow(10);


  
}



void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
         timer_1 = 0;
     timer_1 = millis();
     Blynk.run();
     timer_1 = millis() - timer_1;
     Serial.println(timer_1);
      if(theater_loop ==0)
      return;
      }
      strip.show();
      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
         timer_1 = 0;
     timer_1 = millis();
     Blynk.run();
     timer_1 = millis() - timer_1;
     Serial.println(timer_1);
      if(theater_loop ==0)
      return;
      }
    }
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      
    }
    strip.show();
    timer_1 = 0;
    timer_1 = millis();
    Blynk.run();
    timer_1 = millis() - timer_1;
    Serial.println(timer_1);
    if(rainbow_loop ==0)
    break;
    delay(wait);
  }
}
