#define cold_dir 13
#define hot_dir 12
#define cold_en 10
#define hot_en 11

#define pwm_a A0
#define pwm_b A1

#define cold_hot_a A5
#define cold_hot_b A4


int led_temp=0;
int last_temp=0;
int current_temp=0;
int led_pwm=0;
int last_pwm=0;
int current_pwm=0;

float cold_pwm=0;
float hot_pwm=0;

int pwm_counter = 0;
int pwmState;
int pwmLastState;

int temp_counter = 0;
int cold_hotState;
int cold_hotLastState;



void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

void setup() {
  pinMode(cold_dir,OUTPUT);
  pinMode(cold_en,OUTPUT);
  pinMode(hot_dir,OUTPUT);
  pinMode(hot_en,OUTPUT);
  pinMode(pwm_a,INPUT);
  pinMode(pwm_b,INPUT);
  pinMode(cold_hot_a,INPUT);
  pinMode(cold_hot_b,INPUT);

  digitalWrite(cold_dir,LOW);
  digitalWrite(hot_dir,HIGH);

  setPwmFrequency(10,1);
  setPwmFrequency(11,1);

  analogWrite(cold_en, led_pwm);
  analogWrite(hot_en, led_pwm);

  cold_hotLastState = digitalRead(pwm_a);
  pwmLastState = digitalRead(cold_hot_a);
  
  Serial.begin(9600);
}

void loop() {

  pwmState = digitalRead(pwm_a);
  cold_hotState = digitalRead(cold_hot_a);


  if(pwmState != pwmLastState){

    if(digitalRead(pwm_b) != pwmState){
      pwm_counter += 2;
    }
    else{
      pwm_counter -= 2;
    }
    if(pwm_counter < 0)
   pwm_counter = 0;
   if(pwm_counter > 255)
   pwm_counter = 255;
    
  }
  pwmLastState = pwmState;


if(cold_hotState != cold_hotLastState){

    if(digitalRead(cold_hot_b) != cold_hotState){
      temp_counter += 2;
    }
    else{
      temp_counter -= 2;
    }
   if(temp_counter < 0)
   temp_counter = 0;
   if(temp_counter > 255)
   temp_counter = 255;
  }

  cold_hotLastState = cold_hotState;

//  Serial.print("PWM: ");
//   Serial.print(pwm_counter);
//   Serial.print("  ");
//   Serial.print("Temp: ");
//  Serial.println(temp_counter);


  // eeprom a yaz

  led_pwm = map(pwm_counter, 0,255,0,100);
  

  hot_pwm = temp_counter;
  cold_pwm = 255 - temp_counter;


  cold_pwm /= 100;
  cold_pwm *= led_pwm;
  
  hot_pwm = (hot_pwm/100)*led_pwm; 

  analogWrite(cold_en, cold_pwm);
  analogWrite(hot_en, hot_pwm);
  
  }
  

 
