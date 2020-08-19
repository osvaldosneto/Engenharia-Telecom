clear all
close all
clc

% Filtro Passa-Alta Chebyshev Tipo 1
fp = 200;
fs = 40;
A0 = 0;
Ap = 1;
As = 50;
Gtopo = 10;
Gp = 9;
Gs = -40;
G0db = 10;
wp = 2*pi*fp;
ws = 2*pi*fs;
Os = wp/ws;
Op = wp/wp;

% Passo 0 - Calculando Epsilon
epsilon = sqrt((10^(0.1*Ap))-1);

% Passo 1 - Ordem do filtro
n = acosh((sqrt((10^(0.1*As))-1))/(epsilon^2))/acosh(Os);
n = ceil(n);

% Passo 2 - Polos do Filtro
k = 1:n;

theta_k = (((2.*k-1)*pi)/(2*n));
phi2 = (1/n)*asinh(1/epsilon);

pk = -sinh(phi2).*sin(theta_k)+1i*cosh(phi2).*cos(theta_k);
figure(1)
zplane(1,poly(pk));
title('Polos do filtro prototipo')

% Passo 3 - Parte real de um polinomio com raizes pk 
% Denominador da funcao transferencia
Dp = real(poly(pk));

% Passo 4 - Numerador da funcao transferencia
d0 = Dp(end);
if rem(n,2) == 0
    Ho = d0/sqrt(1+(epsilon^2));
else
    Ho = d0;
end 
 
% Passo 5 - Funcao transferencia prototipo
syms p
Hp(p) = Ho/(Dp(1)*p^4+Dp(2)*p^3+Dp(3)*p^2+Dp(4)*p^1+Dp(5)*p^0);
pretty(vpa(Hp(p),3))

% Filtro LP prototipo
figure(2)
[h,w] = freqs(Ho,Dp,1000);
semilogx(w,20*log10(abs(h))); grid on;
ylabel('dB')
xlabel('Hz')
title('Filtro LP prototipo')

% Ajustando para filtro HP
syms s

Hs(s) = Hp(wp/s);
pretty(vpa(collect(Hs(s)),3))

Dp = [1.94e21 6.57e24 1.62e28 1.33e31 1.75e34];
Ho = [1.73e21*10^(G0db/20) 0 0 0 0];

figure(3)

subplot(2,1,1)
[h,w] = freqs(Ho,Dp,logspace(2, 5, 1000));
semilogx(w/(2*pi),20*log10(abs(h))); grid on;

% Mascaras
line([fp fp],[-60 Gp],'Color','red')
line([fp 10e3],[Gp Gp],'Color','red')
line([10 fs],[Gs Gs],'Color','red')
line([fs fs],[Gs Gtopo],'Color','red')
line([fs 10e3],[Gtopo Gtopo],'Color','red')

ylim([-60 30])
xlim([10 1e4])
ylabel('dB')
xlabel('Hz')
title(['Filtro HP Chebyshev Tipo 1 de ordem ', num2str(n),' com ajuste'])

subplot(2,1,2)
fase_rad = angle(h);
fase_graus = (fase_rad*180)/pi;
semilogx(w,fase_graus); grid on;
xlabel('Hz')
ylabel('Graus');
title('Fase do filtro')

[h,w] = freqs(Ho,Dp,[0,2*pi*40,2*pi*200]);
valores_freqs = 20*log10(abs(h))
