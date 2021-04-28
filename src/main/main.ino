#include "transforms.h"
#include "controller.h"
#include <AS5600.h>

#define SELECT 2
#define ENABLE 10
#define M_OC 9
#define M_PWM 8
#define OC_ADJ 11
#define GAIN 12
#define A_CURRENT A2
#define B_CURRENT A3

#define PWM_A 3
#define PWM_B 5
#define PWM_C 6


void setup() {
  Serial.begin(9600);

  // Set the speed of PWM signals
  TCCR0B = TCCR0B & 0b11111000 | 0x01;
  TCCR1B = TCCR1B & 0b11111000 | 0x01;
  TCCR2B = TCCR2B & 0b11111000 | 0x01;

  // Digital pin assignments  
  pinMode(M_PWM, OUTPUT);
  pinMode(M_OC, OUTPUT);
  pinMode(OC_ADJ, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  pinMode(SELECT, OUTPUT);
  pinMode(GAIN, OUTPUT);
  pinMode(PWM_A, OUTPUT); 
  pinMode(PWM_B, OUTPUT); 
  pinMode(PWM_C, OUTPUT); 

  // Analog pin assignments  
  pinMode(A_CURRENT, INPUT);

  // Set pin settings
  digitalWrite(M_PWM, HIGH);
  digitalWrite(M_OC, HIGH);
  digitalWrite(OC_ADJ, HIGH);
  digitalWrite(ENABLE, HIGH);
  digitalWrite(SELECT, HIGH);
  digitalWrite(GAIN, LOW); // Set current amplifier gain to 10V/V

  
}

void loop() {
  
}
