#include <Adafruit_NeoPixel.h>

#define LED_PIN    10
#define LED_COUNT 200

volatile boolean buttonState = false;
int counter = 0;
int timer_1 = 0;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), buttonCounter, FALLING);

  strip.begin();
  strip.show();
  strip.setBrightness(20);
  delay(100);
  counter = 0;
}

void loop() {
  
  Serial.println(counter);
  switch (counter) {
    case 0:
      justWhite();
      
      break;
    case 1:
      // Serial.println("2.secenek");
      colorWipe(strip.Color(148, 9, 150), 0, 0);
      colorWipe(strip.Color(193, 108, 230), 1, 0);
      colorWipe(strip.Color(0, 63, 222), 2, 0);
      delay(1000);
      strip.clear();
      break;
    case 2:
      // Serial.println("3.secenek");
      rainbowCycle(10);
      break;
    case 3:
      colorWipe(strip.Color(64, 224, 208), 0, 0);
      colorWipe(strip.Color(16, 56, 52), 1, 0);
      colorWipe(strip.Color(4, 9, 8), 2, 0);
      delay(1000);
      strip.clear();
      break;
    case 4:
      break;

    case 5:
      thunderEffect();
      break;
  }
}


void justWhite(){
  strip.setBrightness(255);
  for(int i=0;i<LED_COUNT;i++){
  strip.setPixelColor(i, strip.Color(150, 150, 150));
  strip.show();
  delay(20);
  }
  
}

void thunderEffect () {
  
  stripColor(randomStart(), randomEnd(), 0, strip.Color(0, 0, 0), 0, 1500);
  stripColor(randomStart(), randomEnd(), 125, strip.Color(255, 255, 255), 20, 50);
  stripColor(randomStart(), randomEnd(), 255, strip.Color(255, 255, 255), 0, 20);
  fadeEffect(0, 20);
  stripColor(randomStart(), randomEnd(), 255, strip.Color(255, 255, 255), 0 , 20);
  stripColor(randomStart(), randomEnd(), 0, strip.Color(0, 0, 0), 0, 10);
  stripColor(randomStart(), randomEnd(), 255, strip.Color(255, 255, 255), 0, 10);
  fadeEffect(0, 50);
  stripColor(randomStart(), randomEnd(), 255, strip.Color(255, 255, 255), 0, 20);
  fadeEffect(0, 1500);
  
}

void stripColor(int startPixel, int endPixel, int brightness, uint32_t color, int stripEffect, int delayTime) {  //stripEffect ledin yılan gidişi için gerekli delay
                                                                                                                 // delayTime normal delay sadece ortada kalabalık olmasın diye fonksiyona ekledim.
  for (int i = startPixel; i <= endPixel; i ++) {
    strip.setBrightness(brightness);
    strip.setPixelColor(i, color);
    strip.show();
    if (buttonState){
      buttonState = false;
      break;
      
    }
      
    delay(stripEffect);
  }
  delay(delayTime);
}

void fadeEffect(int fadeSpeed, int delayTime) {

  for (int i = 255; i >= 0; i --) {
    strip.setBrightness(i);
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
    delay(fadeSpeed);
  }
  delay(delayTime);
  
}

void colorWipe(uint32_t color, int startLed, int wait) {
  for (int i = startLed; i <= strip.numPixels(); i += 3) {
    strip.setBrightness(255);
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

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

void rainbowCycle(uint8_t wait) {
  
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));

    }
    strip.show();
    timer_1 = 0;
    timer_1 = millis();
    timer_1 = millis() - timer_1;
    //Serial.println(timer_1);
    if (buttonState){
      buttonState = false;
      break;
      
    }
    delay(wait);
  }
  
}

int randomStart () {
  int stripStart = random(0, LED_COUNT / random(1, 5));
  //Serial.println(stripStart);
  return (stripStart);
}

int randomEnd () {
  int stripEnd = random(LED_COUNT / random(1, 5), LED_COUNT);
  //Serial.println(stripEnd);
  return (stripEnd);
}

void buttonCounter() {
  noInterrupts();
  delay(2000);
  counter++;
  if (counter > 5) counter = 0;
  buttonState = true;
  
  Serial.println(counter);
  interrupts();
}
