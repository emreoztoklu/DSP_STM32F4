clc;            %clear command windows all
close all;      %close all figures 
clear;          %erase all existing variables
workspace;      %make sure workspace is showing

%show numbers in a compact form with 5 digit
format long g
format compact

%Set font size
fontSize = 2; 
%------------------------------------------------------
%------------------------------------------------------




%Make 0.5 seconds sampled every 1/2000 of second (2 khz sampling rate)
t = 0 : 1/2000: 0.5;   %interval 1/2000 (2khz)

%define wave parameters  (10Hz)
f1 = 10;  %10Hz
T1 = 1/f1;
amp1 = 1;

%define wave parameters  (100Hz)
f2 = 100;  %100Hz
T2 = 1/f2;
amp2 = 1;

%define wave parameters  (500Hz)
f3 = 500;  %100Hz
T3 = 1/f3;
amp3 = 1;



%Make signal
signal1 = amp1 * sin(2*pi*t/T1);
signal2 = amp2 * sin(2*pi*t/T2);
signal3 = amp3 * sin(2*pi*t/T3);


%Combining the Signals (10 + 100 + 500 Hz)
signal = signal1 + signal2 + signal3; 

%------------------------------------------------------
%compute DFT of the orjiginal signal (signal)
signal_fft = fft(signal);

%Get Signal length
len_signal = length(signal);

%Compute signal magnitude
magnitude_signal = abs(signal_fft);

%2Khz Sampling Frequency
Fs = 2000;
f  = Fs*(0:(len_signal/2))/len_signal;  %X-axis is frequency

P2 = abs(signal_fft / len_signal);
P1 = P2(1: len_signal/2 + 1);
P1(2:end -1) = 2*P1(2:end -1);

plot(f, P1);
title('Single-Sided Amplitude Spectrum of x(t)');
xlabel('f(hz');


%%
% filter designer
% >> fdatool 

%https://www.udemy.com/course/arm-cortex-dsp/learn/lecture/33396494#questions/18142862
%%
% >> lpf_5hz_60hz
% >> plot(lpf_5hz_60hz)
% >> csvwrite('lpf_5hz_60hz.txt',lpf_5hz_60hz)
