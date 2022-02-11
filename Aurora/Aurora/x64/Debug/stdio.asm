; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?integer_buffer@@3PADA				; integer_buffer
PUBLIC	?float_to_string_output@@3PADA			; float_to_string_output
_BSS	SEGMENT
?integer_buffer@@3PADA DB 020H DUP (?)			; integer_buffer
?float_to_string_output@@3PADA DB 020H DUP (?)		; float_to_string_output
_BSS	ENDS
CONST	SEGMENT
$SG2921	DB	'0123456789ABCDEF', 00H
	ORG $+3
$SG3063	DB	'.', 00H
CONST	ENDS
_DATA	SEGMENT
chars	DQ	FLAT:$SG2921
_DATA	ENDS
PUBLIC	?sztoa@@YAPEAD_KPEADH@Z				; sztoa
PUBLIC	?printf@@YAXPEBDZZ				; printf
PUBLIC	?atow@@YAXPEADPEBD@Z				; atow
PUBLIC	?int_to_str@@YAPEBDH@Z				; int_to_str
PUBLIC	?ftoa@@YAPEADME@Z				; ftoa
PUBLIC	__real@41200000
PUBLIC	__real@bf800000
EXTRN	?strlen@@YA_KPEBD@Z:PROC			; strlen
EXTRN	?puts@@YAXPEAD@Z:PROC				; puts
EXTRN	?is_console_initialized@@YA_NXZ:PROC		; is_console_initialized
EXTRN	?debug_print@@YAXPEBDZZ:PROC			; debug_print
EXTRN	_fltused:DWORD
pdata	SEGMENT
$pdata$?sztoa@@YAPEAD_KPEADH@Z DD imagerel $LN11
	DD	imagerel $LN11+275
	DD	imagerel $unwind$?sztoa@@YAPEAD_KPEADH@Z
$pdata$?printf@@YAXPEBDZZ DD imagerel $LN26
	DD	imagerel $LN26+894
	DD	imagerel $unwind$?printf@@YAXPEBDZZ
$pdata$?int_to_str@@YAPEBDH@Z DD imagerel $LN7
	DD	imagerel $LN7+280
	DD	imagerel $unwind$?int_to_str@@YAPEBDH@Z
$pdata$?ftoa@@YAPEADME@Z DD imagerel $LN9
	DD	imagerel $LN9+311
	DD	imagerel $unwind$?ftoa@@YAPEADME@Z
pdata	ENDS
;	COMDAT __real@bf800000
CONST	SEGMENT
__real@bf800000 DD 0bf800000r			; -1
CONST	ENDS
;	COMDAT __real@41200000
CONST	SEGMENT
__real@41200000 DD 041200000r			; 10
CONST	ENDS
xdata	SEGMENT
$unwind$?sztoa@@YAPEAD_KPEADH@Z DD 011301H
	DD	04213H
$unwind$?printf@@YAXPEBDZZ DD 021b01H
	DD	023011bH
$unwind$?int_to_str@@YAPEBDH@Z DD 010801H
	DD	04208H
$unwind$?ftoa@@YAPEADME@Z DD 010e01H
	DD	0820eH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\stdio.cpp
_TEXT	SEGMENT
i$1 = 32
new_value$ = 36
float_ptr$ = 40
int_ptr$ = 48
value$ = 80
decimal_places$ = 88
?ftoa@@YAPEADME@Z PROC					; ftoa

