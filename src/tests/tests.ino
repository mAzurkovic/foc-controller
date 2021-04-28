#include <AS5600.h>

#define PWM_A 3
#define PWM_B 5
#define PWM_C 6
#define ENABLE 7
#define A_OUT A2

AS5600 encoder;
double output;

void setup() {
  Serial.begin(9600);
  
  // sets the speed of PWM signals. 
  TCCR0B = TCCR0B & 0b11111000 | 0x01;
  TCCR1B = TCCR1B & 0b11111000 | 0x01;
  TCCR2B = TCCR2B & 0b11111000 | 0x01;

  pinMode(PWM_A, OUTPUT); 
  pinMode(PWM_B, OUTPUT); 
  pinMode(PWM_C, OUTPUT); 
  pinMode(ENABLE, OUTPUT); 

  digitalWrite(ENABLE, HIGH);
}

void loop() {
  output = encoder.getPosition(); // get the absolute position of the encoder
  //Serial.println(output);
  float iA = analogRead(A2);
  Serial.println(iA);          // debug value

}
