clc
close all
clear all

Am = 1;                                 % Amplitude do sinal 
Ac = 1;                                 % Amplitude da portadora
Ao = 1;                                 % Amplitude AM DSB
mi1 = 0.25;                             % Fator modulante
mi2 = 0.5;
mi3 = 0.75;
mi4 = 1;
mi5 = 1.5;
fm = 1000;                              % Frequ?ncia do sinal
fc = 10000;                             % Frequ?ncia da portadora
N = 200;                                % Fator de superamostragem
fs = N*fm;                              % Frequ?ncia de amostragem
num_periodos = 1000;                    % N?mero de per?odos
t_final = num_periodos*(1/fm);          % Dois per?odos
Ts = 1/fs;                              % Tempo de amostragem 
t = 0:Ts:t_final;                       % Vetor tempo
f_passo = 1/t_final;                   
f = -fs/2:f_passo:fs/2; 

m = Am*cos(2*pi*fm.*t);
c = Ac*cos(2*pi*fc.*t);

figure(1)
subplot(2,1,1)
plot(t,m,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('Sinal m(t)')
axis([0 t_final/200 -1.5*Am 1.5*Am])  

subplot(2,1,2)
plot(t,c,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('Sinal c(t)')
axis([0 t_final/200 -1.5*Am 1.5*Am])

%modulacao AM-DSB-SC
s_AM_DSB_SC = m.*c;

%Sinald modulado
figure(2)
%dominio do tempo
subplot(2,1,1)
plot(t,s_AM_DSB_SC,'k')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('AM DSB SC')
axis([0 t_final/200 -1.5*Am 1.5*Am])

%dominio da ferquencia
S_AM_DSB_SC = fftshift(fft(s_AM_DSB_SC)/length(s_AM_DSB_SC));
subplot(2,1,2)
plot(f,abs(S_AM_DSB_SC),'k');
axis([-2*fc 2*fc 0 0.5]);
ylabel('Amplitude')
xlabel('Frequ?ncia (Hz)')
title('AM DSB SC')

%Demodulando o sinal
m_AM_DSB_SC = s_AM_DSB_SC.*c;

%construindo do filtro
filtro=fir1(50,(1000*2)/fs);
figure(3)
freqz(filtro)

%Filtrando o sinal
m_AM_DSB_SC_filtrado = filter(filtro, 1, m_AM_DSB_SC);

%plotando sinal filtrado
figure(4)
subplot(2,1,1)
%dominio do tempo
plot(t, m_AM_DSB_SC_filtrado,'m')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('Sinal m AM DSB SC filtrado')
axis([0 t_final/200 -1.5*Am 1.5*Am]) 
%dominio da frequencia
M_S_AM_DSB_SC_FILTRADO = fftshift(fft(m_AM_DSB_SC_filtrado)/length(m_AM_DSB_SC_filtrado));
subplot(2,1,2)
plot(f,abs(M_S_AM_DSB_SC_FILTRADO),'m');
axis([-2*fm 2*fm 0 0.8]);
ylabel('Amplitude')
xlabel('Frequ?ncia (Hz)')
title('Sinal M AM DSB SC FILTRADO(f)')






%parte3
%modulacao AM-DSB com fator de modulacao
s_AM_DSB1 = (mi1.*m + Ao).*c;
s_AM_DSB2 = (mi2.*m + Ao).*c;
s_AM_DSB3 = (mi3.*m + Ao).*c;
s_AM_DSB4 = (mi4.*m + Ao).*c;
s_AM_DSB5 = (mi5.*m + Ao).*c;

figure(5)
%fator modulante 0,25 dominio do tempo
subplot(5,2,1)
plot(t,s_AM_DSB1)
ylabel('Amplitude')
xlabel('Tempo (s)')
title('AM DSB - Fator Modulante 0,25')
axis([0 t_final/300 -5*Am 5*Am])
%fator modulante 0,25 dominio da frequencia
S_AM_DSB1 = fftshift(fft(s_AM_DSB1)/length(s_AM_DSB1));
subplot(5,2,2)
plot(f,abs(S_AM_DSB1));
axis([-2*fc 2*fc 0 1.5]);
ylabel('Amplitude')
xlabel('Frequ?ncia (Hz)')
title('AM DSB')

%fator modulante 0,50 dominio do tempo
subplot(5,2,3)
plot(t,s_AM_DSB2)
ylabel('Amplitude')
xlabel('Tempo (s)')
title('AM DSB - Fator Modulante 0,50')
axis([0 t_final/300 -5*Am 5*Am])
%fator modulante 0,50 dominio da frequencia
S_AM_DSB2 = fftshift(fft(s_AM_DSB2)/length(s_AM_DSB2));
subplot(5,2,4)
plot(f,abs(S_AM_DSB2));
axis([-2*fc 2*fc 0 1.5]);
ylabel('Amplitude')
xlabel('Frequ?ncia (Hz)')
title('AM DSB')

%fator modulante 0,75 dominio do tempo
subplot(5,2,5)
plot(t,s_AM_DSB3)
ylabel('Amplitude')
xlabel('Tempo (s)')
title('AM DSB - Fator Modulante 0,75')
axis([0 t_final/300 -5*Am 5*Am])
%fator modulante 0,75 dominio do tempo
S_AM_DSB3 = fftshift(fft(s_AM_DSB3)/length(s_AM_DSB3));
subplot(5,2,6)
plot(f,abs(S_AM_DSB3));
axis([-2*fc 2*fc 0 1.5]);
ylabel('Amplitude')
xlabel('Frequ?ncia (Hz)')
title('AM DSB')

%fator modulante 1 dominio do tempo
%figure(6)
subplot(5,2,7)
plot(t,s_AM_DSB4)
ylabel('Amplitude')
xlabel('Tempo (s)')
title('AM DSB - Fator Modulante 1')
axis([0 t_final/300 -5*Am 5*Am])
%fator modulante 1 dominio do tempo
S_AM_DSB4 = fftshift(fft(s_AM_DSB4)/length(s_AM_DSB4));
subplot(5,2,8)
plot(f,abs(S_AM_DSB4));
axis([-2*fc 2*fc 0 1.5]);
ylabel('Amplitude')
xlabel('Frequ?ncia (Hz)')
title('AM DSB')

%fator modulante 1.5 dominio do tempo
%figure(6)
subplot(5,2,9)
plot(t,s_AM_DSB5)
ylabel('Amplitude')
xlabel('Tempo (s)')
title('AM DSB - Fator Modulante 1.5')
axis([0 t_final/300 -5*Am 5*Am])
%fator modulante 1 dominio do tempo
S_AM_DSB5 = fftshift(fft(s_AM_DSB5)/length(s_AM_DSB5));
subplot(5,2,10)
plot(f,abs(S_AM_DSB5));
axis([-2*fc 2*fc 0 1.5]);
ylabel('Amplitude')
xlabel('Frequ?ncia (Hz)')
title('AM DSB')