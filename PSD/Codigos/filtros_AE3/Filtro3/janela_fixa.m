clc
close all
clear all

% Filtro BP FIR (Janela Fixa)

% Dados iniciais
f1 = 1200; 
f2 = 2000; 
f3 = 3000;
f4 = 3800;
fa = 8000;
fN = fa/2;
Ap = 3; 
As = 40;
Gtopo = 20;
Gp = 17;
Gs = -20;

fs1 = f1;
fp1 = f2;
fp2 = f3;
fs2 = f4;
ws1 = fs1/fN;
wp1 = fp1/fN;
wp2 = fp2/fN;
ws2 = fs2/fN;

fv = [0 ws1 ws1 ws2 ws2 1 1 wp2 wp2 wp1 wp1];
Amin = As+100;
mv = [-As -As Ap/2 Ap/2 -As -As -Amin -Amin -Ap/2 -Ap/2 -Amin];

%% Primeira etapa: Chute inicial da ordem e analise de janelas.

% Valor inicial de Wc1 e Wc2 (sem ajuste)
wc1 = (ws1+wp1)/2;
wc2 = (ws2+wp2)/2;

N = 29;
M = N/2;
CBP = wc2*sinc(wc2*(-M:M))-wc1*sinc(wc1*(-M:M));
bTri = CBP.*triang(2*M+1)';
bHamming = CBP.*hamming(2*M+1)';
bBlackmanharris = CBP.*blackmanharris(2*M+1)';
fvtool(bTri,1,bHamming,1,bBlackmanharris,1);
legend('Triangular', 'Hamming', 'Blackmanharris');
title(['Filtro BP FIR com diferentes janelas de ordem ', num2str(N)]);

%% Segunda etapa: Escolha da janela e ajuste na ordem

N = 30;
M = N/2;
CBP = wc2*sinc(wc2*(-M:M))-wc1*sinc(wc1*(-M:M));
bHamming = CBP.*hamming(2*M+1)';
fvtool(bHamming,1);
title(['Filtro sem ajuste de largura de banda BP FIR com janela Hamming de ordem ', num2str(N)]);

ws1m = 0.3015;
wp1m = 0.427;
wp2m = 0.8231;
ws2m = 0.9485;
Dws1 = ws1m-ws1;
Dwp1 = wp1m-wp1;
Dwp2 = wp2m-wp2;
Dws2 = ws2m-ws2;
Dwm = Dws2/2;
wc1 = (ws1+wp1)/2+Dwm;
wc2 = (ws2+wp2)/2+Dwm;

CBP = wc2*sinc(wc2*(-M:M))-wc1*sinc(wc1*(-M:M));
bHamming = CBP.*hamming(2*M+1)';
fvtool(bHamming,1);
title(['Filtro com ajuste de largura de banda BP FIR com janela Hamming de ordem ', num2str(N)]);

%% Terceira etapa: Ajuste de ganho de topo e nova mascara

fva = [0 ws1 ws1 ws2 ws2 1 1 wp2 wp2 wp1 wp1];
Amin_a = -Gs+100;
mva = [Gs Gs Gtopo Gtopo Gs Gs -Amin_a -Amin_a Gp Gp -Amin_a];

bHamming = bHamming/(10^(0.034/20));
bHamming_ajustado = bHamming*10^(Gtopo/20);
fvtool(bHamming_ajustado,1);
title(['Filtro com ajuste de largura de banda e de ganho LP FIR com janela Hamming de ordem ', num2str(N)]);