; 74   : char* ftoa(float value, uint8_t decimal_places) {

$LN9:
	mov	BYTE PTR [rsp+16], dl
	movss	DWORD PTR [rsp+8], xmm0
	sub	rsp, 72					; 00000048H

; 75   : 	char* int_ptr = (char*)int_to_str((int)value);

	cvttss2si eax, DWORD PTR value$[rsp]
	mov	ecx, eax
	call	?int_to_str@@YAPEBDH@Z			; int_to_str
	mov	QWORD PTR int_ptr$[rsp], rax

; 76   : 	char* float_ptr = float_to_string_output;

	lea	rax, OFFSET FLAT:?float_to_string_output@@3PADA ; float_to_string_output
	mov	QWORD PTR float_ptr$[rsp], rax

; 77   : 
; 78   : 	if (value < 0) {

	xorps	xmm0, xmm0
	comiss	xmm0, DWORD PTR value$[rsp]
	jbe	SHORT $LN6@ftoa

; 79   : 		value *= -1;

	movss	xmm0, DWORD PTR value$[rsp]
	mulss	xmm0, DWORD PTR __real@bf800000
	movss	DWORD PTR value$[rsp], xmm0
$LN6@ftoa:
$LN5@ftoa:

; 80   : 	}
; 81   : 
; 82   : 
; 83   : 	while (*int_ptr != 0) {

	mov	rax, QWORD PTR int_ptr$[rsp]
	movsx	eax, BYTE PTR [rax]
	test	eax, eax
	je	SHORT $LN4@ftoa

; 84   : 		*float_ptr = *int_ptr;

	mov	rax, QWORD PTR float_ptr$[rsp]
	mov	rcx, QWORD PTR int_ptr$[rsp]
	movzx	ecx, BYTE PTR [rcx]
	mov	BYTE PTR [rax], cl

; 85   : 		int_ptr++;

	mov	rax, QWORD PTR int_ptr$[rsp]
	inc	rax
	mov	QWORD PTR int_ptr$[rsp], rax

; 86   : 		float_ptr++;

	mov	rax, QWORD PTR float_ptr$[rsp]
	inc	rax
	mov	QWORD PTR float_ptr$[rsp], rax

; 87   : 	}

	jmp	SHORT $LN5@ftoa
$LN4@ftoa:

; 88   : 
; 89   : 	*float_ptr = '.';

	mov	rax, QWORD PTR float_ptr$[rsp]
	mov	BYTE PTR [rax], 46			; 0000002eH

; 90   : 	float_ptr++;

	mov	rax, QWORD PTR float_ptr$[rsp]
	inc	rax
	mov	QWORD PTR float_ptr$[rsp], rax

; 91   : 
; 92   : 	float new_value = value - (int)value;

	cvttss2si eax, DWORD PTR value$[rsp]
	cvtsi2ss xmm0, eax
	movss	xmm1, DWORD PTR value$[rsp]
	subss	xmm1, xmm0
	movaps	xmm0, xmm1
	movss	DWORD PTR new_value$[rsp], xmm0

; 93   : 
; 94   : 	for (uint8_t i = 0; i < decimal_places; i++) {

	mov	BYTE PTR i$1[rsp], 0
	jmp	SHORT $LN3@ftoa
$LN2@ftoa:
	movzx	eax, BYTE PTR i$1[rsp]
	inc	al
	mov	BYTE PTR i$1[rsp], al
$LN3@ftoa:
	movzx	eax, BYTE PTR i$1[rsp]
	movzx	ecx, BYTE PTR decimal_places$[rsp]
	cmp	eax, ecx
	jge	SHORT $LN1@ftoa

; 95   : 		new_value *= 10;

	movss	xmm0, DWORD PTR new_value$[rsp]
	mulss	xmm0, DWORD PTR __real@41200000
	movss	DWORD PTR new_value$[rsp], xmm0

; 96   : 		*float_ptr = (int)new_value + 48;

	cvttss2si eax, DWORD PTR new_value$[rsp]
	add	eax, 48					; 00000030H
	mov	rcx, QWORD PTR float_ptr$[rsp]
	mov	BYTE PTR [rcx], al

; 97   : 		new_value -= (int)new_value;

	cvttss2si eax, DWORD PTR new_value$[rsp]
	cvtsi2ss xmm0, eax
	movss	xmm1, DWORD PTR new_value$[rsp]
	subss	xmm1, xmm0
	movaps	xmm0, xmm1
	movss	DWORD PTR new_value$[rsp], xmm0

; 98   : 		float_ptr++;

	mov	rax, QWORD PTR float_ptr$[rsp]
	inc	rax
	mov	QWORD PTR float_ptr$[rsp], rax

; 99   : 	}

	jmp	SHORT $LN2@ftoa
$LN1@ftoa:

; 100  : 
; 101  : 	*float_ptr = 0;

	mov	rax, QWORD PTR float_ptr$[rsp]
	mov	BYTE PTR [rax], 0

; 102  : 
; 103  : 	return float_to_string_output;

	lea	rax, OFFSET FLAT:?float_to_string_output@@3PADA ; float_to_string_output

; 104  : }

	add	rsp, 72					; 00000048H
	ret	0
