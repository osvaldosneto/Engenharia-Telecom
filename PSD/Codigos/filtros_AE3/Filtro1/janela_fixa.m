clear all
close all
clc

% Filtro LP FIR Tipo 1 (Janela Fixa)

% Dados iniciais
f1 = 600; 
f2 = 2000; 
fa = 8000;
fN = fa/2;
Ap = 1; 
As = 45;
Gtopo = 5;
Gp = 4;
Gs = -40;

fp = f1;
fs = f2;
wp = fp/fN;
ws = fs/fN;

fv = [wp wp 0 0 ws ws 1];
Amin = As+100;
mv = [-Amin -Ap/2 -Ap/2 Ap/2 Ap/2 -As -As];

%% Primeira etapa: Chute inicial da ordem e analise de janelas.

% Valor inicial de Wc (sem ajuste)
wc = (ws+wp)/2;

N = 14;
M = N/2;
CLP = wc*sinc(wc*(-M:M));
bRet = CLP;
bHamming = CLP.*hamming(2*M+1)';
bBlackman = CLP.*blackman(2*M+1)';
fvtool(bRet,1,bHamming,1,bBlackman,1);
legend('rectwin', 'Hamming', 'Blackman');
title(['Filtro LP FIR com diferentes janelas de ordem ', num2str(N)]);

%% Segunda etapa: Escolha da janela e analise da ordem inicial

N = 14;
bHamming = CLP.*hamming(2*M+1)';
fvtool(bHamming,1);
title(['Filtro sem ajuste de largura de banda LP FIR com janela Hamming de ordem ', num2str(N)]);

wpm = 0.198;
wsm = 0.557;  
Dwp = wpm - wp;
Dws = wsm - ws;
Dwm = -Dws;

wc = (ws+wp)/2+Dwm;

CLP = wc*sinc(wc*(-M:M));
bHamming = CLP.*hamming(2*M+1)';
fvtool(bHamming,1);
title(['Filtro sem ajuste de largura de banda LP FIR com janela Hamming de ordem ', num2str(N)]);


%% Terceira etapa: Ajuste da largura de banda e da ordem
wc = (ws+wp)/2;
N = 16;
M = N/2;

CLP = wc*sinc(wc*(-M:M));
bHamming = CLP.*hamming(2*M+1)';
fvtool(bHamming,1);
title(['Filtro sem ajuste de largura de banda LP FIR com janela Hamming de ordem ', num2str(N)]);

% Primeiro ajuste
wpm = 0.214;
wsm = 0.5285;  
Dwp = wpm - wp;
Dws = wsm - ws;
Dwm = -Dws;

wc = (ws+wp)/2+Dwm;

CLP = wc*sinc(wc*(-M:M));
bHamming = CLP.*hamming(2*M+1)';
fvtool(bHamming,1);
title(['Filtro com primeiro ajuste de largura de banda LP FIR com janela Hamming de ordem ', num2str(N)]);

% Segundo ajuste
wpm = 0.186;
wsm = 0.5005; 
Dwp = wpm - wp;
Dws = wsm - ws;
Dwm = -Dws;

wc= wc+Dwm;

CLP = wc*sinc(wc*(-M:M));
bHamming = CLP.*hamming(2*M+1)';
fvtool(bHamming,1);
title(['Filtro com segundo ajuste de largura de banda LP FIR com janela Hamming de ordem ', num2str(N)]);

%% Quarta etapa: Ajuste de ganho de topo e nova mascara

fva = [wp wp 0 0 ws ws 1];
Amin_a = -Gs+100;
mva = [-Amin_a Gp Gp Gtopo Gtopo Gs Gs];

bHamming = bHamming/(10^(0.0434/20));
bHamming_ajustado = bHamming*10^(Gtopo/20);
fvtool(bHamming_ajustado,1);
title(['Filtro com ajuste de largura de banda e de ganho LP FIR com janela Hamming de ordem ', num2str(N)]);








