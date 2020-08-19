clear all
close all
clc

% Comparacao dos filtros BP com janela fixa, ajustavel e Parks McClellan

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

fs1 = f1;
fp1 = f2;
fp2 = f3;
fs2 = f4;
ws1 = fs1/fN;
wp1 = fp1/fN;
wp2 = fp2/fN;
ws2 = fs2/fN;

fva = [0 ws1 ws1 ws2 ws2 1 1 wp2 wp2 wp1 wp1];
Amin_a = -Gs+80;
mva = [Gs Gs Gtopo Gtopo Gs Gs -Amin_a -Amin_a Gp Gp -Amin_a];


%% Janela Fixa 
ws2m = 0.9485;
Dws2 = ws2m-ws2;
Dwm = Dws2/2;
wc1 = (ws1+wp1)/2+Dwm;
wc2 = (ws2+wp2)/2+Dwm;
n_fixa = 30;
M = n_fixa/2;
CBP = wc2*sinc(wc2*(-M:M))-wc1*sinc(wc1*(-M:M));
bHamming = CBP.*hamming(2*M+1)';
bHamming = bHamming/(10^(0.034/20));
bHamming_ajustado = bHamming*10^(Gtopo/20);

%% Janela ajustavel
fcuts = [fs1 fp1 fp2 fs2];
a = [0 1 0];
dev = [10^(-As/20) (10^(Apa/20)-1)/(10^(Apa/20)+1) 10^(-As/20)];
[n,Wn,beta,ftype] = kaiserord(fcuts,a,dev,fa);
n_ajustavel = n+1;
L = n_ajustavel+1;
bKaiser = fir1(n_ajustavel,Wn,ftype,kaiser(L,beta),'noscale');
bKaiser = bKaiser/(10^(0.06/20));
bKaiser_ajustado = bKaiser*10^(Gtopo/20);

%% Parks McClellan
fcuts = [fs1 fp1 fp2 fs2];
a = [0 1 0];
dev = [10^(-As/20) (10^(Apa/20)-1)/(10^(Apa/20)+1) 10^(-As/20)];
[n,fo,ao,w] = firpmord(fcuts,a,dev,fa);
n_PM = 15;
w = [5 1 5]';
bPM = firpm(n_PM,fo,ao,w);
bPM = bPM/(10^(0.355/20));
bPM_ajustado = bPM*10^(Gtopo/20);

%% Comparando os filtros

% Magnitude
subplot(4,2,1:4)
[H1,w1] = freqz(bHamming_ajustado);
plot(w1*fa/2/pi,20*log10(abs(H1))); grid on;
xlim([0 fN])
ylim([-Amin_a Gtopo+5])
hold on
[H2,w2] = freqz(bKaiser_ajustado);
plot(w2*fa/2/pi,20*log10(abs(H2))); grid on;
hold on
[H3,w3] = freqz(bPM_ajustado);
plot(w3*fa/2/pi,20*log10(abs(H3))); grid on;
legend(['Hamming n = ', num2str(n_fixa)],['Kaiser n = ', num2str(n_ajustavel)],['Parks McClellan n = ', num2str(n_PM)]);
title('Resultado final dos filtros BP projetados')
ylabel('dB')

line([0 fs1],[Gs Gs],'Color','red')
line([fs1 fs1],[Gs Gtopo],'Color','red')
line([fs1 fs2],[Gtopo Gtopo],'Color','red')
line([fs2 fs2],[Gtopo Gs],'Color','red')
line([fs2 fN],[Gs Gs],'Color','red')

line([fp1 fp1],[-Amin_a Gp],'Color','red')
line([fp1 fp2],[Gp Gp],'Color','red')
line([fp2 fp2],[-Amin_a Gp],'Color','red')

% Detalhe banda de passagem
subplot(4,2,5:6)
plot(w1*fa/2/pi,20*log10(abs(H1))); grid on;
xlim([0 fN])
ylim([Gp-1 Gtopo+1])
hold on
plot(w2*fa/2/pi,20*log10(abs(H2))); grid on;
hold on
plot(w3*fa/2/pi,20*log10(abs(H3))); grid on;
ylabel('dB')

line([0 fs1],[Gs Gs],'Color','red')
line([fs1 fs1],[Gs Gtopo],'Color','red')
line([fs1 fs2],[Gtopo Gtopo],'Color','red')
line([fs2 fs2],[Gtopo Gs],'Color','red')
line([fs2 fN],[Gs Gs],'Color','red')

line([fp1 fp1],[-Amin_a Gp],'Color','red')
line([fp1 fp2],[Gp Gp],'Color','red')
line([fp2 fp2],[-Amin_a Gp],'Color','red')

% Detalhe banda de rejeicao 
subplot(4,2,7:8)
plot(w1*fa/2/pi,20*log10(abs(H1))); grid on;
xlim([0 fN])
ylim([Gs-10 Gs+10])
hold on
plot(w2*fa/2/pi,20*log10(abs(H2))); grid on;
hold on
plot(w3*fa/2/pi,20*log10(abs(H3))); grid on;
ylabel('dB')
xlabel('Frequencia (Hz)')

line([0 fs1],[Gs Gs],'Color','red')
line([fs1 fs1],[Gs Gtopo],'Color','red')
line([fs1 fs2],[Gtopo Gtopo],'Color','red')
line([fs2 fs2],[Gtopo Gs],'Color','red')
line([fs2 fN],[Gs Gs],'Color','red')

line([fp1 fp1],[-Amin_a Gp],'Color','red')
line([fp1 fp2],[Gp Gp],'Color','red')
line([fp2 fp2],[-Amin_a Gp],'Color','red')
