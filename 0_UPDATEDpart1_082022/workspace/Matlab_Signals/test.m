clc;
clear;
close all;


Ts=0.005; %200 hz
Fs=1/Ts;

z=tf('z',Ts);

syms stable unstable
state = stable;


switch(state) 
    case(stable)
        for alpha=0.001:0.02:0.995;          %% Alpha increases   0<alpha<1 important stabilty
            beta= 1-alpha;                  %% a+b=1
            G = beta /(z-alpha);            %% IIR Low Pass Filter Equation
            [num,den]=tfdata(G,'v');        %% Transfer Function
            hold on
               freqz(num,den);             %% frequency Respone
            %  pzmap(num,den);
        end
    case(unstable)
         for alpha=1.1:0.05:2;         %% 0<alpha<1 important stabilty this is  unstable
            beta= 1-alpha;
            G = beta /(z-alpha);           %% low pass filter equation
            [num,den]=tfdata(G,'v');
            hold on
            %  freqz(num,den);             %% frequency Respone
            pzmap(num,den);
         end
end