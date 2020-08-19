
clear all;
load handel;
y = transpose(y);
t_audio = length(y)/Fs;
t = [0:1/Fs:t_audio-1/Fs];

Y = fft(y);
Y = fftshift(Y);
f = [-Fs/2: 1/ (t_audio) :Fs/2-(1/t_audio)];

subplot(211)
plot(t,y)
subplot(212)
plot(f,abs(Y))
