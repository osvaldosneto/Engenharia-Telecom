%filtro passa alta
%f1 = 40 Hz
%f2 = 200 Hz
%Ap = 1 dB
%As = 50 dB
%Gp = 10 dB

close all;
clear all;
clc;

%parâmetros
Ap = 1
As = 50
Gp = 10
Ws = 40
Wp = 200

Gt = Ap + Gp
Gs = Gt - As

%determinando ordem filtro
epsion = sqrt(10^0.1*Ap -1)
Os = Wp/Ws
Op = Wp/Wp
n = acosh(sqrt ( (10^(As*0.1) - 1) / epsion^2) )  / acosh(Os);
n = ceil(n)

%determinando os polos
%theta e phi
k = 1: n;
theta = ( (2*k -1)*pi ) / (2*n)
phi = (1/n) * ( asinh( 1 / epsion) )

pk = -sinh(phi)*sin(theta) +1j*cosh(phi)*cos(theta)
dp = real(poly(pk))

%calculo Ho para n impar
Ho = dp(end)/(sqrt(1+epsion^2))

%funcao de transferencia
syms p
Dp = vpa( dp(1)*p^3 + dp(2)*p^2 + dp(3)*p^1 + dp(4)*p^0);

%Gerando graficos
%figure(1)
%[h, w] = freqs(1, dp, 1000);
%semilogx(w, 20*log10(abs(h))); grid on;
%figure(2)
%freqs(1, dp, 1000)
%ganho nos pontos das frequencias
%[h, w] = freqs(1, dp, [0, 1, 5]);
%20*log10(abs(h))






