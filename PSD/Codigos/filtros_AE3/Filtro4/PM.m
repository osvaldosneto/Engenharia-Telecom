clc
close all
clear all

% Filtro BS FIR (Parks McClellan)

% Dados iniciais
f1 = 1200; 
f2 = 2000; 
f3 = 3000;
f4 = 3800;
fa = 8000;
fN = fa/2;
Ap = 3; 
Apa = Ap/2;
As = 40;
Gtopo = 20;
Gp = 17;
Gs = -20;

fp1 = f1;
fs1 = f2;
fs2 = f3;
fp2 = f4;
ws1 = fs1/fN;
wp1 = fp1/fN;
wp2 = fp2/fN;
ws2 = fs2/fN;

fv = [wp1 wp1 0 0 ws1 ws1 ws2 ws2 1 1 wp2 wp2];
Amin = As+100;
mv = [-Amin -Ap/2 -Ap/2 Ap/2 Ap/2 -As -As Ap/2 Ap/2 -Ap/2 -Ap/2 -Amin];

%% Primeira etapa: Estimativa do filtro.

fcuts = [fp1 fs1 fs2 fp2];
a = [1 0 1];
dev = [(10^(Apa/20)-1)/(10^(Apa/20)+1) 10^(-As/20) (10^(Apa/20)-1)/(10^(Apa/20)+1)];

[n,fo,ao,w] = firpmord(fcuts,a,dev,fa);
b = firpm(n,fo,ao,w);
fvtool(b)
title(['Filtro de ordem estimada BS FIR com algoritmo PM de ordem ', num2str(n)]);

%% Segunda etapa: Ajuste dos pesos e da ordem

n = 16;
w = [1 8 1]';
b = firpm(n,fo,ao,w);
fvtool(b)
title(['Filtro com ajuste de ordem BS FIR com algoritmo PM de ordem ', num2str(n)]);
 
%% Terceira etapa: Ajuste do ganho de topo e nova mascara

fva = [wp1 wp1 0 0 ws1 ws1 ws2 ws2 1 1 wp2 wp2];
Amin_a = As+15;
mva = [-Amin Gp Gp Gtopo Gtopo Gs Gs Gtopo Gtopo Gp Gp -Amin];

b = b/(10^(0.55/20));
b_ajustado = b*10^(Gtopo/20);
fvtool(b_ajustado)
title(['Filtro com ajuste de ganho de topo BS FIR com algoritmo PM de ordem ', num2str(n)]);

%% Resultado final

% Magnitude
subplot(4,2,1:4)
[H, W] = freqz(b_ajustado);
plot(W*fa/2/pi,20*log10(abs(H))); grid on;
xlim([0 fN])
ylim([-Amin_a Gtopo+5])
title(['Resultado final Filtro BS FIR utilizando o algoritmo de Parks McClellan n=', num2str(n)])
ylabel('dB')

line([0 fs1],[Gtopo Gtopo],'Color','red')
line([fs1 fs1],[Gs Gtopo],'Color','red')
line([fs1 fs2],[Gs Gs],'Color','red')
line([fs2 fs2],[Gs Gtopo],'Color','red')
line([fs2 fN],[Gtopo Gtopo],'Color','red')

line([0 fp1],[Gp Gp],'Color','red')
line([fp1 fp1],[-Amin_a Gp],'Color','red')

line([fp2 fN],[Gp Gp],'Color','red')
line([fp2 fp2],[-Amin_a Gp],'Color','red')

% Detalhe banda de passagem
subplot(4,2,5:6)
plot(W*fa/2/pi,20*log10(abs(H))); grid on;
xlim([0 fN])
ylim([Gp-5 Gp+5])
ylabel('dB')

line([0 fs1],[Gtopo Gtopo],'Color','red')
line([fs1 fs1],[Gs Gtopo],'Color','red')
line([fs1 fs2],[Gs Gs],'Color','red')
line([fs2 fs2],[Gs Gtopo],'Color','red')
line([fs2 fN],[Gtopo Gtopo],'Color','red')

line([0 fp1],[Gp Gp],'Color','red')
line([fp1 fp1],[-Amin_a Gp],'Color','red')

line([fp2 fN],[Gp Gp],'Color','red')
line([fp2 fp2],[-Amin_a Gp],'Color','red')

% Detalhe banda de rejeicao
subplot(4,2,7:8)
plot(W*fa/2/pi,20*log10(abs(H))); grid on;
xlim([0 fN])
ylim([Gs-10 Gs+10])
ylabel('dB')
xlabel('Frequencia (Hz)')

line([0 fs1],[Gtopo Gtopo],'Color','red')
line([fs1 fs1],[Gs Gtopo],'Color','red')
line([fs1 fs2],[Gs Gs],'Color','red')
line([fs2 fs2],[Gs Gtopo],'Color','red')
line([fs2 fN],[Gtopo Gtopo],'Color','red')

line([0 fp1],[Gp Gp],'Color','red')
line([fp1 fp1],[-Amin_a Gp],'Color','red')

line([fp2 fN],[Gp Gp],'Color','red')
line([fp2 fp2],[-Amin_a Gp],'Color','red')
