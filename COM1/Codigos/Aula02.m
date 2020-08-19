close all;
clear all;

a = 6;                  %amplitude
fm = 1e3;               %frequencia do seno
n = 200;                 %fator de super amostra
fs = n*fm;              %frequencia de amostragem
num_periodo = 200;      %numeros de períodos a ser apresentados na tela
t_final = num_periodo*(1/fm);
ts = 1/fs;              %tempo de amostragem (espaçamento entre amostras)
t = [0:ts:t_final];
y = a*sin(2*pi*fm*t)+(a/3)*sin(2*pi*3*fm*t)+(a/5)*sin(2*pi*5*fm*t)+(a/7)*sin(2*pi*7*fm*t);
figure(1);
plot(t,y);
axis([0 50/fm -a a]);

passo_f = 1/t_final;
f1 = [-fs/2:passo_f:fs/2];
y = fft(y)/length(y);
figure(2);
plot(f1,abs(fftshift(y)));
axis ([-7*fm 7*fm 0 1.5*a])