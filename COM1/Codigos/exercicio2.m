close all;
clear all;
clc;

%Gerar um sinal s(t) composto pela somat?ria de 3 senos com amplitudes
%de 5V, 5/3V e 1V e frequ?ncias de 1, 3 e 5 kHz, respectivamente.

A = 5;
f = 5000;
n = 50;                     %fator de super amostra deve de ser duas vezes a frequencia
n_periodo = 100;            %numeros de per?odos a ser apresentados na tela
fs = n*f;                   %frequencia de amostragem
t_final = n_periodo*(1/f);  %numero de periodos * periodo
ts = 1/fs;                  %tempo de amostragem - capturando o tempo em que ser? plotado o sinal
t = [0:ts:t_final];         %vetor de tempo


y = A*sin(2*pi*f/5*t) + A/3*sin(2*pi*3000*t) + A/5*sin(2*pi*f*t);

%Plotar em uma figura os tr?s cossenos e o sinal 's ' no dom?nio do tempo e
%da frequ?ncia

%dom?niio do tempo
figure(1)
subplot(2,1,1);
plot(t,y, 'r');
xlim([0 2e-3])
ylabel('y(t)');
xlabel('tempo(s)');
title('Sinal y(t) - Dominio tempo');

%dominio da frequ?ncia
Y = fftshift(fft(y));
passo_f = 1/t_final;
f = [-fs/2 : passo_f : fs/2];
subplot(2,1,2);
plot(f, abs(Y));
xlim([-1e4 1e4]);
ylabel('Amplitude');
xlabel('frequ?ncia (f)');
title('Sinal Y(f) - Dominio frequencia');

%Passa baixa (frequ?ncia de corte em 2kHz)
n_filtro_pb = fs/passo_f;
intervalo_filtro = fs/n_filtro_pb;

figure(2)
%filtro passa baixa
n_PB = [zeros(1, 2460) ones(1, 81) zeros(1, 2460)];
Y_filtrado_PB = Y.*n_PB;

%plotagem 
subplot(3,2,1)
plot(f, Y_filtrado_PB, 'r')
xlim([-1e4 1e4])
title('Resposta ao Filtro Passa Baixa - 2 KHz')
ylabel('Amplitude');
xlabel('frequ?ncia (f)');
ylim([0,200])

subplot(3,2,2);
y_PB = ifft(ifftshift(Y_filtrado_PB));
plot(t, y_PB, 'r');
xlabel('tempo(s)');
title('Sinal Filtrado Passa Baixa - 2 KHz');
xlim([0, 3e-3])
ylim([-5.5 5.5])

n_PA = [ ones(1, 2420) zeros(1, 161) ones(1, 2420)];
subplot(3,2,3)
Y_filtrado_PA = n_PA.*Y;
plot(f, Y_filtrado_PA, 'b');
title('Resposta ao Filtro Passa Alta - 4 KHz')
ylabel('Amplitude');
xlabel('frequ?ncia (f)');
ylim([0,200]);
xlim([-1e4 1e4])

subplot(3,2,4);
y_PA = ifft(ifftshift(Y_filtrado_PA));
plot(t, y_PA, 'b');
xlabel('tempo(s)');
title('Sinal Filtrado Passa Alta - 4 KHz');
xlim([0, 3e-3])

n_PBanda = ([zeros(1,2420) ones(1,40) zeros(1, 81) ones(1, 40) zeros(1, 2420)]);
subplot(3,2,5);
Y_filtrado_PBanda = n_PBanda.*Y;
plot(f, Y_filtrado_PBanda, 'gr');
title('Resposta ao Filtro Passa Banda - 2 a 4 KHz')
ylabel('Amplitude');
xlabel('frequ?ncia (f)');
ylim([0,200]);
xlim([-1e4 1e4]);

subplot(3,2,6);
y_PBanda = ifft(ifftshift(Y_filtrado_PBanda));
plot(t, y_PBanda, 'gr');
xlabel('tempo(s)');
title('Sinal Filtrado Passa Banda - 2 a 4 KHz');
xlim([0, 3e-3])

figure(3);
subplot(3,1,1);
plot(f, n_PB);
xlim([-5000, 5000]);
ylim([0 1.2])

