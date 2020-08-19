clear all;
close all;
clc;

N = 200;
limiar = 1/2;
filtro_tx = [ones(1,N) zeros(1,N)];
filtro = ones(1,N);
info = [0 1 1 0 1 0 1 1 0 1 0];
info_up = upsample(info, N); %super amostrando sinal
sinal_tx = filter(filtro, 1, info_up);

figure(1)
subplot(411)
stem(info);
title('Sinal Tx amostrado');
ylim([-0.2 1.2])

subplot(412)
stem(info_up);
title('Sinal Tx super-amostrado');
ylim([-0.2 1.2])

subplot(413)
stem(filtro_tx)
title('Filtro Tx');
ylim([0 1.2])

subplot(414)
plot(sinal_tx);
title('Sinal Tx');
ylim([-0.2 1.2])

%acrescentando ruido e enviando sinal
SNR = 10; %10 vezez menor
sinal_rx = awgn(sinal_tx, SNR);

figure(2)
subplot(411)
plot(sinal_rx);
title('Sinal Rx');
%grid on;
ylim([-1 2])

filtro_rx = fliplr(filtro);

sinal_rx_FC = filter(filtro_rx, 1, sinal_rx)/N;
sinal_det_FC = sinal_rx_FC(N:N:end);
info_est_FC = sinal_det_FC > limiar;

subplot(412)
stem(info_est_FC)
title('Sinal Filtrado')
ylim([-0.2 1.2])

sinal_SF = sinal_rx(N:N:end);
info_est = sinal_SF > limiar;

filtro_rx = [filtro_rx zeros(1,5)];
subplot(413)
stem(info_est)
title('Sem Filtro')
ylim([-0.2 1.2])

subplot(414)
stem(filtro_rx);
title('Filtro Casado')
ylim([-0.2 1.2])