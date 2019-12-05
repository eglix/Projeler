#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 3); // RX, TX
char data;

#define left_1 A1
#define left_2 A2
#define right_2 A3
#define right_1 A4
#define yesil_led 12
#define kirmizi_led 2
#define mavi_led 13

#define left_en 10
#define right_en 9

float hiz = 80, yavas_hiz=40;
float ramp_time = 80;
float anlik_hiz =0;
float anlik_yavas_hiz=0;
float hiz_artis = 0;
float yavas_hiz_artis=0;

int rampa_status = 0;
int i, ramp_start = 15;
 
void setup() {
pinMode(A1,OUTPUT);   //Sol Motor 2
pinMode(A2,OUTPUT);   //Sol Motor 1
pinMode(A3,OUTPUT);   //Sağ Motor 1
pinMode(A4,OUTPUT);   //Sağ Motor 2
pinMode(9,OUTPUT);   //Sağ Motor EN
pinMode(10,OUTPUT);   //Sol Motor EN
pinMode(13,OUTPUT);   //Sol Motor EN

pinMode(8,OUTPUT);   //Sol Motor EN
pinMode(7,OUTPUT);   //Sol Motor EN
pinMode(yesil_led,OUTPUT);   //Sol Motor EN
pinMode(kirmizi_led,OUTPUT);   //Sol Motor EN

digitalWrite(8,LOW);
digitalWrite(7,LOW);

analogWrite(left_en,hiz);
analogWrite(right_en,hiz);

hiz_artis = hiz / ramp_time;
yavas_hiz_artis = yavas_hiz / ramp_time;

Serial.begin(9600);
mySerial.begin(9600);

digitalWrite(mavi_led, LOW);
digitalWrite(yesil_led, LOW);
digitalWrite(kirmizi_led, LOW);


digitalWrite(mavi_led, HIGH);
delay(250);
digitalWrite(yesil_led, HIGH);
delay(250);
digitalWrite(kirmizi_led, HIGH);
delay(250);
digitalWrite(mavi_led, LOW);
digitalWrite(yesil_led, LOW);
digitalWrite(kirmizi_led, LOW);
delay(1000);

for(int a=0; a<3;a++){
digitalWrite(mavi_led, HIGH);
delay(20);
digitalWrite(mavi_led, LOW);
delay(250);
digitalWrite(yesil_led, HIGH);
delay(20);
digitalWrite(yesil_led, LOW);
delay(250);
digitalWrite(kirmizi_led, HIGH);
delay(20);
digitalWrite(kirmizi_led, LOW);
delay(250);
}

}

void ileri(){


  
  digitalWrite(left_1, HIGH);
  digitalWrite(left_2, LOW);
  digitalWrite(right_1, HIGH);
  digitalWrite(right_2, LOW);
 

 if(rampa_status){
  for(i=ramp_start;i<ramp_time;i++){
   anlik_hiz += hiz_artis;
   anlik_yavas_hiz += yavas_hiz_artis;
   
   analogWrite(left_en,anlik_hiz);
   analogWrite(right_en,anlik_hiz);
   delay(10);
   Serial.println(anlik_hiz);
  }
  rampa_status = 0;
  }

   analogWrite(left_en,hiz);
   analogWrite(right_en,hiz);


  
  digitalWrite(13,HIGH);
  delay(100);
  digitalWrite(13,LOW);
  delay(100);
}

void geri(){
  
  digitalWrite(left_1, LOW);
  digitalWrite(left_2, HIGH);
  digitalWrite(right_1, LOW);
  digitalWrite(right_2, HIGH);


 if(rampa_status){
  for(i=ramp_start;i<ramp_time;i++){
   anlik_hiz += hiz_artis;
   anlik_yavas_hiz += yavas_hiz_artis;
   
   analogWrite(left_en,anlik_hiz);
   analogWrite(right_en,anlik_hiz);
   delay(10);
   Serial.println(anlik_hiz);
  }
  rampa_status = 0;
  }

  analogWrite(left_en,hiz);
  analogWrite(right_en,hiz);
}

void sol(){

  

  digitalWrite(left_1, LOW);
  digitalWrite(left_2, HIGH);
  digitalWrite(right_1, HIGH);
  digitalWrite(right_2, LOW);



 if(rampa_status){
  for(i=ramp_start;i<ramp_time;i++){
   anlik_hiz += hiz_artis;
   anlik_yavas_hiz += yavas_hiz_artis;
   
   analogWrite(left_en,anlik_hiz);
   analogWrite(right_en,anlik_hiz);
   delay(10);
   Serial.println(anlik_hiz);
  }
  rampa_status = 0;
  }
  analogWrite(left_en,hiz);
  analogWrite(right_en,hiz);
}

