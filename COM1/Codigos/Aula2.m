close all;
clear all;

a = 1;
f = 1000;                       %frequencia seno
fs = 2000*f;                    %frequencia de amostragem
periodos = 10;                %numero de periodo
t_final = periodos*(1/f);       %tempo final
Ts = 1/fs;                      %tempo de amostragem
t = 0:Ts:t_final-Ts;            %eixo do tempo

x = a*sin(2*pi*f*t);
X = fft(x)/length(x);
%axis([0 1, f-1 1]);

figure(1)
plot (t,x)

figure(2)
plot (abs(X))

figure(3)
plot (abs(fftshift(X)))