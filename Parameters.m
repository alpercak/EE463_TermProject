Vout = 24;
Vin = 300; %It will be in a range e.g. 150 to 330V
i_out = 2; 
fs = 50000; %switching frequency
fc = 339; %Corner frequency for LC filter
delta_i = 0.2*i_out; %Desired inductor ripple current

delta_Vo = 0.05; %Desired peak to peak output voltage

D = Vout/Vin; %Duty cycle will also be in a range due to Vin variance

L = Vout*(1-D)/(fs*delta_i); %Inductor sizing

C = 1/(((2*pi*fc)^2)*L); %Capacitor sizing related to corner frequency
% C = delta_i/(8*fs*delta_Vo); %Capacitor sizing

Diode_size = i_out*(1-D); %V30K45, shotky