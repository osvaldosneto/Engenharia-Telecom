clear all
close all
clc

% Filtro HP FIR (Parks McClellan)

% Dados iniciais
f1 = 600; 
f2 = 2000; 
fa = 8000;
fN = fa/2;
Ap = 1; 
As = 45;
Apa = Ap/2;
Gtopo = 10;
Gp = 9;
Gs = -35;

fs = f1;
fp = f2;
wp = fp/fN;
ws = fs/fN;

fv = [0 ws ws 1 1 wp wp];
Amin = As+40;
mv = [-As -As Ap/2 Ap/2 -Ap/2 -Ap/2 -Amin];

%% Primeira etapa: Estimativa do filtro

f = [fs fp];    
a = [0 1];        
dev = [10^(-As/20) (10^(Apa/20)-1)/(10^(Apa/20)+1)]; 
[n,fo,ao,w] = firpmord(f,a,dev,fa);
b = firpm(n,fo,ao,w);
fvtool(b)
title(['Filtro de ordem estimada HP FIR (Parks McClellan) de ordem ', num2str(n)]);

%% Segunda etapa: Ajuste dos pesos e da ordem

n = 12;
w = [3 1]';
b = firpm(n,fo,ao,w);
fvtool(b)
title(['Filtro com ajuste de ordem HP FIR (Parks McClellan) de ordem ', num2str(n)]);

%% Terceira etapa: Ajuste do ganho de topo e nova mascara

fva = [wp wp 1 1 ws ws 0];
Amin_a = -Gs+100;
mva = [-Amin_a Gp Gp Gtopo Gtopo Gs Gs];

b = b/(10^(0.139/20));
b_ajustado = b*10^(Gtopo/20);
fvtool(b_ajustado)
title(['Filtro com ajuste de ganho de topo HP FIR (Parks McClellan) de ordem ', num2str(n)]);

%% Resultado final

Magnitude
subplot(4,1,[1 2])
[H, W] = freqz(b_ajustado);
plot(W*fa/2/pi,20*log10(abs(H))); grid on;
xlim([0 2*fp])
ylim([-Amin Gtopo+5])
title(['Resultado final Filtro HP FIR utilizando o algoritmo de Parks McClellan n=', num2str(n)])
ylabel('dB')

line([fp fp],[-Amin Gp],'Color','red')
line([fp 10e3],[Gp Gp],'Color','red')
line([10 fs],[Gs Gs],'Color','red')
line([fs fs],[Gs Gtopo],'Color','red')
line([fs 10e3],[Gtopo Gtopo],'Color','red')

% Detalhe banda de passagem
subplot(413)
plot(W*fa/2/pi,20*log10(abs(H))); grid on;
xlim([0 2*fp])
ylim([Gp-0.05 Gtopo+0.05])
ylabel('dB')

line([fp fp],[-Amin Gp],'Color','red')
line([fp 10e3],[Gp Gp],'Color','red')
line([10 fs],[Gs Gs],'Color','red')
line([fs fs],[Gs Gtopo],'Color','red')
line([fs 10e3],[Gtopo Gtopo],'Color','red')

% Detalhe banda de rejeicao
subplot(414)
plot(W*fa/2/pi,20*log10(abs(H))); grid on;
xlim([0 2*fp])
ylim([Gs-10 Gs+10])
ylabel('dB')
xlabel('Frequencia (Hz)')

line([fp fp],[-Amin Gp],'Color','red')
line([fp 10e3],[Gp Gp],'Color','red')
line([10 fs],[Gs Gs],'Color','red')
line([fs fs],[Gs Gtopo],'Color','red')
line([fs 10e3],[Gtopo Gtopo],'Color','red')








