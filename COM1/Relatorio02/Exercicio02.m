clc
close all
clear all

Am = 1;                                 % Amplitude do sinal 
Ac = 1;                                 % Amplitude da portadora
fm = 1000;                              % Frequ?ncia do sinal
fc = 1000;                              % Frequ?ncia da portadora
N = 200;                                % Fator de superamostragem
fs = N*fm;                              % Frequ?ncia de amostragem
num_periodos = 1000;                    % N?mero de per?odos
t_final = num_periodos*(1/fm);          % Dois per?odos
Ts = 1/fs;                              % Tempo de amostragem 
t = 0:Ts:t_final;                       % Vetor tempo
f_passo = 1/t_final;
f = -fs/2:f_passo:fs/2;

%sinal a modular
m1 = Am*cos(2*pi*fm.*t);
m2 = Am*cos(2*pi*2*fm*t);
m3 = Am*cos(2*pi*3*fm*t);
%gerando sinais das portadorasa
c1 = Ac*cos(2*pi*10*fc.*t);
c2 = Ac*cos(2*pi*12*fc.*t);
c3 = Ac*cos(2*pi*14*fc.*t);

%plot sinais dominio tempo e frequencia
%m1
figure(1)
subplot(3,2,1)
plot(t,m1,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('m1(t)')
axis([0 t_final/100 -1.5*Am 1.5*Am])
subplot(3,2,2)
M1 = fftshift(fft(m1)/length(m1));
plot(f,abs(M1),'k');
axis([-4*fc 4*fc 0 0.7]);
ylabel('Amplitude')
xlabel('Frequencia (Hz)')
title('M1(f)')
%m2
subplot(3,2,3)
plot(t,m2,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('m2(t)')
axis([0 t_final/100 -1.5*Am 1.5*Am])
subplot(3,2,4)
M2 = fftshift(fft(m2)/length(m2));
plot(f,abs(M2),'k');
axis([-4*fc 4*fc 0 0.7]);
ylabel('Amplitude')
xlabel('Frequencia (Hz)')
title('M2(f)')
%m3
subplot(3,2,5)
plot(t,m3,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('m3(t)')
axis([0 t_final/100 -1.5*Am 1.5*Am])
subplot(3,2,6)
M3 = fftshift(fft(m3)/length(m3));
plot(f,abs(M3),'k');
axis([-4*fc 4*fc 0 0.7]);
ylabel('Amplitude')
xlabel('Frequencia (Hz)')
title('M3(f)')

%modulando os sinais
m1_m = m1.*c1;
m2_m = m2.*c2;
m3_m = m3.*c3;

%filtro passa faixa para nao misturar os sinais
pf1 = fir1(500, [8900/(fs/2) 9100/(fs/2)]);
pf2 = fir1(500, [9900/(fs/2) 10100/(fs/2)]);
pf3 = fir1(500, [10900/(fs/2) 11100/(fs/2)]);

%filtrando os sinais
m1_m_filtrado = filter(pf1, 1, m1_m);
m2_m_filtrado = filter(pf2, 1, m2_m);
m3_m_filtrado = filter(pf3, 1, m3_m);

%plot sinais dominio tempo e frequencia filtrados antes da soma e envio
%m1
figure(2)
subplot(3,2,1)
plot(t,m1_m_filtrado,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('m1 m filtrado(t)')
axis([0 t_final/400 -1.5*Am 1.5*Am])
subplot(3,2,2)
M1_M_FILTRADO = fftshift(fft(m1_m_filtrado)/length(m1_m_filtrado));
plot(f,abs(M1_M_FILTRADO),'k');
axis([-14*fc 14*fc 0 0.4]);
ylabel('Amplitude')
xlabel('Frequencia (Hz)')
title('M1 M FILTRADO(f)')
%m2
subplot(3,2,3)
plot(t,m2_m_filtrado,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('m2 m filtrado(t)')
axis([0 t_final/400 -1.5*Am 1.5*Am])
subplot(3,2,4)
M2_M_FILTRADO = fftshift(fft(m2_m_filtrado)/length(m2_m_filtrado));
plot(f,abs(M2_M_FILTRADO),'k');
axis([-14*fc 14*fc 0 0.4]);
ylabel('Amplitude')
xlabel('Frequencia (Hz)')
title('M2 M FILTRADO(f)')
%m3
subplot(3,2,5)
plot(t,m3_m_filtrado,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('m3 m filtrado(t)')
axis([0 t_final/400 -1.5*Am 1.5*Am])
subplot(3,2,6)
M3_M_FILTRADO = fftshift(fft(m3_m_filtrado)/length(m3_m_filtrado));
plot(f,abs(M3_M_FILTRADO),'k');
axis([-14*fc 14*fc 0 0.4]);
ylabel('Amplitude')
xlabel('Frequencia (Hz)')
title('M3 M FILTRADO(f)')

%sinal enviado
s = m1_m_filtrado + m2_m_filtrado + m3_m_filtrado;

%plot sinal enviado
figure(3)
subplot(2,1,1)
plot(t, s, 'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('s(t)')
axis([0 t_final/250 -1.5*Am 1.5*Am])
subplot(2,1,2)
S = fftshift(fft(s)/length(s));
plot(f,abs(S),'k');
axis([-14*fc 14*fc 0 0.4]);
ylabel('Amplitude')
xlabel('Frequencia (Hz)')
title('S(f)')

%filtrando sinal recebido
s1_filtrado = filter(pf1, 1, s);
s2_filtrado = filter(pf2, 1, s);
s3_filtrado = filter(pf3, 1, s);

%plot sinais tratado no dominio tempo e frequencia
%s1_filtrado
figure(4)
subplot(3,2,1)
plot(t,s1_filtrado,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('s1 filtrado(t)')
axis([0 t_final/200 -0.5*Am 0.5*Am])
subplot(3,2,2)
S1_FILTRADO = fftshift(fft(s1_filtrado)/length(s1_filtrado));
plot(f,abs(S1_FILTRADO),'k');
axis([-14*fc 14*fc 0 0.4]);
ylabel('Amplitude')
xlabel('Frequencia (Hz)')
title('S 1 FILTRADO(f)')
%s2_filtrado
subplot(3,2,3)
plot(t,s2_filtrado,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('s2 filtrado(t)')
axis([0 t_final/200 -1.5*Am 1.5*Am])
subplot(3,2,4)
S2_FILTRADO = fftshift(fft(s2_filtrado)/length(s2_filtrado));
plot(f,abs(S2_FILTRADO),'k');
axis([-14*fc 14*fc 0 0.4]);
ylabel('Amplitude')
xlabel('Frequencia (Hz)')
title('S2 FILTRADO(f)')
%s3_filtrado
subplot(3,2,5)
plot(t,s3_filtrado,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('S3 filtrado(t)')
axis([0 t_final/200 -1.5*Am 1.5*Am])
subplot(3,2,6)
S3_FILTRADO = fftshift(fft(s3_filtrado)/length(s3_filtrado));
plot(f,abs(S3_FILTRADO),'k');
axis([-14*fc 14*fc 0 0.4]);
ylabel('Amplitude')
xlabel('Frequencia (Hz)')
title('S3 FILTRADO(f)')

%demodulando sinal
s1_m = s1_filtrado.*c1;
s2_m = s2_filtrado.*c2;
s3_m = s3_filtrado.*c3;

%filtro passa baixa para finalizar o tratamento do sinal
pb1 = fir1(500, 910/(fs/2));
pb2 = fir1(500, 2010/(fs/2));
pb3 = fir1(500, 3010/(fs/2));

%filtrando sinal demodulado
s1 = filter(pb1, 1, s1_m);
s2 = filter(pb2, 1, s2_m);
s3 = filter(pb3, 1, s3_m);

%plot sinais filtrado no dominio tempo e frequencia
%s1
figure(5)
subplot(3,2,1)
plot(t,s1,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('s1(t)')
axis([0 t_final/100 -0.2*Am 0.2*Am])
subplot(3,2,2)
S1 = fftshift(fft(s1)/length(s1));
plot(f,abs(S1),'k');
axis([-4*fc 4*fc 0 0.1]);
ylabel('Amplitude')
xlabel('Frequencia (Hz)')
title('S1(f)')
%s2
subplot(3,2,3)
plot(t,s2,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('s2(t)')
axis([0 t_final/100 -0.2*Am 0.2*Am])
subplot(3,2,4)
S2 = fftshift(fft(s2)/length(s2));
plot(f,abs(S2),'k');
axis([-4*fc 4*fc 0 0.1]);
ylabel('Amplitude')
xlabel('Frequencia (Hz)')
title('S2 (f)')
%s3
subplot(3,2,5)
plot(t,s3,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('S3(t)')
axis([0 t_final/100 -0.2*Am 0.2*Am])
subplot(3,2,6)
S3 = fftshift(fft(s3)/length(s3));
plot(f,abs(S3),'k');
axis([-4*fc 4*fc 0 0.1]);
ylabel('Amplitude')
xlabel('Frequencia (Hz)')
title('S3(f)')