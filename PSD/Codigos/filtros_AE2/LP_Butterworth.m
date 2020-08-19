clear all
close all
clc

% Filtro Passa-Baixa Butterworth
fp = 40;
fs = 200;
A0 = 0;
Ap = 3;
As = 20;
Gtopo = 5;
Gp = 2;
Gs = -15;
wp = 2*pi*fp;
ws = 2*pi*fs;

% Passo 0
Os = ws/wp;
Op = wp/wp;

% Passo 1 - Ordem do filtro
n = log((10^(0.1*As)-1))/(2*log(Os));
n = ceil(n);
k = 1:n;

% Passo 2 - Polos do filtro
pk = exp(1j*(2*k+n-1)/(2*n)*pi);
figure(1)
zplane(1,poly(pk));
title('Polos do filtro prototipo')

% Passo 3 - Parte real de um polinomio com raizes pk
Dp = real(poly(pk));

% Passo 4 - Funcao transferencia prototipo
syms p
Dps = poly2sym(Dp,p);
Hp(p) = 1/Dps;

figure(2)
[h,w] = freqs(1,Dp,1000);
semilogx(w,20*log10(abs(h))); grid on;
ylabel('dB')
xlabel('Hz')
title('Filtro LP Butterworth sem ajuste')

% Passos 5 e 6 - Ajustando o filtro
syms s

Hs(s) = subs(Hp(p),(s/wp)); % Funcao transferencia
pretty(vpa(Hs(s),3));
Hs(s) = collect(Hs(s));

[num_Hs, den_Hs] = numden(Hs(s));

bs = sym2poly(num_Hs); % Numerador
as = sym2poly(den_Hs); % Denominador

G0db = Gtopo;
bs = bs * (1*10^(G0db/20)); % Ajuste do ganho
 
figure(3)

subplot(2,1,1)
[h, w] = freqs(bs , as , logspace(2, 5, 1000)); 
semilogx((w/(2*pi)), 20*log10(abs(h))); grid on; % Grafico do filtro

% Mascaras
line([1 fp],[-Gp -Gp],'Color','red')
line([fp fp],[-Gp -50],'Color','red')
line([1 fs],[Gtopo Gtopo],'Color','red')
line([fs fs],[Gtopo Gs],'Color','red')
line([fs 10e3],[Gs Gs],'Color','red')

ylabel('dB')
xlabel('Hz')
ylim([-50 10])
title(['Filtro LP Butterworth de ordem ', num2str(n),' com ajuste'])

subplot(2,1,2)
fase_rad = angle(h);
fase_graus = (fase_rad*180)/pi;
semilogx(w,fase_graus); grid on;
xlabel('Hz')
ylabel('Graus');
title('Fase do filtro')

[h,w] = freqs(bs,as,[0,wp,ws]);
valores_freqs = 20*log10(abs(h))