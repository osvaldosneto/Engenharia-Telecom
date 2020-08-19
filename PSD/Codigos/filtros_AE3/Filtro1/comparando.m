clear all
close all
clc

% Comparacao dos filtros LP com janela fixa, ajustavel e Parks McClellan

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

fva = [wp wp 0 0 ws ws 1];
Amin_a = -Gs+30;
mva = [-Amin_a Gp Gp Gtopo Gtopo Gs Gs];

%% Janela Fixa
wc = (ws+wp)/2;
n_fixa = 16;
M = n_fixa/2;

CLP = wc*sinc(wc*(-M:M));
bHamming = CLP.*hamming(2*M+1)';

% Primeiro ajuste
wpm = 0.214;
wsm = 0.5285;  
Dwp = wpm - wp;
Dws = wsm - ws;
Dwm = -Dws;
wc = (ws+wp)/2+Dwm;
CLP = wc*sinc(wc*(-M:M));
bHamming = CLP.*hamming(2*M+1)';

% Segundo ajuste
wpm = 0.186;
wsm = 0.5005; 
Dwp = wpm - wp;
Dws = wsm - ws;
Dwm = -Dws;
wc= wc+Dwm;
CLP = wc*sinc(wc*(-M:M));
bHamming = CLP.*hamming(2*M+1)';

bHamming = bHamming/(10^(0.0434/20));
bHamming_ajustado = bHamming*10^(Gtopo/20);

%% Janela Ajustavel

Dw = abs(ws-wp);
alpha = As-Ap;
beta = (0.5842*(alpha-21)^0.4)+(0.07886*(alpha-21));
n = ceil(((alpha-8)/(2.285*Dw*pi))+1);

ftype = 'low';
n_ajustavel = n-2;
L = n_ajustavel+1;

wpm = 0.216;
wsm = 0.505;
Dwp = wpm-wp;
Dws = wsm-ws;
Dwm = (Dwp-Dws)/2;
wc = (wp+ws)/2-Dwm;

wsm2 = 0.4768;
Dws2 = ws-wsm2;
wc2 = wc+Dws2;
h_low = fir1(n_ajustavel,wc2,ftype,kaiser(L,beta),'noscale');

h_low = h_low/(10^(0.048/20));
kaiser_ajustado = h_low*10^(Gtopo/20);

%% Parks McClellan

f = [fp fs];    
a = [1 0];        
dev = [(10^(Apa/20)-1)/(10^(Apa/20)+1)  10^(-As/20)]; 
[n,fo,ao,w] = firpmord(f,a,dev,fa);
n_PM = 11;
w = [1 5]';
b_PM = firpm(n_PM,fo,ao,w);

b_PM = b_PM/(10^(0.1812/20));
PM_ajustado = b_PM*10^(Gtopo/20);

%% Comparando os filtros

% Magnitude
subplot(4,1,1:2)
[H1,w1] = freqz(bHamming_ajustado);
plot(w1*fa/2/pi,20*log10(abs(H1))); grid on;
xlim([0 2*fs])
ylim([-Amin_a Gtopo+5])
hold on
[H2,w2] = freqz(kaiser_ajustado);
plot(w2*fa/2/pi,20*log10(abs(H2))); grid on;
hold on
[H3,w3] = freqz(PM_ajustado);
plot(w3*fa/2/pi,20*log10(abs(H3))); grid on;
legend(['Hamming n = ', num2str(n_fixa)],['Kaiser n = ', num2str(n_ajustavel)],['Parks McClellan n = ', num2str(n_PM)]);
title('Resultado final dos filtros LP projetados')
ylabel('dB')

line([1 fp],[Gp Gp],'Color','red')
line([fp fp],[Gp -Amin_a],'Color','red')
line([1 fs],[Gtopo Gtopo],'Color','red')
line([fs fs],[Gtopo Gs],'Color','red')
line([fs 10e3],[Gs Gs],'Color','red')
hold on 

% Detalhe banda de passagem
subplot(413)
plot(w1*fa/2/pi,20*log10(abs(H1))); grid on;
xlim([0 2*fs])
ylim([Gp-1 Gtopo+1])
hold on
plot(w2*fa/2/pi,20*log10(abs(H2))); grid on;
hold on
plot(w3*fa/2/pi,20*log10(abs(H3))); grid on;
ylabel('dB')

line([1 fp],[Gp Gp],'Color','red')
line([fp fp],[Gp -Amin_a],'Color','red')
line([1 fs],[Gtopo Gtopo],'Color','red')
line([fs fs],[Gtopo Gs],'Color','red')
line([fs 10e3],[Gs Gs],'Color','red')
hold on 

% Detalhe banda de rejeicao
subplot(414)
plot(w1*fa/2/pi,20*log10(abs(H1))); grid on;
xlim([0 2*fs])
ylim([Gs-10 Gs+10])
hold on
plot(w2*fa/2/pi,20*log10(abs(H2))); grid on;
hold on
plot(w3*fa/2/pi,20*log10(abs(H3))); grid on;
ylabel('dB')
xlabel('Frequencia (Hz)')

line([1 fp],[Gp Gp],'Color','red')
line([fp fp],[Gp -Amin_a],'Color','red')
line([1 fs],[Gtopo Gtopo],'Color','red')
line([fs fs],[Gtopo Gs],'Color','red')
line([fs 10e3],[Gs Gs],'Color','red')
hold on 
