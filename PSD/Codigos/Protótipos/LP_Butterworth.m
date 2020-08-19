clear all
close all
clc

n = 2;
k = 1:n;

% Passo 2 - Polos do filtro
pk = exp(1j*(2*k+n-1)/(2*n)*pi)
% zplane(1,poly(pk));

% Passo 3 - parte real de um polinomio com raizes pk
Dp = real(poly(pk))

% Passo 4 - Funcao transferencia
syms p
Dps = vpa(1*p^2 + 1.414*p^1 + 1*p^0);

figure(1)
% Gerando grafico do filtro
[h,w] = freqs(1,Dp,1000);
semilogx(w,20*log10(abs(h))); grid on;
title('Filtro LP Butterworth sem ajuste')
% Ganho nos pontos das freq passadas como param.
[h,w] = freqs(1,Dp,[0,1,5]);
20*log10(abs(h))

% Passos 5 e 6 - Ajustando o filtro
G0db = 5;
bs = 1*10^(G0db/20);
as = [625e-6 35.35e-3 1];

figure(2)
[h,w] = freqs(bs,as,1000);
semilogx(w,20*log10(abs(h))); grid on;
title('Filtro LP Butterworth com ajuste')
% Ganho nos pontos das freq passadas como param.
[h,w] = freqs(bs,as,[0,40,200]);
