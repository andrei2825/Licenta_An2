function [ y1, y2, y3, y4 ] = ts_continous_conv( t )
%% ts_continous_conv 
% Outputs the convolution result between u and h and shows up its plot vs
% time t

% u - input function
% h - impulse response function
% t - time steps array

h = (100/3) * exp(1).^(-t/3);

dt = t(2) - t(1);
u1 = sin(100*t);
u2 = (1+sign(t))/2;
u3 = u1 + u2;
u4 = (1+sign(t-3))/2;

y1 = conv(u1,h)*dt 
y1 = y1(1:length(t));

figure;
plot(t,y1);

y2 = conv(u2,h)*dt 
y2 = y2(1:length(t));

figure;
plot(t,y2);
%Automobilul ajunge la viteza maxima in momentul t = 24 secunde.
%Cand acceleratia este apasata la 50%, viteza maxima este redusa la
%jumatate, dar timpul pana cand masina ajunge la aceasta este aceasta este
%identic.
y3 = conv(u3,h)*dt 
y3 = y3(1:length(t));

figure;
plot(t,y3);

y4 = conv(u4,h)*dt 
y4 = y4(1:length(t));

figure;
plot(t,y4);

end
