clear all
close all
clc
M = 8;
info = randi([0 M-1], 1, 1000);
teta = (2*pi*info)/M;
phi = exp(1j*teta);
scatterplot(phi)