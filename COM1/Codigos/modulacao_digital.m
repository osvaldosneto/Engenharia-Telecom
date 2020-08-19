clear all;
close all;
clc;

A = 1;
k = 3; %numero de bits do quantizador
l = 2^k; %numero de níveis de quantização

f = 1e3;
fs = 1000*f;
t = [0:1/fs:2e-3];
y = sin(2*pi*f*t);
plot(t,y)

vpp = 2*A;
passo = vpp/l; %definindo o passo amplitude/numeroníveis
y_aux = y/passo; %forma para chegar aos valores dos níveis desejados [-4 -4 -2 -1 0 1 2 3 4 ]
y_round = round(y_aux); %arrendondamento dos valores
y_int = y_round + l/2; %somando para enviar apenas sinais acima de 0

%concertando o numero de níveis
for i=1:length(y_int)
  if y_int(i) == l
    y_int(i) = l-1;
  end
end

figure(2)
plot(y_int)

%sinal para transmissão
y_bin = dec2bin(y_int) %sequencia binária transmitida

%recepção sinal
y_rec = bin2dec(y_bin);
y_rec2 = y_rec-(l/2); %deslocando 4 unidades para baixo, voltando ao sinal original
y_rec3 = y_rec2*passo;
figure(1)
subplot(211)
plot(t,y)
subplot(212)
plot(t, transpose(y_rec3))

figure(2)
plot(t,y)
hold on;
plot(t,y_rec3)