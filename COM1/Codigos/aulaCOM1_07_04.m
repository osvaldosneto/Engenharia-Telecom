clear all
close all
clc
M = 2; #número de níveis de transmissão
N = 100;
A = 5; # Amplitude do sinal
limiar = A/2;
Rb = 10e4;
Tb = 1/Rb;
BW = Rb;
t_final = 1;
passo_t = 1/(Rb*N);
t = [0:passo_t:t_final-passo_t];
var_ruido = 1;
filtro_NRZ = ones(1,N); # filtro que formator do sinal
info = randint(1,Rb*t_final,M); # gerando a informação
info_up = upsample(info,N); # super-amostragem
sinal_tx = conv(info_up,filtro_NRZ)*A; # processo de filtragem para formatar o sinal
sinal_tx = sinal_tx(1:end-(N-1)); # truncando o sinal devido ao processo de convolução
ruido = sqrt(var_ruido)*randn(1,length(sinal_tx));
sinal_rx = sinal_tx + ruido;
sinal_det = sinal_rx(N/2:N:end);
info_hat = sinal_det > limiar;
n_erro = sum(xor(info, info_hat))
taxa_erro = n_erro/(Rb*t_final)

figure(1)
plot(t,sinal_tx)
xlim([0 10*Tb])
hold on
plot(t,sinal_rx)
xlim([0 10*Tb])