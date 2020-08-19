clear all
ws1 = 770*2*pi;
wp1= 811*2*pi;
wp2 = 895.5*2*pi;
ws2= 1209*2*pi;
W0 = sqrt(wp1*wp2);
Bw = (wp2-wp1);
Ws1 = abs((W0^2-ws1^2)/(Bw*ws1));
Ws2 = abs((W0^2-ws2^2)/(Bw*ws2));

%% Chebyshev I
n = cheb1ord(1, Ws1, 1, 30,'s');

[b,a] = cheby1(n,1, 1, 's');

freqs (b,a);

syms p
syms s
Np=poly2sym(b,'p');
Dp=poly2sym(a,'p');
H(p)= Np/Dp;

digits(2);
% pretty(vpa(H(p)));
%%
%P=((s^2+W0^2)/(Bw*s));
Hs1(s) = collect(H(((s^2+W0^2)/(Bw*s))));


[Ns,Ds] = numden(Hs1(s));
pretty(vpa(Hs1(s)))
bs = sym2p