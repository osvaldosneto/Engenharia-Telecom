clear all
close all
clc
M = 2; #número de níveis de transmissão
N = 20;
A = 2; # Amplitude do sinal
limiar = 0;
Rb = 10e3;
Fs = N*Rb;
Tb = 1/Rb;
BW = Rb;
t_final = 1;
passo_t = 1/(Rb*N);
t = [0:passo_t:t_final-passo_t];
passo_f = 1/t_final;
f = [-Fs/2:passo_f:Fs/2-passo_f];
var_ruido = 1;
filtro_NRZ = ones(1,N);
ordem_filtro = 20; # Neste programa, não colocar a ordem maior do que N! 
f_cut = 2*Rb;
filtro_Rx = fir1(ordem_filtro, (2*f_cut)/Fs); # filtro que formator do sinal
info = randint(1,Rb*t_final,M); # gerando a informação
info_up = upsample(info,N); # super-amostragem
sinal_tx_aux = conv(info_up,filtro_NRZ); # processo de filtragem para formatar o sinal
sinal_tx = sinal_tx_aux(1:end-(N-1))*2*A-A; # truncando o sinal devido ao processo de convolução
ruido = sqrt(var_ruido)*randn(1,length(sinal_tx));
sinal_rx = sinal_tx + ruido;
sinal_rx_filter = filter(filtro_Rx, 1, sinal_rx);
sinal_det = sinal_rx_filter(ordem_filtro:N:end);
info_rec = sinal_det > limiar;
n_erro = sum(xor(info, info_rec))
taxa_erro = n_erro/(Rb*t_final)

# Análise em frequêcia
Rx = xcorr(sinal_tx);
Gx1 = fftshift(fft(Rx));
SINAL_TX = fft(sinal_tx);
Gx2 = fftshift(abs(SINAL_TX).^2);
figure(1)
plot(t,sinal_tx)
xlim([0 10*Tb])
hold on
plot(t,sinal_rx)
xlim([0 10*Tb])
hold on
plot(t(1:end-(ordem_filtro/2)+1),sinal_rx_filter(ordem_filtro/2:end),'k')

figure(2)
subplot(211)
f_aux = [-Fs/2:passo_f/2:Fs/2-passo_f];
plot(f_aux, abs(Gx1)/length(Rx))
subplot(212)
plot(f,abs(Gx2)/length(sinal_tx))