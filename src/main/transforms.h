#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#define ADC_CONVERT 204.6
#define AMPLIFIER_GAIN 10
#define R_SHUNT 0.005

void forwardClarke(float a, float b, float c) {
  float alpha = a;
  float beta =  1/sqrt(3) * a + 2/sqrt(3) * b; 
}

void inverseClarke(float alpha, float beta) {
  float a = alpha;
  float b = -0.5*alpha + sqrt(3)/2 * beta;
  float c = -0.5*alpha - sqrt(3)/2 * beta;
}

void forwardPark(float alpha, float beta, float theta) {
  float d = alpha * cos(theta) + beta * sin(theta);
  float q = -alpha * sin(theta) + beta * cos(theta);
}

void inversePark(float d, float q, float theta) {
  float alpha = d * cos(theta) - q * sin(theta);
  float beta = d * sin(theta) + q * cos(theta);
}

float toCurrent(int val) {
  return (( val / ADC_CONVERT ) / AMPLIFIER_GAIN) / R_SHUNT;
}

#endif
