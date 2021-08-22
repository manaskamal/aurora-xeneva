; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG2891	DB	'0123456789ABCDEF', 00H
	ORG $+3
$SG2947	DB	'0', 00H
	ORG $+2
$SG2984	DB	'.', 00H
CONST	ENDS
_DATA	SEGMENT
chars	DQ	FLAT:$SG2891
_DATA	ENDS
PUBLIC	?sztoa@@YAPEAD_KPEADH@Z				; sztoa
PUBLIC	?printf@@YAXPEBDZZ				; printf
PUBLIC	?atow@@YAXPEADPEBD@Z				; atow
EXTRN	?strlen@@YA_KPEBD@Z:PROC			; strlen
EXTRN	?puts@@YAXPEAD@Z:PROC				; puts
pdata	SEGMENT
$pdata$?sztoa@@YAPEAD_KPEADH@Z DD imagerel $LN11
	DD	imagerel $LN11+275
	DD	imagerel $unwind$?sztoa@@YAPEAD_KPEADH@Z
$pdata$?printf@@YAXPEBDZZ DD imagerel $LN23
	DD	imagerel $LN23+844
	DD	imagerel $unwind$?printf@@YAXPEBDZZ
pdata	ENDS
xdata	SEGMENT
$unwind$?sztoa@@YAPEAD_KPEADH@Z DD 011301H
	DD	04213H
$unwind$?printf@@YAXPEBDZZ DD 021b01H
	DD	02f011bH
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\stdio.cpp
_TEXT	SEGMENT
buf$ = 8
source$ = 16
?atow@@YAXPEADPEBD@Z PROC				; atow

; 38   : {

	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
$LN2@atow:

; 39   : 	while(*source != 0)*buf++ = *source++;

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

; 40   : 	*buf = '\0';

	mov	rax, QWORD PTR buf$[rsp]
	mov	BYTE PTR [rax], 0

; 41   : }

	ret	0
?atow@@YAXPEADPEBD@Z ENDP				; atow
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\stdio.cpp
_TEXT	SEGMENT
args$ = 32
buf$1 = 40
buf$2 = 44
i$3 = 48
width$4 = 56
c$5 = 64
len$6 = 72
i$7 = 80
x$8 = 88
tv134 = 96
x$9 = 104
tv133 = 112
buffer$10 = 128
buffer$11 = 208
buffer$12 = 288
format$ = 384
?printf@@YAXPEBDZZ PROC					; printf

; 44   : {

$LN23:
	mov	QWORD PTR [rsp+8], rcx
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+32], r9
	sub	rsp, 376				; 00000178H

; 45   : 	_va_list_ args;
; 46   : 	va_start(args, format);

	lea	rax, QWORD PTR format$[rsp+8]
	mov	QWORD PTR args$[rsp], rax
$LN20@printf:

; 47   : 
; 48   : 	while (*format)

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	test	eax, eax
	je	$LN19@printf