void sag(){

 
  digitalWrite(left_1, HIGH);
  digitalWrite(left_2, LOW);
  digitalWrite(right_1, LOW);
  digitalWrite(right_2, HIGH);



 if(rampa_status){
  for(i=ramp_start;i<ramp_time;i++){
   anlik_hiz += hiz_artis;
   anlik_yavas_hiz += yavas_hiz_artis;
   
   analogWrite(left_en,anlik_hiz);
   analogWrite(right_en,anlik_hiz);
   delay(10);
   Serial.println(anlik_hiz);
  }
  rampa_status = 0;
  }

  analogWrite(left_en,hiz);
   analogWrite(right_en,hiz);
  
}

void dur(){
  digitalWrite(left_1, LOW);
  digitalWrite(left_2, LOW);
  digitalWrite(right_1, LOW);
  digitalWrite(right_2, LOW);

  rampa_status = 1; 

 anlik_hiz =0;
  anlik_yavas_hiz=0;
}


void sag_ileri_capraz(){

  
  digitalWrite(left_1, HIGH);
  digitalWrite(left_2, LOW);
  digitalWrite(right_1, HIGH);
  digitalWrite(right_2, LOW);

 

 if(rampa_status){
  for(i=ramp_start;i<ramp_time;i++){
   anlik_hiz += hiz_artis;
   anlik_yavas_hiz += yavas_hiz_artis;
   
   analogWrite(left_en,anlik_hiz);
   analogWrite(right_en,anlik_yavas_hiz);
   delay(10);
   Serial.println(anlik_hiz);
  }
  rampa_status = 0;
  }

  analogWrite(left_en,hiz);
   analogWrite(right_en,yavas_hiz);
 
}

void sol_ileri_capraz(){

  
  digitalWrite(left_1, HIGH);
  digitalWrite(left_2, LOW);
  digitalWrite(right_1, HIGH);
  digitalWrite(right_2, LOW);



 if(rampa_status){
  for(i=ramp_start;i<ramp_time;i++){
   anlik_hiz += hiz_artis;
   anlik_yavas_hiz += yavas_hiz_artis;
   
   analogWrite(left_en,anlik_yavas_hiz);
   analogWrite(right_en,anlik_hiz);
   delay(10);
   Serial.println(anlik_hiz);
  }
  rampa_status = 0;
  }

  analogWrite(left_en,yavas_hiz);
   analogWrite(right_en,hiz);
 
}

void sol_geri_capraz(){

  
  digitalWrite(left_1, LOW);
  digitalWrite(left_2, HIGH);
  digitalWrite(right_1, LOW);
  digitalWrite(right_2, HIGH);



 if(rampa_status){
  for(i=ramp_start;i<ramp_time;i++){
   anlik_hiz += hiz_artis;
   anlik_yavas_hiz += yavas_hiz_artis;
   
   analogWrite(left_en,anlik_yavas_hiz);
   analogWrite(right_en,anlik_hiz);
   delay(10);
   Serial.println(anlik_hiz);
  }
  rampa_status = 0;
  }
  analogWrite(left_en,yavas_hiz);
  analogWrite(right_en,hiz);
 
}


void sag_geri_capraz(){

  
  digitalWrite(left_1, LOW);
  digitalWrite(left_2, HIGH);
  digitalWrite(right_1, LOW);
  digitalWrite(right_2, HIGH);

  

 if(rampa_status){
  for(i=ramp_start;i<ramp_time;i++){
   anlik_hiz += hiz_artis;
   anlik_yavas_hiz += yavas_hiz_artis;
   
   analogWrite(left_en,anlik_hiz);
   analogWrite(right_en,anlik_yavas_hiz);
   delay(20);
   Serial.println(anlik_hiz);
  }
  rampa_status = 0;
  }

  analogWrite(left_en,hiz);
  analogWrite(right_en,yavas_hiz);
 
}
 
void loop() {


  
if(mySerial.available()){
  data = mySerial.read();
  Serial.println(data);
}
 
if(data == 'F'){            
 ileri();
}
 
else if(data == 'B'){      
  geri();
}
 
else if(data == 'L'){      
  sol();
}
 
else if(data == 'R'){     
 sag();
}

else if(data == 'I'){     
 sag_ileri_capraz();
}

else if(data == 'G'){     
 sol_ileri_capraz();
}

else if(data == 'J'){     
 sag_geri_capraz();
}

else if(data == 'H'){     
 sol_geri_capraz();
}
 
else if(data == 'S'){      
  dur();
}

}
