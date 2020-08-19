%Exercício 03

fs = 10e3;                   %frequencia de amostragem
ts = 1/fs; 
t_final = 1;
t = [0:ts:t_final-ts];
f = [-fs/2:1:fs/2-1];

rui = randn(1,10000);
figure(1);
hist(rui, 200);
title('Histograma Ru?do')

figure(2)
subplot(2,1,1)
plot(t, rui)
xlabel('Tempo (s)')
ylabel('Amplitude')
title('Ru?do no Dom?nio do Tempo');

subplot(2,1,2)
R = fftshift(fft(rui));
plot(f, abs(R));
xlabel('Frequ?ncia (Hz)')
ylabel('Amplitude')
title('Ru?do no Dom?nio da Frequ?ncia');

[R, L] = xcorr(rui, 30, 'biased');
figure(3)
plot(L,R, 'b')
title('Auto Correlacao')

filtro=fir1(50,(1000*2)/fs);
figure(4)
freqz(filtro)

figure(5)
subplot(2,1,1)
Ruido_filtrado = filter(filtro, 1, rui);
plot(t, Ruido_filtrado)
title('Ruido Dominio do Tempo - Filtrado');
xlabel('Tempo (s)');
ylabel('Amplitude')

subplot(2,1,2)
RF = fftshift(fft(Ruido_filtrado))
plot(f, abs(RF))
title('Ruido Dominio da Frequencia - Filtrado');
xlabel('Frequencia (Hz)');
ylabel('Amplitude')
figure(6)
hist(Ruido_filtrado,200)
title('Histograma Ruido Filtrado')
