clear all
close all
clc
A = 1;
k = 8; #n. de bits do quantizador
L = 2^k; # n. de níveis de quantização
f = 1e3;
fs = 50*f;
tempo_final = 1;
t = [0:1/fs:tempo_final];
f_eixo = [-fs/2:1/tempo_final:fs/2];
y = A*sin(2*pi*t*f);
%plot(t,y)
Vpp = 2*A;
passo = Vpp/L;
y_aux = y/passo;
y_round = round(y_aux);
y_int = y_round + L/2;
for i=1:length(y_int)
  if y_int(i) == L
    y_int(i) = L-1;
  end
end
y_bin = dec2bin(y_int); # seq. binário transmitida
# considerando que o receptor identificou todos os bits corretamente!
y_rec = bin2dec(y_bin);
y_rec2 = y_rec-(L/2);
y_rec3 = y_rec2*passo;

Y = fftshift(fft(y));
Y_REC3 = fftshift(fft(y_rec3));
figure(1)
subplot(211)
plot(f_eixo,abs(Y))
subplot(212)
plot(f_eixo,abs(Y_REC3))

%figure(2)
%subplot(211)
%plot(t,y)
%subplot(212)
%plot(t,transpose(y_rec3))
%sound(y_rec3)

figure(2)
plot(t,y)
xlim([0 1e-3])
hold on
plot(t,y_rec3)
xlim([0 1e-3])