; 49   : 	{
; 50   : 		if (*format == '%')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 37					; 00000025H
	jne	$LN18@printf

; 51   : 		{
; 52   : 			++format;

	mov	rax, QWORD PTR format$[rsp]
	inc	rax
	mov	QWORD PTR format$[rsp], rax

; 53   : 			if (*format == 'd')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 100				; 00000064H
	jne	$LN17@printf

; 54   : 			{
; 55   : 				size_t width = 0;

	mov	QWORD PTR width$4[rsp], 0

; 56   : 				if (format[1] == '.')

	mov	eax, 1
	imul	rax, 1
	mov	rcx, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 46					; 0000002eH
	jne	$LN16@printf

; 57   : 				{
; 58   : 					for (size_t i = 2; format[i] >= '0' && format[i] <= '9'; ++i)

	mov	QWORD PTR i$3[rsp], 2
	jmp	SHORT $LN15@printf
$LN14@printf:
	mov	rax, QWORD PTR i$3[rsp]
	inc	rax
	mov	QWORD PTR i$3[rsp], rax
$LN15@printf:
	mov	rax, QWORD PTR i$3[rsp]
	mov	rcx, QWORD PTR format$[rsp]
	add	rcx, rax
	mov	rax, rcx
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 48					; 00000030H
	jl	SHORT $LN13@printf
	mov	rax, QWORD PTR i$3[rsp]
	mov	rcx, QWORD PTR format$[rsp]
	add	rcx, rax
	mov	rax, rcx
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 57					; 00000039H
	jg	SHORT $LN13@printf

; 59   : 					{
; 60   : 						width *= 10;

	mov	rax, QWORD PTR width$4[rsp]
	imul	rax, 10
	mov	QWORD PTR width$4[rsp], rax

; 61   : 						width += format[i] - '0';

	mov	rax, QWORD PTR i$3[rsp]
	mov	rcx, QWORD PTR format$[rsp]
	add	rcx, rax
	mov	rax, rcx
	movsx	eax, BYTE PTR [rax]
	sub	eax, 48					; 00000030H
	cdqe
	mov	rcx, QWORD PTR width$4[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR width$4[rsp], rax

; 62   : 					}

	jmp	SHORT $LN14@printf
$LN13@printf:
$LN16@printf:

; 63   : 				}
; 64   : 				size_t i = va_arg(args, size_t);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	rax, QWORD PTR [rax-8]
	mov	QWORD PTR i$7[rsp], rax

; 65   : 				char buffer[sizeof(size_t) * 8 + 1];
; 66   : 				sztoa(i, buffer, 10);

	mov	r8d, 10
	lea	rdx, QWORD PTR buffer$10[rsp]
	mov	rcx, QWORD PTR i$7[rsp]
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 67   : 				size_t len = strlen(buffer);

	lea	rcx, QWORD PTR buffer$10[rsp]
	call	?strlen@@YA_KPEBD@Z			; strlen
	mov	QWORD PTR len$6[rsp], rax
$LN12@printf:

; 68   : 				while (len++ < width)

	mov	rax, QWORD PTR len$6[rsp]
	mov	QWORD PTR tv133[rsp], rax
	mov	rax, QWORD PTR width$4[rsp]
	mov	QWORD PTR tv134[rsp], rax
	mov	rax, QWORD PTR len$6[rsp]
	inc	rax
	mov	QWORD PTR len$6[rsp], rax
	mov	rax, QWORD PTR tv134[rsp]
	cmp	QWORD PTR tv133[rsp], rax
	jae	SHORT $LN11@printf

; 69   : 					puts("0");

	lea	rcx, OFFSET FLAT:$SG2947
	call	?puts@@YAXPEAD@Z			; puts
	jmp	SHORT $LN12@printf
$LN11@printf:

; 70   : 				puts(buffer);

	lea	rcx, QWORD PTR buffer$10[rsp]
	call	?puts@@YAXPEAD@Z			; puts
	jmp	$LN10@printf
$LN17@printf:

; 71   : 			}
; 72   : 			else if (*format == 'c')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 99					; 00000063H
	jne	SHORT $LN9@printf

; 73   : 			{
; 74   : 				int c = va_arg(args, int);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 4
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	eax, DWORD PTR [rax-4]
	mov	DWORD PTR c$5[rsp], eax

; 75   : 				char buffer[sizeof(size_t) * 8 + 1];
; 76   : 				sztoa(c, buffer, 10);

	movsxd	rax, DWORD PTR c$5[rsp]
	mov	r8d, 10
	lea	rdx, QWORD PTR buffer$11[rsp]
	mov	rcx, rax
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 77   : 				puts(buffer);

	lea	rcx, QWORD PTR buffer$11[rsp]
	call	?puts@@YAXPEAD@Z			; puts
	jmp	$LN8@printf
$LN9@printf:

; 78   : 			}
; 79   : 			else if (*format == 'x')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 120				; 00000078H
	jne	SHORT $LN7@printf

; 80   : 			{
; 81   : 				size_t x = va_arg(args, size_t);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	rax, QWORD PTR [rax-8]
	mov	QWORD PTR x$9[rsp], rax

; 82   : 				char buffer[sizeof(size_t) * 8 + 1];
; 83   : 				sztoa(x, buffer, 16);

	mov	r8d, 16
	lea	rdx, QWORD PTR buffer$12[rsp]
	mov	rcx, QWORD PTR x$9[rsp]
	call	?sztoa@@YAPEAD_KPEADH@Z			; sztoa

; 84   : 				//puts("0x");
; 85   : 				puts(buffer);

	lea	rcx, QWORD PTR buffer$12[rsp]
	call	?puts@@YAXPEAD@Z			; puts
	jmp	$LN6@printf
$LN7@printf:

; 86   : 			}
; 87   : 			else if (*format == 's')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 115				; 00000073H
	jne	SHORT $LN5@printf

; 88   : 			{
; 89   : 				char* x = va_arg(args, char*);

	mov	rax, QWORD PTR args$[rsp]
	add	rax, 8
	mov	QWORD PTR args$[rsp], rax
	mov	rax, QWORD PTR args$[rsp]
	mov	rax, QWORD PTR [rax-8]
	mov	QWORD PTR x$8[rsp], rax

; 90   : 				puts(x);

	mov	rcx, QWORD PTR x$8[rsp]
	call	?puts@@YAXPEAD@Z			; puts
	jmp	SHORT $LN4@printf
$LN5@printf:

; 91   : 			}
; 92   : 			/*else if (*format == 'f')
; 93   : 			{
; 94   : 				double x = va_arg(args, double);
; 95   : 				xput_char(ftoa(x,2));
; 96   : 			}*/
; 97   : 			else if (*format == '%')

	mov	rax, QWORD PTR format$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 37					; 00000025H
	jne	SHORT $LN3@printf

; 98   : 			{
; 99   : 				puts(".");

	lea	rcx, OFFSET FLAT:$SG2984
	call	?puts@@YAXPEAD@Z			; puts

; 100  : 			}
; 101  : 			else

	jmp	SHORT $LN2@printf
$LN3@printf:

; 102  : 			{
; 103  : 				char buf[3];
; 104  : 				buf[0] = '%'; buf[1] = *format; buf[2] = '\0';

	mov	eax, 1
	imul	rax, 0
	mov	BYTE PTR buf$2[rsp+rax], 37		; 00000025H
	mov	eax, 1
	imul	rax, 1
	mov	rcx, QWORD PTR format$[rsp]
	movzx	ecx, BYTE PTR [rcx]
	mov	BYTE PTR buf$2[rsp+rax], cl
	mov	eax, 1
	imul	rax, 2
	mov	BYTE PTR buf$2[rsp+rax], 0

; 105  : 				puts(buf);

	lea	rcx, QWORD PTR buf$2[rsp]
	call	?puts@@YAXPEAD@Z			; puts
$LN2@printf:
$LN4@printf:
$LN6@printf:
$LN8@printf:
$LN10@printf:

; 106  : 			}
; 107  : 		}
; 108  : 		else

	jmp	SHORT $LN1@printf
$LN18@printf:

; 109  : 		{
; 110  : 			char buf[2];
; 111  : 			buf[0] = *format; buf[1] = '\0';

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR format$[rsp]
	movzx	ecx, BYTE PTR [rcx]
	mov	BYTE PTR buf$1[rsp+rax], cl
	mov	eax, 1
	imul	rax, 1
	mov	BYTE PTR buf$1[rsp+rax], 0

; 112  : 			puts(buf);

	lea	rcx, QWORD PTR buf$1[rsp]
	call	?puts@@YAXPEAD@Z			; puts
$LN1@printf:

; 113  : 		}
; 114  : 		++format;

	mov	rax, QWORD PTR format$[rsp]
	inc	rax
	mov	QWORD PTR format$[rsp], rax

; 115  : 	}

	jmp	$LN20@printf
$LN19@printf:

; 116  : 	va_end(args);
; 117  : }

	add	rsp, 376				; 00000178H
	ret	0
