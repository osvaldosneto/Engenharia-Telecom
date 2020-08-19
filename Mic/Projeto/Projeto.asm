	DADOS EQU P2
	RS EQU P0.5
	RW EQU P0.6
	EN EQU P0.7

	bola equ 1fh

	org 0000h
	jmp setdisplay

	ORG 0003h
	call interrupcao
	reti
	
	ORG 0013h
	call interrupcao_2
	RETI 

	ORG 001Bh
	clr tr1
	clr tf1
	call contagem
	reti
	
	org 0050h
;*************** inicialização display **************
setDisplay:
	rept 6
	call delay_5ms
	endm
	mov r7, #00110000b
	call cmd
	call delay_5ms	
	mov r7, #00110000b
	call cmd
	call delay_5ms
	mov r7, #00110000b
	call cmd
	call delay_5ms
	mov r7, #00111000b
	call cmd
	call delay_5ms
	mov r7, #00001000b
	call cmd
	call delay_5ms
	mov r7, #00000001b
	call cmd
	call delay_5ms
	mov r7, #00000110b
	call cmd
	call delay_5ms
	mov r7, #00001111b		;b seta o blinking
	call cmd
	call delay_5ms
	jmp config
;**************** fim inicialização display *********************
config:
	mov ie, #10001101b
	mov dptr, #1000h
	mov r1, #21h

inicializacao:
	mov r7, #10000000b
	call cmd
	mov r0, #'#'
	rept 16
	call delay_40micro
	call envio
	endm
	mov r7, #11000000b
	call cmd
	rept 16
	call delay_40micro
	call envio
	endm
	rept 150
	call delay_5ms
	endm
	call clear
zero:
	mov r0, #'T'
	mov r6, #00110000b
	mov r2, #00110000b
	mov r3, #00110000b
	mov r4, #00110000b
	mov r7, #10000001b
	call cmd
	call envio
	call envio
	mov r0, #'I'
	call envio
	mov r0, #'M'
	call envio
	mov r0, #'E'
	call envio
	mov r0, #'R'
	call envio
	mov r0, #'='
	call envio
	mov r0, #00110000b
	call envio
	call envio
	mov r0, #':'
	call envio
	mov r0, #00110000b
	call envio
	call envio
	mov r7, #11000000b
	call cmd
	mov r0, #'S'
	call envio
	mov r0, #'O'
	call envio
	mov r0, #'R'
	call envio
	mov r0, #'T'
	call envio
	mov r0, #'E'
	call envio
	mov r0, #'I'
	call envio
	mov r0, #'O'
	call envio
	mov r0, #'='
	call envio
	
	jmp init
;******************************************inicio de contagem**********
init:	
	call delay_1s
	jmp init

;****************************************fim***************************
interrupcao:
	clr a
	movc a, @a+DPTR
	mov @r1, a
	inc r1
	inc dptr
	call sorteio_dezena	
	call sorteio_unidade
	call delay_50ms
	call delay_50ms
	call delay_50ms
	call delay_50ms
	inc bola
	ret

interrupcao_2:
	clr tr2
	clr tr1
	mov ie, #00000000b
	mov r1, #21h

repeticao:
	
	djnz bola, imprimir
	jmp $

imprimir:
	mov a, @r1
	call sorteio_dezena
	call sorteio_unidade
	inc r1
	call delay_1s
	jmp repeticao
	
sorteio_dezena:
	mov b, a
	clr b.7
	clr b.6
	setb b.5
	setb b.4
	mov r0, b
	mov r7, #11001001b
	call cmd
	call envio
	ret

sorteio_unidade:
	swap a
	clr a.7
	clr a.6
	setb a.5
	setb a.4
	mov r0, a
	mov r7, #11001000b
	call cmd
	call envio
	ret
	

contagem:
	inc r6
	cjne r6, #00111010b, conta_segundos
	call decimal
	ret

conta_segundos:
	mov r7, #10001010b
	call cmd
	mov a, r6
	mov r0, a
	call envio
	ret

decimal:
	inc r2
	mov r6, #00110000b
	mov r7, #10001010b
	call cmd
	mov a, r6
	mov r0, a
	call envio
	cjne r2, #00110110b, setR2
	call minutos_0
	mov r7, #10001011b
	call cmd
	ret

setR2:
	mov r7, #10001001b
	call cmd
	mov a, r2
	mov r0, a
	call envio
	mov r7, #10001011b
	call cmd
	ret

minutos_0:
	inc r3
	mov r2, #00110000b
	call setr2
	cjne r3, #00111010b, setR3
	call minutos_1
	mov r7, #10001011b
	call cmd
	ret
	
setR3:
	mov r7, #10000111b
	call cmd
	mov a, r3
	mov r0, a
	call envio
	mov r7, #10001011b
	call cmd
	ret

minutos_1:
	inc r4
	mov r3, #00110000b
	mov r7, #10000110b
	call cmd
	mov a, r4
	mov r0, a
	call envio
	call setr3
	mov r7, #10001011b
	call cmd
	ret

envio:
	setb en
	setb rs
	clr rw
	mov dados, r0
	clr en
	call delay_5ms
	ret

clear:
	clr rs
	clr rw
	setb en
	mov dados, #00000001b
	call delay_5ms
	clr en
	ret

cmd: 	
	setb en
	clr rs
	clr rw
	mov dados, r7
	clr en
	call delay_40micro
	call delay_40micro
	ret

delay_1s:
	rept 16
	call delay_timer2_995ms
	endm
	mov tmod, #00010000b
	mov th1, #0FCh
	mov tl1, #018h
	setb tr1
	jnb tf1, $
	ret

delay_timer2_995ms:
	mov th2, #02eh
	mov tl2, #0b8h
	setb tr2	
	jnb tf2, $
	clr tf2
	clr tr2
	ret

delay_5ms:
	mov tmod, #00000001b
	mov th0, #0ECh	
	mov tl0, #078h
	setb tr0
	jnb tf0, $		;LOOP AGUARDANDO FLAG "ESTOURAR"
	clr tr0			;DESLIGA O TIME
	clr tf0
	ret

delay_50ms:
	mov tmod, #00000001b
	mov th0, #03Ch	
	mov tl0, #0B0h
	setb tr0
	jnb tf0, $		;LOOP AGUARDANDO FLAG "ESTOURAR"
	clr tr0			;DESLIGA O TIME
	clr tf0
	ret

delay_40micro: ;mudar o timer
	mov tmod, #00000001b
	mov th0, #0FFh
	mov tl0, #0D8h
	setb tr0
	jnb tf0, $		;LOOP AGUARDANDO FLAG "ESTOURAR"
	clr tr0			;DESLIGA O TIME
	clr tf0
	ret


	ORG 1000h
	
	DB 24h	 
	DB 07h
	DB 31h
	DB 21h
	DB 78h
	DB 83h
	DB 49h
	DB 18h
	DB 46h 
	DB 35h
	DB 62h
	DB 56h
	DB 81h
	DB 55h
	DB 72h
	DB 06h
	DB 57h
	DB 68h
	DB 94h
	DB 04h
	DB 34h
	DB 17h
	DB 61h
	DB 69h
	DB 48h
	DB 87h
	DB 79h
	DB 96h
	DB 30h
	DB 99h
	DB 28h
	DB 02h	 
	DB 36h

end

