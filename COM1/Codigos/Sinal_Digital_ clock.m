clear all
close all
clc
#* Parâmetros iniciais *
M = 2; #Transmissão binária
Fs = 100e3; #Frequência de amostragem
Ts = 1/Fs; #Período de amostragem
Rb = 1e3; #Taxa de transmissão
Tb = 1/Rb; #Duração do bit
N = Fs/Rb; #Fator de superamostragem. Neste script N tem que ser inteiro!
A = 2; #Nível de amplitude do pulso

#* Definição do eixo tempo *
periodo_tx = 4; #Período de transmissão em segundos
t = [0:Ts:periodo_tx-Ts];

#* Definição do eixo frequência *
delta_f = 1/periodo_tx;
f = [-Fs/2:delta_f:Fs/2-delta_f];

#* Geração do clock *
f_clk = Rb;
pulso_clk = ((square(2*pi*f_clk*t))+1)*(0.5);

#* Geração da sequência de informação binária *
info_bin = randint(1,Rb*periodo_tx,M);
info_t = upsamplefill(info_bin, N-1, true); %matlab função rectpulse
info_TTL = info_t*5;
#* Geração da forma de onda NRZ polar
info_NRZ = info_t*2*A-A;

#* Geração da forma de onda Manchester
info_Manchester = xor(info_t,pulso_clk)*2*A-A;

#* Figura domínio do tempo *
figure(1)
subplot(411)
plot(t,pulso_clk);
title('CLOCK')
ylabel('Amplitude')
axis([0 10*Tb -0.5 1.5])
subplot(412)
plot(t,info_TTL);
title('DADO - TTL')
ylabel('Amplitude')
axis([0 10*Tb -.5 5.5])
subplot(413)
plot(t,info_NRZ);
title('NRZ')
ylabel('Amplitude')
axis([0 10*Tb -A*1.5 A*1.5])
subplot(414)
plot(t,info_Manchester);
title('MANCHESTER')
ylabel('Amplitude')
xlabel('tempo')
axis([0 10*Tb -A*1.5 A*1.5])

#* Autocorrelação e Densidade Espectral *
Rx_NRZ = xcorr(info_NRZ)/length(info_t);
Gx_NRZ = fftshift(fft(Rx_NRZ));
Rx_Manchester = xcorr(info_Manchester)/length(info_t);
Gx_Manchester = fftshift(fft(Rx_Manchester));

#* Figura no domínio da frequência *
figure(2)
subplot(211)
f_aux = [-Fs/2:delta_f/2:Fs/2-delta_f];
plot(f_aux, abs(Gx_NRZ)/length(Rx_NRZ))
xlabel('frequencia')
ylabel('Densidade espectral')
xlim([-5*Rb 5*Rb])
subplot(212)
plot(f_aux,abs(Gx_Manchester)/length(Rx_Manchester))
xlim([-5*Rb 5*Rb])
xlabel('frequencia')
ylabel('Densidade espectral')

#* Transmissão NRZ por canal livre de interferência *
sinal_tx = info_NRZ;

#* Detecção NRZ com ruído Gaussiano *
limiar = 0;
var_ruido = 2; # Variância do ruído
ruido = sqrt(var_ruido)*randn(1,length(sinal_tx));
sinal_rx = sinal_tx + ruido;
sinal_det = sinal_rx(N/2:N:end); #Coletando amostra no meio do pulso
info_rec = sinal_det > limiar;
n_erro = sum(xor(info_bin, info_rec));
Pb = n_erro/(Rb*periodo_tx)
a1 = A;
a2 = -A;
V_dif = a1-a2
sigma = std(ruido)
Pb_teorico = qfunc((a1-a2)/(2*sigma))

figure(3)
subplot(211)
plot(t,sinal_tx)
title('SINAL NRZ TX')
xlabel('tempo')
ylabel('Amplitude')
axis([0 10*Tb -A*1.2 A*1.2])
subplot(212)
plot(t,sinal_rx)
hold on
plot(t,sinal_tx)
title('SINAL NRZ RX')
xlabel('tempo')
ylabel('Amplitude')
xlim([0 10*Tb])