?ftoa@@YAPEADME@Z ENDP					; ftoa
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\stdio.cpp
_TEXT	SEGMENT
size$ = 0
index$ = 1
remainder$1 = 2
remainder$ = 3
new_value$ = 8
size_tester$ = 16
value$ = 48
?int_to_str@@YAPEBDH@Z PROC				; int_to_str

; 50   : const char* int_to_str (int value) {

$LN7:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 40					; 00000028H

; 51   : 	uint8_t size = 0;

	mov	BYTE PTR size$[rsp], 0

; 52   : 	uint64_t size_tester = (uint64_t)value;

	movsxd	rax, DWORD PTR value$[rsp]
	mov	QWORD PTR size_tester$[rsp], rax
$LN4@int_to_str:

; 53   : 	while (size_tester / 10 > 0) {

	xor	edx, edx
	mov	rax, QWORD PTR size_tester$[rsp]
	mov	ecx, 10
	div	rcx
	test	rax, rax
	jbe	SHORT $LN3@int_to_str

; 54   : 		size_tester /= 10;

	xor	edx, edx
	mov	rax, QWORD PTR size_tester$[rsp]
	mov	ecx, 10
	div	rcx
	mov	QWORD PTR size_tester$[rsp], rax

; 55   : 		size++;

	movzx	eax, BYTE PTR size$[rsp]
	inc	al
	mov	BYTE PTR size$[rsp], al

; 56   : 	}

	jmp	SHORT $LN4@int_to_str
$LN3@int_to_str:

; 57   : 
; 58   : 	uint8_t index = 0;

	mov	BYTE PTR index$[rsp], 0

; 59   : 	uint64_t new_value = (uint64_t)value;

	movsxd	rax, DWORD PTR value$[rsp]
	mov	QWORD PTR new_value$[rsp], rax
$LN2@int_to_str:

; 60   : 	while (new_value / 10 > 0) {

	xor	edx, edx
	mov	rax, QWORD PTR new_value$[rsp]
	mov	ecx, 10
	div	rcx
	test	rax, rax
	jbe	SHORT $LN1@int_to_str

; 61   : 		uint8_t remainder = new_value % 10;

	xor	edx, edx
	mov	rax, QWORD PTR new_value$[rsp]
	mov	ecx, 10
	div	rcx
	mov	rax, rdx
	mov	BYTE PTR remainder$1[rsp], al

; 62   : 		new_value /= 10;

	xor	edx, edx
	mov	rax, QWORD PTR new_value$[rsp]
	mov	ecx, 10
	div	rcx
	mov	QWORD PTR new_value$[rsp], rax

; 63   : 		integer_buffer[size - index] = remainder + 48;

	movzx	eax, BYTE PTR remainder$1[rsp]
	add	eax, 48					; 00000030H
	movzx	ecx, BYTE PTR size$[rsp]
	movzx	edx, BYTE PTR index$[rsp]
	sub	ecx, edx
	movsxd	rcx, ecx
	lea	rdx, OFFSET FLAT:?integer_buffer@@3PADA	; integer_buffer
	mov	BYTE PTR [rdx+rcx], al

; 64   : 		index++;

	movzx	eax, BYTE PTR index$[rsp]
	inc	al
	mov	BYTE PTR index$[rsp], al

; 65   : 	}

	jmp	SHORT $LN2@int_to_str
$LN1@int_to_str:

; 66   : 
; 67   : 	uint8_t remainder = new_value % 10;

	xor	edx, edx
	mov	rax, QWORD PTR new_value$[rsp]
	mov	ecx, 10
	div	rcx
	mov	rax, rdx
	mov	BYTE PTR remainder$[rsp], al

; 68   : 	integer_buffer[size - index] = remainder + 48;

	movzx	eax, BYTE PTR remainder$[rsp]
	add	eax, 48					; 00000030H
	movzx	ecx, BYTE PTR size$[rsp]
	movzx	edx, BYTE PTR index$[rsp]
	sub	ecx, edx
	movsxd	rcx, ecx
	lea	rdx, OFFSET FLAT:?integer_buffer@@3PADA	; integer_buffer
	mov	BYTE PTR [rdx+rcx], al

; 69   : 	integer_buffer[size + 1] = 0;

	movzx	eax, BYTE PTR size$[rsp]
	inc	eax
	cdqe
	lea	rcx, OFFSET FLAT:?integer_buffer@@3PADA	; integer_buffer
	mov	BYTE PTR [rcx+rax], 0

; 70   : 	return integer_buffer;

	lea	rax, OFFSET FLAT:?integer_buffer@@3PADA	; integer_buffer

; 71   : }

	add	rsp, 40					; 00000028H
	ret	0
