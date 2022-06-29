
#include <Servo.h>

#define max_pulse 2000
#define min_pulse 1000

Servo motor_R, motor_L;

int pot_value, pwm_value;

void setup() {

  Serial.begin(9600);
  motor_R.attach(9, min_pulse, max_pulse);
  motor_L.attach(10, min_pulse, max_pulse);

}

void loop() {

  pot_value = analogRead(A0);
  pwm_value = map(pot_value, 0,1024,1000,2000);
  motor_R.writeMicroseconds(pwm_value);
  motor_L.writeMicroseconds(pwm_value);
  Serial.print(pot_value);
  Serial.print(" , ");
  Serial.println(pwm_value);
}
