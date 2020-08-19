clear all;
close all;
clc;

% Transmissão utilizando sinalização NRZ unipolar
% com amplitude de 1V, com e sem filtro casado;


N = 5; %fator de super amostragem
A = 1; %amplitude 1v
limiar = A/2; %limiar 1
Rb = 1e4; %taxa de transmiss?o
Fs = N*Rb; %frequ?ncia de amostragem
passo = 1/Fs; %passo no tempo
t = [0 : passo : 1-passo]; %vetor no tempo
filtro_tx = ones(1,N); %filtro formatador
snr = 20; %definindo snr m?ximo

%sinal tx
info = randint(1, Rb);
info1 = A.*info;

%super amostragem dos sinais
infoup = upsample(info1,N);

%filtragem dos sinais no filtro formatador
sinal_tx = filter(filtro_tx, 1, infoup);

%filtro casado
filtro_rx = fliplr(filtro_tx);

for i = 0 : snr
    
    %inserindo ruidos
    sinal_rx = awgn(sinal_tx, i);
    
    %filtrando o sinal
    sinal_rx_FC = filter(filtro_rx, 1, sinal_rx)/N;
    
    %sinal detectado
    sinal_rx_dec_FC = sinal_rx_FC(N : N : end);
    sinal_rx_dec = sinal_rx(N/2 : N : end);
    
    %erros
    info_est_rx_FC = sinal_rx_dec_FC > limiar;
    info_est_rx = sinal_rx_dec > limiar;
    
    %Pb
    Pb_FC(i+1) = sum(xor(info, info_est_rx_FC))/length(info);
    Pb(i+1) = sum(xor(info, info_est_rx))/length(info);
    
end

% figure(1)
% subplot(211)
% freqz(filtro_tx)
% figure(2)
% freqz(filtro_rx)

%plotando Pb vs SNR
figure(1)
semilogy([0:snr], Pb_FC);
hold on;
semilogy([0:snr], Pb);
xlabel('SNR');
ylabel('Probabilidade de erro de bit')
legend('Unipolar 1V - Filtro Casado', 'Unipolar 1V - Sem Filtro');