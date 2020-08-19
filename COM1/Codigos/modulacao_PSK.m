clear all
close all
clc

fc = 10e3;
N = 60;
fs = fc*N;
ts = 1/fs;
A = 1;
M = 8;
Rb = 1e4;
filtro_tx = ones(1,N);
info = randi([0 M-1], 1, Rb);
info_up = upsample(info, N);
info_tx = filter(filtro_tx, 1, info_up);

phi = (2*pi*info_tx)/M;
t = [0:ts:1-ts];

c_t = A*sin(2*pi*fc*t + 0);
s_t = A*sin(2*pi*fc*t + phi);
subplot(311)
plot(t,info_tx)
xlim([0 30/fc]) 
ylim([-.2 M*1.2])
subplot(312)
plot(t,c_t)
xlim([0 30/fc])
ylim([-A*1.2 A*1.2])
subplot(313)
plot(t,s_t)
xlim([0 30/fc])
ylim([-A*1.2 A*1.2])