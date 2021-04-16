clear all;


%% PWM Switching frequency
PWM_frequency 	= 20e3;    
T_pwm           = 1/PWM_frequency;  

%% Sampling Time
Ts          	= T_pwm;            
Ts_simulink     = T_pwm/20;          
Ts_motor        = T_pwm/20;            
Ts_inverter     = T_pwm/20;             
Ts_speed        = 10*Ts;          

%% Data Type

%dataType = 'single';           

%% Motor Parameters
pmsm.model  = 'Teknic-2310P';   % Motor           
pmsm.p      = 7;                % Pole Pairs           
pmsm.Rs     = 3.33;             % Stator Resistance (ohms)       
pmsm.Ld     = 2.1e-3;           % D-axis inductance (H)        
pmsm.Lq     = 2.1e-3;           % Q-axis inductance (H)         
pmsm.J      = 6.1e-6;% Inertia (Kg-m2)      
pmsm.B      = 2.636875217824e-6;% Kg-m2/s    
pmsm.Ke     = 4.64;             % Bemf Const	
pmsm.Kt     = 0.1;            % Nm/A       
pmsm.I_rated= 1.45;              % Max Current Is (A)      	
pmsm.N_max  = 1500;             % Max Speed (RPM)                 
pmsm.FluxPM     = (pmsm.Ke)/(sqrt(3)*2*pi*1000*pmsm.p/60); % (Wb) 
pmsm.T_rated    = (3/2)*pmsm.p*pmsm.FluxPM*pmsm.I_rated; % Max Torque (Nm)  

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