?int_to_str@@YAPEBDH@Z ENDP				; int_to_str
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\stdio.cpp
_TEXT	SEGMENT
buf$ = 8
source$ = 16
?atow@@YAXPEADPEBD@Z PROC				; atow

; 44   : {

	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
$LN2@atow:

; 45   : 	while(*source != 0)*buf++ = *source++;

	mov	rax, QWORD PTR source$[rsp]
	movsx	eax, BYTE PTR [rax]
	test	eax, eax
	je	SHORT $LN1@atow
	mov	rax, QWORD PTR buf$[rsp]
	mov	rcx, QWORD PTR source$[rsp]
	movzx	ecx, BYTE PTR [rcx]
	mov	BYTE PTR [rax], cl
	mov	rax, QWORD PTR buf$[rsp]
	inc	rax
	mov	QWORD PTR buf$[rsp], rax
	mov	rax, QWORD PTR source$[rsp]
	inc	rax
	mov	QWORD PTR source$[rsp], rax
	jmp	SHORT $LN2@atow
$LN1@atow:

; 46   : 	*buf = '\0';

	mov	rax, QWORD PTR buf$[rsp]
	mov	BYTE PTR [rax], 0

; 47   : }

	ret	0
?atow@@YAXPEADPEBD@Z ENDP				; atow
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\stdio.cpp
_TEXT	SEGMENT
c$1 = 32
args$ = 40
buf$2 = 48
buf$3 = 52
i$4 = 56
i$5 = 64
width$6 = 72
x$7 = 80
x$8 = 88
x$9 = 96
len$10 = 104
buffer$11 = 112
buffer$12 = 192
format$ = 288
?printf@@YAXPEBDZZ PROC					; printf

; 107  : {

$LN26:
	mov	QWORD PTR [rsp+8], rcx
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+32], r9
	sub	rsp, 280				; 00000118H

; 108  : 
; 109  : 	if (!is_console_initialized()) {

	call	?is_console_initialized@@YA_NXZ		; is_console_initialized
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN23@printf

; 110  : 		debug_print (format);

	mov	rcx, QWORD PTR format$[rsp]
	call	?debug_print@@YAXPEBDZZ			; debug_print

; 111  : 		return;

	jmp	$LN24@printf
$LN23@printf:

; 112  : 	}
; 113  : 
; 114  : 	_va_list_ args;
; 115  : 	va_start(args, format);

	lea	rax, QWORD PTR format$[rsp+8]
	mov	QWORD PTR args$[rsp], rax
$LN22@printf:

; 116  : 
; 117  : 	while (*format)

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	test	eax, eax
	je	$LN21@printf

