clc;
close all;
clear all;

info = randi([0 1], 1, 100e3)*2-1;      %gerando muneros aleatórios
info_format = rectpulse(info, 100);     %gerando uma função rect parâmetros (vetor, período)
%plot(info_format);
rx = xcorr(info_format);                %função de autocorrelação (integral)
Gx = fft(rx);                           %densidade espectral de potência
Gx = fftshift(Gx);                      %módulo
plot(abs(Gx))
