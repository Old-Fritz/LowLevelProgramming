section .text
global setSepiaRegisters
global setRGBRegistersAndCalc

; rdi = x, rsi = y, rdx = z, rcx = [4] r8 = [5] r9 = [6] 

setSepiaRegisters:
	movdqa xmm3, [rdi]
	movdqa xmm4, [rsi]
	movdqa xmm5, [rdx]
	ret

setRGBRegistersAndCalc:
	movdqa xmm0, [rdi]
	movdqa xmm1, [rsi]
	movdqa xmm2, [rdx]

	mulps xmm3, xmm0
	mulps xmm4, xmm1
	mulps xmm5, xmm2

	addps xmm3, xmm4
	addps xmm3, xmm5

	movdqa [rcx], xmm3
	ret