#ifndef CONTROLLER_H
#define CONTROLLER_H

#define PWM_A 3
#define PWM_B 5
#define PWM_C 6

typedef struct {
  // Controller gains
  float Kp;
  float Ki;

  // Controller sample time (seconds)
  float dt;

  // Controller variables
  float integral;
  
  float output;
} PI_Controller;


//*****************************************************************************//
// This function sets the PID controller gains, sample time, and total         //
// samples.                                                                    //
//*****************************************************************************//
void initPI(PI_Controller *pi, float Kp, float Ki, float dt) {
  pi->Kp = Kp;
  pi->Ki = Ki;
  pi->dt = dt;
  pi->integral = 0;
}

//*****************************************************************************//
// This function computes the updated output based on the current measurement  //
// and set-point provided.                                                     //
//*****************************************************************************//
float updatePI(PI_Controller *pi, float setPoint, float current) {
  float error = setPoint - current;
  float pTerm, iTerm;
  
  // Compute the proportional term
  pTerm = pi->Kp * error;

  // Compute the intergral term
  pi->integral += pi->dt * error;
  iTerm = pi->Ki * pi->integral;
  
  // Compute the final PID control output
  pi->output = pTerm + iTerm;

  return pi->output;
}


void currentLoop(float currents[], float elecPos, float Id_Setpoint, float Iq_Setpoint, PI_Controller *Dpi, PI_Controller *Qpi) {
  float a = currents[0];
  float b = currents[1];
  float c = currents[2];

  float alpha = a;
  float beta =  1/sqrt(3) * a + 2/sqrt(3) * b; 
  float d = alpha * cos(elecPos) + beta * sin(elecPos);
  float q = -alpha * sin(elecPos) + beta * cos(elecPos);

  // Compute the Vq and Vd correction voltages
  float Vd = updatePI(Dpi, Id_Setpoint, d);
  float Vq = updatePI(Qpi, Iq_Setpoint, q);
    
  alpha = Vd * cos(elecPos) - Vq * sin(elecPos);
  beta = Vd * sin(elecPos) + Vq * cos(elecPos);

  a = alpha;
  b = -0.5*alpha + sqrt(3)/2 * beta;
  c = -0.5*alpha - sqrt(3)/2 * beta;

  digitalWrite(PWM_A, 255/12 * a);
  digitalWrite(PWM_B, 255/12 * b);
  digitalWrite(PWM_C, 255/12 * c);
}

#endif
