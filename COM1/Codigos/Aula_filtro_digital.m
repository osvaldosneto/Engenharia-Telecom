close all;
clear all;
clc

M = 2;
N = 100;
info = randi([0 M-1], 1, 10)
filtro_NRZ = ones(1, N);

info_up = upsample(info, N);
sinal_tx = conv(info_up, filtro_NRZ);
sinal_tx = sinal_tx(1:end-(N-1)); %truncamento
