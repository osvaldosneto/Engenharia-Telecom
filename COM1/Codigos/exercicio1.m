close all;
clear all;
clc;

%Gerar um sinal s(t) composto pela somat?ria de 3 senos com amplitudes de 6V, 2V e 4V e 
%frequ?ncias de 1, 3 e 5 kHz, respectivamente.

A = 2;
f = 5000;
n = 50;                    %fator de super amostra deve de ser duas vezes a frequencia
n_periodo = 100;             %numeros de per?odos a ser apresentados na tela
fs = n*f;                   %frequencia de amostragem
t_final = n_periodo*(1/f);  %numero de periodos * periodo
ts = 1/fs;                  %tempo de amostragem - capturando o tempo em que ser? plotado o sinal
t = [0:ts:t_final];         %vetor de tempo


y = 3*A*sin(2*pi*f/5*t) + A*sin(2*pi*3000*t) + 2*A*sin(2*pi*f*t);
p_y = sum(y.^2)/length(y)
p_y2 = sum(y.^2)
std(y)^2
sqrt(p_y2)


%Plotar em uma figura os tr?s cossenos e o sinal 's ' no dom?nio do tempo e
%da frequ?ncia

%dom?niio do tempo
subplot(3,1,1);
plot(t,y, 'r');
%axis([0 t]);
ylabel('y(t)');
xlabel('tempo(s)');
xlim([0 0.003]);
title('Sinal y(t) - Dominio tempo');

%dominio da frequ?ncia
Y = fftshift(fft(y));
passo_f = 1/t_final;
f = [-fs/2 : passo_f : fs/2];
subplot(3,1,2);
plot(f, abs(Y));
ylabel('Amplitude');
xlabel('frequencia (Hz)');
xlim([-20000 20000])
title('Sinal Y(f) - Dominio frequencia');

%Utilizando a fun??o 'norm', determine a pot?ncia m?dia do sinal 's'.
n = norm(y)
n2 = n^2
%Utilizando a fun??o 'pwelch', plote a Densidade Espectral de Pot?ncia do sinal 's'.
subplot(3,1,3);
pwelch(y,[],[],[],fs,'onesided');
%subplot(3,1,3);
%plot(10*log10(pxx))
%ylabel('dB (rad/amostra)');
%xlabel('rad/amostra');
%title('Densidade Espectral de Potencia do Sinal')