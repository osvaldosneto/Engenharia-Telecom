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

m1 = Am*cos(2*pi*fm.*t);
m2 = Am*cos(2*pi*2*fm*t);
m3 = Am*cos(2*pi*3*fm*t);

figure(1)
subplot(3,1,1)
plot(t,m1,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('Sinal m1(t)')
axis([0 t_final/100 -3*Am 3*Am])

c1 = Ac*cos(2*pi*10*fc.*t);
c2 = Ac*cos(2*pi*12*fc.*t);
c3 = Ac*cos(2*pi*14*fc.*t);

%modulando os sinais
m1_m = 2*m1.*c1;
m2_m = m2.*c2;
m3_m = m3.*c3;

%filtro passa faixa para nao misturar os sinais
pf1 = fir1(200, [8500/(fs/2) 9500/(fs/2)]);
pf2 = fir1(200, [9500/(fs/2) 10500/(fs/2)]);
pf3 = fir1(200, [10500/(fs/2) 11500/(fs/2)]);

%filtrando os sinais
m1_m_filtrado = filter(pf1, 1, m1_m);
m2_m_filtrado = filter(pf2, 1, m2_m);
m3_m_filtrado = filter(pf3, 1, m3_m);

%sinal enviado
s = m1_m_filtrado + m2_m_filtrado + m3_m_filtrado;

%sinal em funcao do tempo
figure(2)
subplot(2,1,1)
plot(t,s,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('Sinal s(t)')
axis([0 t_final/500 -3*Am 3*Am])
% 
subplot(2,1,2)
S = fftshift(fft(s)/length(s));
plot(f,abs(S),'k');
axis([-21*fc 21*fc 0 0.7]);
ylabel('Amplitude')
xlabel('Frequ?ncia (Hz)')
title('S(f)')


%tratamento recebimento do sinal
%gerando filtros para tratamento do sinal
filtro_pf1 = fir1(200, [8500/(fs/2) 9500/(fs/2)]);
filtro_pf2 = fir1(200, [9500/(fs/2) 10500/(fs/2)]);
filtro_pf3 = fir1(200, [10500/(fs/2) 11500/(fs/2)]);

%filtrando e separando os sinais
s1 = filter(filtro_pf1, 1, s);
s2 = filter(filtro_pf2, 1, s);
s3 = filter(filtro_pf3, 1, s);

%demodulando os sinais
s1_dem = 2*s1.*c1;
s2_dem = s2.*c2;
s3_dem = s3.*c3;

%gerando os filtros de 1, 2 e 3 KHz
filtro_pb1 = fir1(200, 1500/(fs/2));
filtro_pb2 = fir1(200, 2500/(fs/2));
filtro_pb3 = fir1(200, 3500/(fs/2));

%filtrando os sinais separados
s1_filtrado = filter(filtro_pb1, 1, s1_dem);
s2_filtrado = filter(filtro_pb2, 1, s2_dem);
s3_filtrado = filter(filtro_pb3, 1, s3_dem);


figure(3)
%plotando os sinais
%s1(t)
subplot(3,1,1)
plot(t,s1_filtrado,'r')
ylabel('Amplitude')
xlabel('Tempo (s)')
title('Sinal s1(t)')
axis([0 t_final/100 -3*Am 3*Am])
%S1(f)
S1_FILTRADO = fftshift(fft(s1_filtrado)/length(s1_filtrado));
subplot(3,1,2)
plot(f,abs(S1_FILTRADO),'k');
axis([-21*fc 21*fc 0 0.7]);
ylabel('Amplitude')
xlabel('Frequencia (Hz)')
title('S1 FILTRADO(f)')