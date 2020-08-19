clear all
close all
clc

% Filtro BS IIR - Transformacao Bilinear

% Dados iniciais
A0 = 0;
Ap = 3;
As = 40;
Gtopo = 20;
Gp = 17;
Gs = -20;

% Frequencia de amostragem
fa = 8e3;
fa2 = fa/2;

% Frequencias originais (H_especificado(z)) (Hz)
f1 = 1200; f2 = 2000; f3 = 3000; f4 = 3800;

fp1 = f1;
fs1 = f2;
fs2 = f3;
fp2 = f4;
f = [fp1 fs1 fs2 fp2];

% Angulos (H(z))
theta = f/fa2;

% Lambdas (H(s)) - Compensar o empenamento
l = 2.*tan((theta.*pi)/2);
lp1 = l(1); ls1 = l(2); ls2 = l(3); lp2 = l(4);

% Largura de banda e lambda_zero (frequencia central)
B = lp2-lp1;
l0 = sqrt(lp2*lp1);

% Omegas
Os1 = abs((B*ls1)/(-(ls1^2)+l0^2));
Os2 = abs((B*ls2)/(-(ls2^2)+l0^2));
Os = min(Os1,Os2);
Op = 1;

% Passa Baixa Prototipo Eliptico
[n, Wp] = ellipord(Op,Os,Ap,As,'s');
[b, a] = ellip(n,Ap,As,Wp,'s');

% Filtro analogico LP prototipo
[h, w] = freqs(b,a,1000);
mag = 20*log10(abs(h));
subplot(411)
plot(w,mag); grid on; hold on;
plot([0,Op,Os,Op*10],-[0,Ap,As,As],'+'); hold off;
ylim([-2*As 5]); legend('Hp(p)');
title('Filtro analogico LP prototipo')
xlabel('Omega')
ylabel('db');

% Funcao transferencia filtro analogico LP prototipo
syms p
Np = poly2sym(b,p);
Dp = poly2sym(a,p);
Hp(p) = Np/Dp;
pretty(vpa(Hp(p),2));

% Funcao transferencia filtro analogico BS prototipo
syms s
Hs(s) = Hp((B*s)/(s^2+l0^2)); % Substituicao das variaveis
%pretty(vpa(collect(Hs(s)),3))
[Ns, Ds] = numden(Hs(s));

bs = sym2poly(Ns);
as = sym2poly(Ds);
bsn = bs/as(1);
asn = as/as(1);
pretty(vpa(poly2sym(bsn,s)/poly2sym(asn,s),2))

% Filtro analogico BS prototipo
[h, w] = freqs(bsn,asn,linspace(0,10*lp2,1000));
mag = 20*log10(abs(h));
subplot(412)
plot(w,mag); grid on; hold on;
plot([ls1 lp1 lp2 ls2],-[As Ap Ap As],'+'); hold off;
ylim([-2*As 5]);
xlim([lp1*0.1 lp2*2]);
legend('Hs(s)')
title(' Filtro analogico BS prototipo')
xlabel('Omega')
ylabel('db');

% Funcao transferencia filtro digital BS em escala de theta
syms z
Hz(s) = collect(Hs(2*(z-1)/(z+1))); % Transformacao Bilinear
%pretty(vpa(Hz(z),2))
[Nz, Dz] = numden(Hz(z));

bz = sym2poly(Nz)*10^(Gtopo/20);
az = sym2poly(Dz);
bzn = bz/az(1);
azn = az/az(1);
pretty(vpa(poly2sym(bzn,z)/poly2sym(azn,z),2));

% Filtro digital BS em escala de theta
[h, w] = freqz(bzn,azn,10000);
mag = 20*log10(abs(h));
subplot(413)
plot(w/pi,mag); grid on; hold on;
plot([fs1 fp1 fp2 fs2]/(fa/2),-[As Ap Ap As]+Gtopo,'+'); hold off;
ylim([-2*As 5]+Gtopo);
%xlim([lp1*0.1 lp2*2]);
legend('H(z)') 
title(' Filtro digital BS (theta)')
xlabel('theta')
ylabel('db');

% Filtro digital BS em escala de Hz
subplot(414)
plot(w/pi*(fa/2),mag); grid on; hold on;
plot([fs1 fp1 fp2 fs2],-[As Ap Ap As]+Gtopo,'+'); hold off;
ylim([-2*As 5]+Gtopo);
%xlim([lp1*0.1 lp2*2]);
legend('H(z)') 
title(' Filtro digital BS Euler')
xlabel('Hz')
ylabel('db');

% Mascaras
line([0 fs1],[Gtopo Gtopo],'Color','red')
line([fs1 fs1],[Gs Gtopo],'Color','red')
line([fs1 fs2],[Gs Gs],'Color','red')
line([fs2 fs2],[Gs Gtopo],'Color','red')
line([fs2 4e3],[Gtopo Gtopo],'Color','red')

line([0 fp1],[Gp Gp],'Color','red')
line([fp1 fp1],[-60 Gp],'Color','red')

line([fp2 4e3],[Gp Gp],'Color','red')
line([fp2 fp2],[-60 Gp],'Color','red')

% Fase de H(z)
figure(2)
fase_rad = angle(h);
fase_graus = (fase_rad*180)/pi;
semilogx(w,fase_graus); grid on;
xlabel('Hz')
ylabel('Graus');
title('Fase do filtro IIR BS Euler')

% Polos e zeros
figure(3)
zplane(b,a)
title('Polos e zeros do filtro LP prototipo')

figure(4)
zplane(bs,as)
title('Polos e zeros do filtro Bs analogico')

figure(5)
zplane(bz,az)
title('Polos e zeros do filtro BS digital')





