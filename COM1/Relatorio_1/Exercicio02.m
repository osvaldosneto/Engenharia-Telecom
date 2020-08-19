%Exercício 02:

A = 5;
f = 5000;
n = 50;                     		%fator de super amostra deve de ser duas vezes a frequencia
n_periodo = 100;            	%numeros de per?odos a ser apresentados na tela
fs = n*f;                   		%frequencia de amostragem
t_final = n_periodo*(1/f); 	 %numero de periodos * periodo
ts = 1/fs;             
t = [0:ts:t_final];         		%vetor de tempo

y = A*sin(2*pi*f/5*t) + A/3*sin(2*pi*3000*t) + A/5*sin(2*pi*f*t);

%domínio do tempo
figure(1)
subplot(2,1,1);
plot(t,y, 'r');
xlim([0 2e-3])
ylabel('y(t)');
xlabel('tempo(s)');
title('Sinal s(t) - Dominio tempo');

%dominio da frequ?ncia
Y = fftshift(fft(y));
passo_f = 1/t_final;
f = [-fs/2 : passo_f : fs/2];
subplot(2,1,2);
plot(f, abs(Y));
xlim([-1e4 1e4]);
ylabel('Amplitude');
xlabel('frequência (Hz)');
title('Sinal S(f) - Dominio frequência');

%Passa baixa (frequ?ncia de corte em 2kHz)
n_filtro_pb = fs/passo_f;
intervalo_filtro = fs/n_filtro_pb;

figure(2)
n_PB = [zeros(1, 2460) ones(1, 81) zeros(1, 2460)];
Y_filtrado_PB = n_PB.*Y;
subplot(3,2,1)
plot(f, Y_filtrado_PB, 'r')
xlim([-1e4 1e4])
title('Sinal Domínio Frequencia - Filtro Passa Baixa - 2 KHz')
ylabel('Amplitude');
xlabel('frequência (Hz)');
ylim([0,200])

subplot(3,2,2);
y_PB = ifft(ifftshift(Y_filtrado_PB));
plot(t, y_PB, 'r');
xlabel('tempo(s)');
title('Sinal Domínio Tempo - Filtro Passa Baixa - 2 KHz');
xlim([0, 3e-3])

%Passa alta(frequ?ncia de corte acima de 4kHz)
n_PA = [ ones(1, 2420) zeros(1, 161) ones(1, 2420)];
subplot(3,2,3)
Y_filtrado_PA = n_PA.*Y;
plot(f, Y_filtrado_PA, 'b');
title('Sinal Domínio Frequência - Filtro Passa Alta - 4 KHz')
ylabel('Amplitude');
xlabel('frequência (Hz)');
ylim([0,200]);
xlim([-1e4 1e4])

subplot(3,2,4);
y_PA = ifft(ifftshift(Y_filtrado_PA));
plot(t, y_PA, 'b');
xlabel('tempo(s)');
title('Sinal Domínio do Tempo - Filtro Passa Alta - 4 KHz');
xlim([0, 3e-3])

%Passa banda (frequ?ncia de corte entre 2 e 4kHz)
n_PBanda = ([zeros(1,2420) ones(1,40) zeros(1, 81) ones(1, 40) zeros(1, 2420)]);
subplot(3,2,5);
Y_filtrado_PBanda = n_PBanda.*Y;
plot(f, Y_filtrado_PBanda, 'g');
title('Sinal Domínio Frequência - Passa Banda - 2 a 4 KHz')
ylabel('Amplitude');
xlabel('frequência (Hz)');
ylim([0,200]);
xlim([-1e4 1e4]);

subplot(3,2,6);
y_PBanda = ifft(ifftshift(Y_filtrado_PBanda));
plot(t, y_PBanda, 'g');
xlabel('tempo(s)');
title('Sinal Domínio Tempo - Passa Banda - 2 a 4 KHz');
xlim([0, 3e-3])

%plotagem dos filtros
figure(4)
subplot(3,1,1)
plot(f, n_PB, 'r');
title('Filtro Passa Faixa')
ylabel('Amplitude');
xlabel('frequência (Hz)');
ylim([0 1.2]);
xlim([-7000 7000])

subplot(3,1,2)
plot(f, n_PA, 'b');
title('Filtro Passa Alta')
ylabel('Amplitude');
xlabel('frequência (Hz)');
ylim([0 1.2]);
xlim([-7000 7000])

subplot(3,1,3)
plot(f, n_PBanda, 'g');
title('Filtro Passa Banda')
ylabel('Amplitude');
xlabel('frequência (Hz)');
ylim([0 1.2]);
xlim([-7000 7000])
