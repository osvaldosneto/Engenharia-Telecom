clear all
close all
clc

% Filtro LP FIR (Parks McClellan)

% Dados iniciais
f1 = 600; 
f2 = 2000; 
fa = 8000;
fN = fa/2;
Ap = 1; 
As = 45;
Apa = Ap/2;
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

%% Primeira etapa: Estimativa do filtro

f = [fp fs];    
a = [1 0];        
dev = [(10^(Apa/20)-1)/(10^(Apa/20)+1)  10^(-As/20)]; 
[n,fo,ao,w] = firpmord(f,a,dev,fa);
b = firpm(n,fo,ao,w);
fvtool(b)
title(['Filtro de ordem estimada LP FIR (Parks McClellan) de ordem ', num2str(n)]);

%% Segunda etapa: Ajuste dos pesos e da ordem

n = 11;
w = [1 5]';
b = firpm(n,fo,ao,w);
fvtool(b)
title(['Filtro com ajuste de ordem LP FIR (Parks McClellan) de ordem ', num2str(n)]);

%% Terceira etapa: Ajuste do ganho de topo e nova mascara

fva = [wp wp 0 0 ws ws 1];
Amin_a = -Gs+100;
mva = [-Amin_a Gp Gp Gtopo Gtopo Gs Gs];

b = b/(10^(0.1812/20));
b_ajustado = b*10^(Gtopo/20);
fvtool(b_ajustado)
title(['Filtro com ajuste de ganho de topo LP FIR (Parks McClellan) de ordem ', num2str(n)]);






