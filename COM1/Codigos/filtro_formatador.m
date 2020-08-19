clear all
close all
clc

% Niveis de transmisssao, no caso zero e um
M = 2; 
% Numero de amostras
N = 100; 
% Numero de bits
n_bits = 10000;

% Filtro formatador
filtro_NRZ = ones(1,N); 
% Informacao
info = randint(1,n_bits,M);
% Superamostragem
info_up = upsample(info,N); 
% Filtragem para formatar o sinal
sinal_tx = conv(info_up,filtro_NRZ)*5;
% Truncando N-1 amostras restantes da convolucao
sinal_tx = sinal_tx(1:end-(N-1)); 

% Variancia do ruido
var_ruido = 0.1;
% Ruido
ruido = sqrt(var_ruido)*randn(1,length(sinal_tx));
% Sinal recebido com ruido
sinal_rx = sinal_tx + ruido;

% Subamostrando pegando amostra do meio
% e indo em intervalos de N. Sinal sem ruido
sinal_det = sinal_rx(N/2:N:end);


% Compara a um limiar para aproximar 
% o ruido
limiar = 2.5;
info_hat = sinal_det > limiar;
num_erro = sum(xor(info,info_hat));
taxa_erro = num_erro/n_bits

figure(1)
plot(sinal_tx)
xlim([0 10*N])

figure(2)
plot(sinal_rx);
xlim([0 10*N])