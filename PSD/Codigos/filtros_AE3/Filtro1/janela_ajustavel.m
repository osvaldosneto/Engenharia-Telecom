clear all
close all
clc

% Filtro LP FIR (Janela Ajustavel - Kaiser)

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

%% Primeira etapa: Janela de Kaiser

Dw = abs(ws-wp);
alpha = As-Ap;
beta = (0.5842*(alpha-21)^0.4)+(0.07886*(alpha-21));
n = ceil(((alpha-8)/(2.285*Dw*pi))+1);
L = n+1;
wvtool(kaiser(L,beta));
title(['Janela de Kaiser com ordem estimada de ', num2str(n)]);

%% Segunda etapa: Visualizando o filtro com ordem estimada

ftype = 'low';
wc = (wp+ws)/2;
h_low = fir1(n,wc,ftype,kaiser(L,beta),'noscale');
fvtool(h_low,1)
title(['Filtro sem ajuste de banda LP FIR com janela de Kaiser de ordem ', num2str(n)]);

%% Terceira etapa: Ajustes de largura de banda e de ordem

n = n-2;
L = n+1;

h_low = fir1(n,wc,ftype,kaiser(L,beta),'noscale');
fvtool(h_low,1)
title(['Filtro sem ajuste de banda LP FIR com janela de Kaiser de ordem ', num2str(n)]);

% % Primeiro ajuste
wpm = 0.216;
wsm = 0.505;
Dwp = wpm-wp;
Dws = wsm-ws;
Dwm = (Dwp-Dws)/2;
wc = (wp+ws)/2-Dwm;
h_low = fir1(n,wc,ftype,kaiser(L,beta),'noscale');
fvtool(h_low,1)
title(['Filtro com ajuste de banda LP FIR com janela de Kaiser de ordem ', num2str(n)]);
 
% % Segundo ajuste
wsm2 = 0.4768;
Dws2 = ws-wsm2;
wc2 = wc+Dws2;
h_low = fir1(n,wc2,ftype,kaiser(L,beta),'noscale');
fvtool(h_low,1)
title(['Filtro com ajuste de banda LP FIR com janela de Kaiser de ordem ', num2str(n)]);
 
%% Quarta etapa: Ajuste do ganho de topo e nova mascara

fva = [wp wp 0 0 ws ws 1];
Amin_a = -Gs+100;
mva = [-Amin_a Gp Gp Gtopo Gtopo Gs Gs];

h_low = h_low/(10^(0.048/20));
h_low_ajustado = h_low*10^(Gtopo/20);
fvtool(h_low_ajustado,1)
title(['Filtro com ajuste de banda e de ganho de topo LP FIR com janela de Kaiser de ordem ', num2str(n)]);

