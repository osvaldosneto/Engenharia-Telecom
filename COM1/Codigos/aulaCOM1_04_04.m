clear all
close all
clc
M = 2; #número de níveis de transmissão
N = 100;
limiar = 2.5;
n_bits = 10000;
var_ruido = 0.1;
filtro_NRZ = ones(1,N); # filtro que formator do sinal
info = randint(1,n_bits,M); # gerando a informação
info_up = upsample(info,N); # super-amostragem
sinal_tx = conv(info_up,filtro_NRZ)*5; # processo de filtragem para formatar o sinal
sinal_tx = sinal_tx(1:end-(N-1)); # truncando o sinal devido ao processo de convolução

ruido = sqrt(var_ruido)*randn(1,length(sinal_tx));
sinal_rx = sinal_tx + ruido;
sinal_det = sinal_rx(N/2:N:end);
info_hat = sinal_det > limiar;
n_erro = sum(xor(info, info_hat))
taxa_erro = n_erro/n_bits

figure(1)
plot(sinal_tx)
xlim([0 10*N])
hold on
plot(sinal_rx)
xlim([0 10*N])