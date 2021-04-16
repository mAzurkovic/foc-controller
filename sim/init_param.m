clear all;

%% PWM Switching frequency
PWM_frequency 	= 20e3;    
T_pwm           = 1/PWM_frequency;  

%% Sampling Tim
Ts          	= T_pwm;            
Ts_simulink     = T_pwm/20;          
Ts_motor        = T_pwm/20;            
Ts_inverter     = T_pwm/20;             
Ts_speed        = 10*Ts;          

%% Data Type

dataType = 'single';           

%% Motor Parameters
pmsm.model  = 'Teknic-2310P';   % Motor           
pmsm.p      = 4;                % Pole Pairs           
pmsm.Rs     = 0.36;             % Stator Resistance (ohms)       
pmsm.Ld     = 0.2e-3;           % D-axis inductance (H)        
pmsm.Lq     = 0.4e-3;           % Q-axis inductance (H)         
pmsm.J      = 10.061551833333e-4;% Inertia (Kg-m2)      
pmsm.B      = 2.636875217824e-6;% Kg-m2/s    
pmsm.Ke     = 4.64;             % Bemf Const	
pmsm.Kt     = 0.274;            % Nm/A       
pmsm.I_rated= 7.1;              % Max Current Is (A)      	
pmsm.N_max  = 6000;             % Max Speed (RPM)                 
pmsm.FluxPM     = (pmsm.Ke)/(sqrt(3)*2*pi*1000*pmsm.p/60); % (Wb) 
pmsm.T_rated    = (3/2)*pmsm.p*pmsm.FluxPM*pmsm.I_rated; % Max Torque (Nm)  

Lq = pmsm.Lq;
Ld = pmsm.Lq;
Rs = pmsm.Rs;
flux = pmsm.FluxPM;
J = pmsm.J;
B = pmsm.B;

tau = 1e-4;
damping = 80;

K = (3*pmsm.p*flux)/(2*J);

Kd = 1/(damping^2*tau)
Kc = 1/(damping*K*tau)

Ka = Lq * 3000 * 2 * pi;
Ka2 = 10*Lq/(damping*tau)
Ka3 = (pi*Lq)/(5*Ts)
Kb = Rs/Lq;
Kp = Ka;
Ki = Kb * Kp;

Vol = zpk([], [(-B/J) (-Ka/Lq)], (1.5*pmsm.p*flux/B));

%% Inverter Parameters

inverter.V_dc           = 24; % (V)      
inverter.Rds_on         = 2e-3;     % (Ohms)  
inverter.Rshunt         = 1e-6;   % (Ohms) 

%% ControllerGains PI

% Reference: https://e2e.ti.com/blogs_/b/industrial_strength/archive/2015/07/20/teaching-your-pi-controller-to-behave-part-i
BW_hz = 3000; % in Hz
Kp_id = 2*pi*BW_hz*pmsm.Ld; 
Ki_id = 2*pi*BW_hz*pmsm.Rs*Ts; 
Kp_iq = 2*pi*BW_hz*pmsm.Lq; 
Ki_iq = 2*pi*BW_hz*pmsm.Rs*Ts; 
