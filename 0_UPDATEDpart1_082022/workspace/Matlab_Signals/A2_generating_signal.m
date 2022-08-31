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


%show all signals in a window frame
subplot(4,1,1);
plot(t, signal1, 'b.-', 'LineWidth', 1, 'MarkerSize',1);
title('10Hz Signal');

subplot(4,1,2);
plot(t, signal2, 'b.-', 'LineWidth', 1, 'MarkerSize',1);
title('100Hz Signal');

subplot(4,1,3);
plot(t, signal3, 'b.-', 'LineWidth', 1, 'MarkerSize',1);
title('500Hz Signal');

subplot(4,1,4);
plot(t, signal, 'g.-', 'LineWidth', 1, 'MarkerSize',1);
title('10+100+500Hz Signal');





