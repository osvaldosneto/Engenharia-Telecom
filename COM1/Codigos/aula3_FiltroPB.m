close all;
clear all;

a = 6;                  %amplitude
fm = 1e3;               %frequencia do seno
n = 200;                 %fator de super amostra
fs = n*fm;              %frequencia de amostragem
num_periodo = 250;      %numeros de períodos a ser apresentados na tela
t_final = num_periodo*(1/fm);
ts = 1/fs;              %tempo de amostragem (espaçamento entre amostras)
t = [0:ts:t_final];
y = a*cos(2*pi*fm*t)+(a/3)*cos(2*pi*3*fm*t)+(a/5)*cos(2*pi*5*fm*t)+(a/7)*cos(2*pi*7*fm*t);
figure(1);
plot(t,y);
axis([0 50/fm -a a]);

Y = fftshift(y);
passo_f = 1/t_final;
f = [-fs/2:passo_f:fs/2];
y = fft(y)/length(y);
figure(2);
plot(f,abs(Y));
axis ([-7*fm 7*fm 0 1.5*a])


%filtro Passa Baixa
filtro_PB = [zeros(1,24625) ones(1,751) zeros(1,24625)];
Y_filtrado = abs(Y) .* filtro_PB;
figure(3);

plot(f,filtro_PB);
ylim([0 1.5]);
            82



