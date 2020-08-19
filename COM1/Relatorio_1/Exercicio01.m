%Exercício 01:

A = 2;
f = 5000;
n = 50;                     		%fator de super amostra deve de ser duas vezes a frequencia
n_periodo = 100;            	%numeros de per?odos a ser apresentados na tela
fs = n*f;                   		%frequencia de amostragem
t_final = n_periodo*(1/f);  	%numero de periodos * periodo
ts = 1/fs;                  		
t = [0:ts:t_final];         		%vetor de tempo

y = 3*A*sin(2*pi*f/5*t) + A*sin(2*pi*3000*t) + 2*A*sin(2*pi*f*t);
p_y = sum(y.^2)/length(y)
p_y2 = sum(y.^2)
std(y)^2
sqrt(p_y2)

subplot(3,1,1);
plot(t,y, 'r');
ylabel('y(t)');
xlabel('tempo(s)');
xlim([0 0.003]);
title('Sinal s(t) - Dominio tempo');

Y = fftshift(fft(y));
passo_f = 1/t_final;
f = [-fs/2 : passo_f : fs/2];
subplot(3,1,2);
plot(f, abs(Y));
ylabel('Amplitude');
xlabel('frequencia (Hz)');
xlim([-20000 20000])
title('Sinal S(f) - Dominio frequencia');

n = norm(y)
n2 = n^2

subplot(3,1,3);
%pwelch(y,[],[],[],fs,'onesided');
%pwelch(y,[],[],[],fs,'shift','semilogy');