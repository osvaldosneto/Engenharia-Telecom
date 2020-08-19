close all;
clear all;
clc;

A0 = 2;
Am = 1;
fm = 1000;

Ac = 1;
fc = 10000;
fs = 200*fm;
n = 20;
n_periodo = 1000;
t_final = n_periodo*(1/fm);
ts = 1/fs;
t = [0:ts:t_final];

m = Am*cos(2*pi*fm*t);
c = Ac*cos(2*pi*fc*t);
m_AMDSB = m+A0;

s = m.*c;
s_AMDSB = m_AMDSB.*c;

figure(1)
subplot(3,2,1);
plot(t, m, 'g');
ylim([-1.4 1.4]);
xlim([0 t_final/200]);
ylabel('m(t)');
xlabel('tempo(s)');

subplot(3,2,3);
plot(t, c, 'b');
ylim([-1.4 1.4]);
xlim([0 t_final/200]);
ylabel('c(t)');
xlabel('tempo(s)');

subplot(3,2,5);
plot(t,s, 'r');
ylim([-1.4 1.4]);
xlim([0 t_final/200]);
ylabel('s(t)');
xlabel('tempo(s)');

f_passo = 1/(t_final);
f = [-fs/2:f_passo:fs/2];

M = fftshift(fft(m)/length(m));
C = fftshift(fft(c)/length(c));
S = fftshift(fft(s)/length(s));

M_AMDSB = fftshift(fft(m_AMDSB)/length(m_AMDSB));
S_AMDSB = fftshift(fft(s_AMDSB)/length(s_AMDSB));

subplot(3,2,2);
plot(f,abs(M),'r');
xlim([-0.1e6 0.1e6]);
ylabel('M(f)');
xlabel('Frequência(Hz)');

subplot(3,2,4);
plot(f,abs(C),'r');
xlim([-0.1e6 0.1e6]);
ylabel('C(f)');
xlabel('Frequência(Hz)');

subplot(3,2,6);
plot(f,abs(S),'r');
xlim([-0.1e6 0.1e6]);
ylabel('S(f)');
xlabel('Frequência(Hz)');

figure(2);
subplot(3,2,1);
plot(t, m_AMDSB, 'g');
xlim([0 t_final/200]);
%ylim([-1.4 1.4]);
ylabel('m(t)');
xlabel('tempo(s)');

subplot(3,2,3);
plot(t, c, 'b');
xlim([0 t_final/200]);
%ylim([-1.4 1.4]);
ylabel('c(t)');
xlabel('tempo(s)');

subplot(3,2,5);
plot(t,s_AMDSB, 'r');
%ylim([-1.4 1.4]);
xlim([0 t_final/200]);
ylabel('s(t)');
xlabel('tempo(s)');

 subplot(3,2,2);
plot(f,abs(M_AMDSB),'r');
xlim([-0.1e6 0.1e6]);
ylabel('M(f)');
xlabel('Frequência(Hz)');

subplot(3,2,4);
plot(f,abs(C),'r');
xlim([-0.1e6 0.1e6]);
ylabel('C(f)');
xlabel('Frequência(Hz)');

subplot(3,2,6);
plot(f,abs(S_AMDSB),'r');
xlim([-0.1e6 0.1e6]);
ylabel('S(f)');
xlabel('Frequência(Hz)');