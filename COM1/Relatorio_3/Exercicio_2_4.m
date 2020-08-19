clear all;
close all;
clc;

% Plote as expressões teóricas de Pb das sinalizações 
% Polar e Bipolar (eq. 3.73 e 3.76) e compare-as com os 
% resultados da simulação do item 3. 
% Observe que as simulações anteriores estão em função 
% de SNR e as expressões em função de Eb/No!

N = 5; %fator de super amostragem
A = 1; %amplitude 1v
Rb = 1e4; %taxa de transmiss?o
Fs = N*Rb; %frequ?ncia de amostragem
passo = 1/Fs; %passo no tempo
t = [0 : passo : 1-passo]; %vetor no tempo
filtro_tx = ones(1,N); %filtro formatador
snr = 20; %definindo snr m?ximo

%sinal tx
info = randint(1, Rb);
info_uni = A.*info;
info_bi = (2.*info)-1;

%Limiares
limiar_uni = A/2;
limiar_bi = (min(info_bi) + max(info_bi))/2;

%super amostragem dos sinais
infoup_uni = upsample(info_uni,N);
infoup_bi = upsample(info_bi,N);
 
%filtragem dos sinais no filtro formatador
sinal_tx_uni = filter(filtro_tx, 1, infoup_uni);
sinal_tx_bi = filter(filtro_tx, 1, infoup_bi);

%filtro casado
filtro_rx = fliplr(filtro_tx);
 
for i = 0 : snr
    
    EbNo = i;
    
    %inserindo ruidos em ambos os sinais
    sinal_rx_uni = awgn(sinal_tx_uni, i);
    sinal_rx_bi = awgn(sinal_tx_bi, i);
    
    %filtrando os sinais
    sinal_rx_uni_FC = filter(filtro_rx, 1, sinal_rx_uni)/N;
    sinal_rx_bi_FC = filter(filtro_rx, 1, sinal_rx_bi)/N;
    
    %sinal detectado
    sinal_rx_dec_uni = sinal_rx_uni_FC(N : N : end);
    sinal_rx_dec_bi = sinal_rx_bi_FC(N : N : end);
    
    %erros
    info_est_rx_uni = sinal_rx_dec_uni > limiar_uni;
    info_est_rx_bi = sinal_rx_dec_bi > limiar_bi;
    
    %Pb na pr?tica
    Pb_uni_prat(i+1) = sum(xor(info, info_est_rx_uni))/length(info);
    Pb_bi_prat(i+1) = sum(xor(info, info_est_rx_bi))/length(info);
    
    %determinando Eb/No e 2*Eb/No
    EbNo_uni = 10^(EbNo/10);
    EbNo_bi = 2*10^(EbNo/10);
    
    %probabilidade de erro te?rico
    Pb_uni_teor(i+1) = qfunc(sqrt(EbNo_uni));
    Pb_bi_teor(i+1) = qfunc(sqrt(EbNo_bi));
    
end

%plotando Pb vs SNR
 figure(1)
 semilogy([0:snr], Pb_uni_teor);
 hold on;
 semilogy([0:snr], Pb_bi_teor);
 xlabel('SNR');
 ylabel('Probabilidade de erro de bit')
 legend('Unipolar', 'Bipolar');
 title('Probabilidade de Erro Teorico')