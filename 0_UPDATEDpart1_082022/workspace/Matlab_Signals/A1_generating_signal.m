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

%define wave parameters
f1 = 10;  %10Hz
T1 = 1/f1;
amp1 = 1;

%Make signal
signal1 = amp1 * sin(2*pi*t/T1);

%show the signal
plot(t, signal1);
