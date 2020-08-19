clc;
close all;
clear all;

rui = randn(1,100000);
max(rui)
min(rui)
var(rui)        %variancia
mean(rui)       %média
hist(rui, 150)
E_x_2 = sum(rui.^2)/length(rui) %valor médio quadrático

%testando sinal deslocado alterando média
r = rui + 5;
var(r)      %variância fica a mesma
mean(r)     %média soma 5
E1_x_2 = sum(r.^2)/length(r) %valor médio quadrático E[x²] = E[x]²(potência DC) + sigma²(potência AC)

%alterando a variância
r_var = sqrt(2)*rui; %sqrt(2) é o valor da variância a somar
var(r_var)