?printf@@YAXPEBDZZ ENDP					; printf
_TEXT	ENDS
; Function compile flags: /Odtp
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

; 18   : {

$LN11:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 19   : 	if (base < 2 || base > 16)

	cmp	DWORD PTR base$[rsp], 2
	jl	SHORT $LN7@sztoa
	cmp	DWORD PTR base$[rsp], 16
	jle	SHORT $LN8@sztoa
$LN7@sztoa:

; 20   : 		return nullptr;

	xor	eax, eax
	jmp	$LN9@sztoa
$LN8@sztoa:

; 21   : 	unsigned int i = 0;

	mov	DWORD PTR i$[rsp], 0
$LN6@sztoa:

; 22   : 	do 
; 23   : 	{
; 24   : 		str[++i] = chars[value%base];

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

; 25   : 		value /= base;

	movsxd	rax, DWORD PTR base$[rsp]
	mov	QWORD PTR tv74[rsp], rax
	xor	edx, edx
	mov	rax, QWORD PTR value$[rsp]
	mov	rcx, QWORD PTR tv74[rsp]
	div	rcx
	mov	QWORD PTR value$[rsp], rax

; 26   : 	} while (value != 0);

	cmp	QWORD PTR value$[rsp], 0
	jne	SHORT $LN6@sztoa

; 27   : 	str[0] = '\0';

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR str$[rsp]
	mov	BYTE PTR [rcx+rax], 0

; 28   : 	for (unsigned int z = 0; z < i; ++z, --i)

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

; 29   : 	{
; 30   : 		char tmp = str[z];

	mov	eax, DWORD PTR z$2[rsp]
	mov	rcx, QWORD PTR str$[rsp]
	movzx	eax, BYTE PTR [rcx+rax]
	mov	BYTE PTR tmp$1[rsp], al

; 31   : 		str[z] = str[i];

	mov	eax, DWORD PTR i$[rsp]
	mov	ecx, DWORD PTR z$2[rsp]
	mov	rdx, QWORD PTR str$[rsp]
	mov	r8, QWORD PTR str$[rsp]
	movzx	eax, BYTE PTR [r8+rax]
	mov	BYTE PTR [rdx+rcx], al

; 32   : 		str[i] = tmp;

	mov	eax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR str$[rsp]
	movzx	edx, BYTE PTR tmp$1[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 33   : 	}

	jmp	SHORT $LN2@sztoa
$LN1@sztoa:

; 34   : 	return str;

	mov	rax, QWORD PTR str$[rsp]
$LN9@sztoa:

; 35   : }

	add	rsp, 40					; 00000028H
	ret	0
?sztoa@@YAPEAD_KPEADH@Z ENDP				; sztoa
_TEXT	ENDS
END
