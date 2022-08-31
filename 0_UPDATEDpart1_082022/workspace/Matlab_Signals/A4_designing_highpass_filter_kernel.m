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



% %show all signals in a window frame
% subplot(4,1,1);
% plot(t, signal1, 'b.-', 'LineWidth', 1, 'MarkerSize',1);
% title('10Hz Signal');
% 
% subplot(4,1,2);
% plot(t, signal2, 'b.-', 'LineWidth', 1, 'MarkerSize',1);
% title('100Hz Signal');
% 
% subplot(4,1,3);
% plot(t, signal3, 'b.-', 'LineWidth', 1, 'MarkerSize',1);
% title('500Hz Signal');
% 
% subplot(4,1,4);
% plot(t, signal, 'g.-', 'LineWidth', 1, 'MarkerSize',1);
% title('10+100+500Hz Signal');

%------------------------------------------------------
%Implement 101 long high-pass filter of cutoff freq 400Hz,
%Sampling at 2000Hz (2Khz)
%FIR1 (kernel_lenght-1, cutoff/Sampling_rate, 'high')

Fc = 400;        %filter Cutof freq
Fs = 2000;      % sampling freq


h = fir1(100, Fc/Fs, 'high');  
%plot(h);

%------------------------------------------------------
%Frequencey Response

freqz(h);   

%------------------------------------------------------
% Convolution of the signal

filtered_sig = conv(h, signal);

%plot input signal & filtered Signal
subplot(3,1,1);
plot(signal, 'r.-', 'LineWidth', 1, 'MarkerSize', 1);
title('Input Signal');

subplot(3,1,2);
plot(signal3, 'b.-', 'LineWidth', 1, 'MarkerSize', 1);
title('Orj 500Hz Signal');

subplot(3,1,3);
plot(filtered_sig, 'g.-', 'LineWidth', 1, 'MarkerSize', 1);
title('Filtered Signal');

%------------------------------------------------------ 
%Save filter kernel to csv
csvwrite('hpf_fc_400hz.txt', h);