; 118  : 	{
; 119  : 		if (*format == '%')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 37					; 00000025H
	jne	$LN20@printf

; 120  : 		{
; 121  : 			++format;

	mov	rax, QWORD PTR format$[rsp]
	inc	rax
	mov	QWORD PTR format$[rsp], rax

; 122  : 			if (*format == 'd')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 100				; 00000064H
	jne	$LN19@printf

; 123  : 			{
; 124  : 				size_t width = 0;

	mov	QWORD PTR width$6[rsp], 0

; 125  : 				if (format[1] == '.')

	mov	eax, 1
	imul	rax, 1
	mov	rcx, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 46					; 0000002eH
	jne	$LN18@printf

; 126  : 				{
; 127  : 					for (size_t i = 2; format[i] >= '0' && format[i] <= '9'; ++i)

	mov	QWORD PTR i$4[rsp], 2
	jmp	SHORT $LN17@printf
$LN16@printf:
	mov	rax, QWORD PTR i$4[rsp]
	inc	rax
	mov	QWORD PTR i$4[rsp], rax
$LN17@printf:
	mov	rax, QWORD PTR i$4[rsp]
	mov	rcx, QWORD PTR format$[rsp]
	add	rcx, rax
	mov	rax, rcx
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 48					; 00000030H
	jl	SHORT $LN15@printf
	mov	rax, QWORD PTR i$4[rsp]
	mov	rcx, QWORD PTR format$[rsp]
	add	rcx, rax
	mov	rax, rcx
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 57					; 00000039H
	jg	SHORT $LN15@printf

; 128  : 					{
; 129  : 						width *= 10;

	mov	rax, QWORD PTR width$6[rsp]
	imul	rax, 10
	mov	QWORD PTR width$6[rsp], rax

; 130  : 						width += format[i] - '0';

	mov	rax, QWORD PTR i$4[rsp]
	mov	rcx, QWORD PTR format$[rsp]
	add	rcx, rax
	mov	rax, rcx
	movsx	eax, BYTE PTR [rax]
	sub	eax, 48					; 00000030H
	cdqe
	mov	rcx, QWORD PTR width$6[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR width$6[rsp], rax

; 131  : 					}

	jmp	SHORT $LN16@printf
$LN15@printf:
$LN18@printf:

; 132  : 				}
; 133  : 				size_t i = va_arg(args, size_t);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	rax, QWORD PTR [rax-8]
	mov	QWORD PTR i$5[rsp], rax

; 134  : 				char buffer[sizeof(size_t) * 8 + 1];
; 135  : 			//	size_t len
; 136  : 				if (i < 0) {

	cmp	QWORD PTR i$5[rsp], 0
	jae	SHORT $LN14@printf

; 137  : 					i = +i;

	mov	rax, QWORD PTR i$5[rsp]
	mov	QWORD PTR i$5[rsp], rax

; 138  : 					sztoa (i,buffer,10);

	mov	r8d, 10
	lea	rdx, QWORD PTR buffer$11[rsp]
	mov	rcx, QWORD PTR i$5[rsp]
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 139  : 				}else {

	jmp	SHORT $LN13@printf
$LN14@printf:

; 140  : 					sztoa(i, buffer, 10);

	mov	r8d, 10
	lea	rdx, QWORD PTR buffer$11[rsp]
	mov	rcx, QWORD PTR i$5[rsp]
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 141  : 					size_t len = strlen(buffer);

	lea	rcx, QWORD PTR buffer$11[rsp]
	call	?strlen@@YA_KPEBD@Z			; strlen
	mov	QWORD PTR len$10[rsp], rax
$LN13@printf:

; 142  : 				}
; 143  : 			/*	while (len++ < width)
; 144  : 					puts("0");*/
; 145  : 				puts(buffer);

	lea	rcx, QWORD PTR buffer$11[rsp]
	call	?puts@@YAXPEAD@Z			; puts
	jmp	$LN12@printf
$LN19@printf:

; 146  : 			}
; 147  : 			else if (*format == 'c')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 99					; 00000063H
	jne	SHORT $LN11@printf

; 148  : 			{
; 149  : 				char c = va_arg(args, char);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 4
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	movzx	eax, BYTE PTR [rax-4]
	mov	BYTE PTR c$1[rsp], al

; 150  : 				//char buffer[sizeof(size_t) * 8 + 1];
; 151  : 				//sztoa(c, buffer, 10);
; 152  : 				//puts(buffer);
; 153  : 				puts((char*)c);

	movsx	rax, BYTE PTR c$1[rsp]
	mov	rcx, rax
	call	?puts@@YAXPEAD@Z			; puts
	jmp	$LN10@printf
$LN11@printf:

; 154  : 			}
; 155  : 			else if (*format == 'x')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 120				; 00000078H
	jne	SHORT $LN9@printf

; 156  : 			{
; 157  : 				size_t x = va_arg(args, size_t);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	rax, QWORD PTR [rax-8]
	mov	QWORD PTR x$9[rsp], rax

; 158  : 				char buffer[sizeof(size_t) * 8 + 1];
; 159  : 				sztoa(x, buffer, 16);

	mov	r8d, 16
	lea	rdx, QWORD PTR buffer$12[rsp]
	mov	rcx, QWORD PTR x$9[rsp]
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 160  : 				//puts("0x");
; 161  : 				puts(buffer);

	lea	rcx, QWORD PTR buffer$12[rsp]
	call	?puts@@YAXPEAD@Z			; puts
	jmp	$LN8@printf
$LN9@printf:

; 162  : 			}
; 163  : 			else if (*format == 's')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 115				; 00000073H
	jne	SHORT $LN7@printf

; 164  : 			{
; 165  : 				char* x = va_arg(args, char*);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	rax, QWORD PTR [rax-8]
	mov	QWORD PTR x$8[rsp], rax

; 166  : 				puts(x);

	mov	rcx, QWORD PTR x$8[rsp]
	call	?puts@@YAXPEAD@Z			; puts
	jmp	$LN6@printf
$LN7@printf:

; 167  : 			}
; 168  : 			else if (*format == 'f')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 102				; 00000066H
	jne	SHORT $LN5@printf

; 169  : 			{
; 170  : 				double x = va_arg(args, double);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	movsdx	xmm0, QWORD PTR [rax-8]
	movsdx	QWORD PTR x$7[rsp], xmm0

; 171  : 				puts(ftoa(x,2));

	cvtsd2ss xmm0, QWORD PTR x$7[rsp]
	mov	dl, 2
	call	?ftoa@@YAPEADME@Z			; ftoa
	mov	rcx, rax
	call	?puts@@YAXPEAD@Z			; puts
	jmp	SHORT $LN4@printf
$LN5@printf:

; 172  : 			}
; 173  : 			else if (*format == '%')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 37					; 00000025H
	jne	SHORT $LN3@printf

; 174  : 			{
; 175  : 				puts(".");

	lea	rcx, OFFSET FLAT:$SG3063
	call	?puts@@YAXPEAD@Z			; puts

; 176  : 			}
; 177  : 			else

	jmp	SHORT $LN2@printf
$LN3@printf:

; 178  : 			{
; 179  : 				char buf[3];
; 180  : 				buf[0] = '%'; buf[1] = *format; buf[2] = '\0';

	mov	eax, 1
	imul	rax, 0
	mov	BYTE PTR buf$3[rsp+rax], 37		; 00000025H
	mov	eax, 1
	imul	rax, 1
	mov	rcx, QWORD PTR format$[rsp]
	movzx	ecx, BYTE PTR [rcx]
	mov	BYTE PTR buf$3[rsp+rax], cl
	mov	eax, 1
	imul	rax, 2
	mov	BYTE PTR buf$3[rsp+rax], 0

; 181  : 				puts(buf);

	lea	rcx, QWORD PTR buf$3[rsp]
	call	?puts@@YAXPEAD@Z			; puts
$LN2@printf:
$LN4@printf:
$LN6@printf:
$LN8@printf:
$LN10@printf:
$LN12@printf:

; 182  : 			}
; 183  : 		}
; 184  : 		else

	jmp	SHORT $LN1@printf
$LN20@printf:

; 185  : 		{
; 186  : 			char buf[2];
; 187  : 			buf[0] = *format; buf[1] = '\0';

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR format$[rsp]
	movzx	ecx, BYTE PTR [rcx]
	mov	BYTE PTR buf$2[rsp+rax], cl
	mov	eax, 1
	imul	rax, 1
	mov	BYTE PTR buf$2[rsp+rax], 0

; 188  : 			puts(buf);

	lea	rcx, QWORD PTR buf$2[rsp]
	call	?puts@@YAXPEAD@Z			; puts
$LN1@printf:

; 189  : 		}
; 190  : 		++format;

	mov	rax, QWORD PTR format$[rsp]
	inc	rax
	mov	QWORD PTR format$[rsp], rax

; 191  : 	}

	jmp	$LN22@printf
$LN21@printf:
$LN24@printf:

; 192  : 	va_end(args);
; 193  : }

	add	rsp, 280				; 00000118H
	ret	0
