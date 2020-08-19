clear all;
close all;
clc;

% Transmissão utilizando sinalização NRZ unipolar
% com amplitude de 1V e 2V, ambos sem a utilização de filtro casado;

N = 5; %fator de super amostragem
A1 = 1; %amplitude 1v
A2 = 2; %amplitude 2v
l1 = A1/2; %limiar 1
l2 = A2/2; %limiar 2
Rb = 1e4; %taxa de transmiss?o
Fs = N*Rb; %frequ?ncia de amostragem
passo = 1/Fs; %passo no tempo
t = [0 : passo : 1-passo]; %vetor no tempo
filtro_tx = ones(1,N); %filtro formatador
snr = 20; %definindo snr m?ximo

%sinal tx
info = randint(1, Rb);
info1 = A1.*info;
info2 = A2.*info;

%super amostragem dos sinais
info1up = upsample(info1,N);
info2up = upsample(info2,N);

%filtragem dos sinais no filtro formatador
sinal_tx1 = filter(filtro_tx, 1, info1up);
sinal_tx2 = filter(filtro_tx, 1, info2up);

for i = 0 : snr
    
    %inserindo ruidos em ambos os sinais
    sinal_rx1 = awgn(sinal_tx1, i);
    sinal_rx2 = awgn(sinal_tx2, i);
    
    %sinal detectado
    sinal_rx1_dec = sinal_rx1(N/2 : N : end);
    sinal_rx2_dec = sinal_rx2(N/2 : N : end);
    
    %erros
    info_est_rx1 = sinal_rx1_dec > l1;
    info_est_rx2 = sinal_rx2_dec > l2;
    
    %Pb
    Pb1(i+1) = sum(xor(info, info_est_rx1))/length(info);
    Pb2(i+1) = sum(xor(info, info_est_rx2))/length(info)
    
end

%plotando Pb vs SNR
figure(1)
semilogy([0:snr], Pb1);
hold on;
semilogy([0:snr], Pb2);
xlabel('SNR');
ylabel('Probabilidade de erro de bit')
legend('Unipolar 1V', 'Unipolar 2V');