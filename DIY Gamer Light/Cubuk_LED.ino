#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Adafruit_NeoPixel.h>

char auth[] = "token"; // blynk token'ı buraya yazmanız gerekiyor
char ssid[] = "ssid"; // ESP8266'nın bağlanabilmesi için WiFi adı buraya yazılacak.
char pass[] = "password"; // WiFi şifresi buraya yazılacak

int rainbow_loop = 0;
int zebra_loop = 0;
int theater_loop=0;
int timer_1=0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(108,2, NEO_GRB + NEO_KHZ800);

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
 
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

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