?printf@@YAXPEBDZZ ENDP					; printf
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\stdio.cpp
_TEXT	SEGMENT
tmp$1 = 0
i$ = 4
z$2 = 8
tv67 = 16
tv74 = 24
value$ = 48
str$ = 56
base$ = 64
?sztoa@@YAPEAD_KPEADH@Z PROC				; sztoa

; 24   : {

$LN11:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 25   : 	if (base < 2 || base > 16)

	cmp	DWORD PTR base$[rsp], 2
	jl	SHORT $LN7@sztoa
	cmp	DWORD PTR base$[rsp], 16
	jle	SHORT $LN8@sztoa
$LN7@sztoa:

; 26   : 		return nullptr;

	xor	eax, eax
	jmp	$LN9@sztoa
$LN8@sztoa:

; 27   : 	unsigned int i = 0;

	mov	DWORD PTR i$[rsp], 0
$LN6@sztoa:

; 28   : 	do 
; 29   : 	{
; 30   : 		str[++i] = chars[value%base];

	mov	eax, DWORD PTR i$[rsp]
	inc	eax
	mov	DWORD PTR i$[rsp], eax
	mov	eax, DWORD PTR i$[rsp]
	mov	QWORD PTR tv67[rsp], rax
	movsxd	rcx, DWORD PTR base$[rsp]
	xor	edx, edx
	mov	rax, QWORD PTR value$[rsp]
	div	rcx
	mov	rax, rdx
	mov	rcx, QWORD PTR str$[rsp]
	mov	rdx, QWORD PTR chars
	movzx	eax, BYTE PTR [rdx+rax]
	mov	rdx, QWORD PTR tv67[rsp]
	mov	BYTE PTR [rcx+rdx], al

; 31   : 		value /= base;

	movsxd	rax, DWORD PTR base$[rsp]
	mov	QWORD PTR tv74[rsp], rax
	xor	edx, edx
	mov	rax, QWORD PTR value$[rsp]
	mov	rcx, QWORD PTR tv74[rsp]
	div	rcx
	mov	QWORD PTR value$[rsp], rax

; 32   : 	} while (value != 0);

	cmp	QWORD PTR value$[rsp], 0
	jne	SHORT $LN6@sztoa

; 33   : 	str[0] = '\0';

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR str$[rsp]
	mov	BYTE PTR [rcx+rax], 0

; 34   : 	for (unsigned int z = 0; z < i; ++z, --i)

	mov	DWORD PTR z$2[rsp], 0
	jmp	SHORT $LN3@sztoa
$LN2@sztoa:
	mov	eax, DWORD PTR z$2[rsp]
	inc	eax
	mov	DWORD PTR z$2[rsp], eax
	mov	eax, DWORD PTR i$[rsp]
	dec	eax
	mov	DWORD PTR i$[rsp], eax
$LN3@sztoa:
	mov	eax, DWORD PTR i$[rsp]
	cmp	DWORD PTR z$2[rsp], eax
	jae	SHORT $LN1@sztoa

; 35   : 	{
; 36   : 		char tmp = str[z];

	mov	eax, DWORD PTR z$2[rsp]
	mov	rcx, QWORD PTR str$[rsp]
	movzx	eax, BYTE PTR [rcx+rax]
	mov	BYTE PTR tmp$1[rsp], al

; 37   : 		str[z] = str[i];

	mov	eax, DWORD PTR i$[rsp]
	mov	ecx, DWORD PTR z$2[rsp]
	mov	rdx, QWORD PTR str$[rsp]
	mov	r8, QWORD PTR str$[rsp]
	movzx	eax, BYTE PTR [r8+rax]
	mov	BYTE PTR [rdx+rcx], al

; 38   : 		str[i] = tmp;

	mov	eax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR str$[rsp]
	movzx	edx, BYTE PTR tmp$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 39   : 	}

	jmp	SHORT $LN2@sztoa
$LN1@sztoa:

; 40   : 	return str;

	mov	rax, QWORD PTR str$[rsp]
$LN9@sztoa:

; 41   : }

	add	rsp, 40					; 00000028H
	ret	0
?sztoa@@YAPEAD_KPEADH@Z ENDP				; sztoa
_TEXT	ENDS
END
