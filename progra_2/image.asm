.data
nuevoValorPixel DWORD 0.0
nuevoValor_R DWORD 0.0
nuevoValor_G DWORD 0.0
nuevoValor_B DWORD 0.0

;Escala de grises
multR DWORD 0.3
multG DWORD 0.59
multB DWORD 0.11
;-----------------

divisor DWORD 3.0
resultado DWORD 0.0

.code



escalaGrises proc R:real4, G:real4, B:real4
	finit
	xor eax, eax
	mov nuevoValorPixel, eax
	;(R * 0.3) + (G * 0.59) + (B * 0.11)

	;------------------Red------------------;
	fld R
	fmul multR
	fstp nuevoValor_R

	;------------------Green------------------;
	fld G
	fmul multG
	fstp nuevoValor_G

	;------------------Blue------------------;
	fld B
	fmul multB
	fstp nuevoValor_B

	;------------------Pixel------------------;
	valorPixel:
		mov eax, nuevoValor_R
		add nuevoValorPixel, eax
		xor eax, eax

		mov eax, nuevoValor_G
		add nuevoValorPixel, eax
		xor eax, eax

		mov eax, nuevoValor_B
		add nuevoValorPixel, eax
		xor eax, eax

		fld nuevoValorPixel
		fdiv divisor
		fstp resultado

		xor eax, eax
		ret

escalaGrises endp

;===================================================================================================================================;

multiplicar proc a:real4, b:real4
	finit								;iniciacion del FPU
	movss a, xmm0
	movss b, xmm1

	fld b								;cargo multiplicando
	fld a								;cargo multiplicador
	fmul								;se procede a la multiplicacion
	fstp a
	movD xmm0, a
	ret									;retorno el resultado
multiplicar endp
;===================================================================================================================================;

dividir proc a:real4, b:real4
	finit								;iniciacion del FPU
	movss a, xmm0
	movss b, xmm1

	fld a								;cargo el dividendo
	fld b								;cargo el divisor
	fdiv								;se realiza la division
	fstp a
	movD xmm0, a
	ret									;retorno el resultado
dividir endp

end