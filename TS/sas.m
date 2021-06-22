clc; 
clear all; 
close all;
s = tf('s');
P = 1/(s^2+11*s+28);
H = c2d(P, 0.1)