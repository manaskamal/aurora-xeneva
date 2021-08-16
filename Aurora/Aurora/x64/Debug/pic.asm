; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?pic_interrupt_eoi@@YAXI@Z			; pic_interrupt_eoi
PUBLIC	?initialize_pic@@YAXEE@Z			; initialize_pic
PUBLIC	?pic_send_command@@YAXEE@Z			; pic_send_command
PUBLIC	?pic_send_data@@YAXEE@Z				; pic_send_data
PUBLIC	?pic_read_data@@YAEE@Z				; pic_read_data
EXTRN	x64_cli:PROC
EXTRN	x64_inportb:PROC
EXTRN	x64_outportb:PROC
pdata	SEGMENT
$pdata$?pic_interrupt_eoi@@YAXI@Z DD imagerel $LN5
	DD	imagerel $LN5+47
	DD	imagerel $unwind$?pic_interrupt_eoi@@YAXI@Z
$pdata$?initialize_pic@@YAXEE@Z DD imagerel $LN3
	DD	imagerel $LN3+162
	DD	imagerel $unwind$?initialize_pic@@YAXEE@Z
$pdata$?pic_send_command@@YAXEE@Z DD imagerel $LN6
	DD	imagerel $LN6+84
	DD	imagerel $unwind$?pic_send_command@@YAXEE@Z
$pdata$?pic_send_data@@YAXEE@Z DD imagerel $LN6
	DD	imagerel $LN6+84
	DD	imagerel $unwind$?pic_send_data@@YAXEE@Z
$pdata$?pic_read_data@@YAEE@Z DD imagerel $LN6
	DD	imagerel $LN6+77
	DD	imagerel $unwind$?pic_read_data@@YAEE@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?pic_interrupt_eoi@@YAXI@Z DD 010801H
	DD	04208H
$unwind$?initialize_pic@@YAXEE@Z DD 010c01H
	DD	0620cH
$unwind$?pic_send_command@@YAXEE@Z DD 010c01H
	DD	0620cH
$unwind$?pic_send_data@@YAXEE@Z DD 010c01H
	DD	0620cH
$unwind$?pic_read_data@@YAEE@Z DD 010801H
	DD	06208H
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\pic.cpp
_TEXT	SEGMENT
reg$ = 32
tv68 = 36
pic_num$ = 64
?pic_read_data@@YAEE@Z PROC				; pic_read_data

; 33   : uint8_t pic_read_data (uint8_t pic_num) {

$LN6:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 56					; 00000038H

; 34   : 
; 35   : 	if (pic_num > 1)

	movzx	eax, BYTE PTR pic_num$[rsp]
	cmp	eax, 1
	jle	SHORT $LN1@pic_read_d

; 36   : 		return 0;

	xor	al, al
	jmp	SHORT $LN2@pic_read_d
$LN1@pic_read_d:

; 37   : 
; 38   : 	uint8_t reg = (pic_num == 1) ? I86_PIC2_REG_DATA : I86_PIC1_REG_DATA;

	movzx	eax, BYTE PTR pic_num$[rsp]
	cmp	eax, 1
	jne	SHORT $LN4@pic_read_d
	mov	DWORD PTR tv68[rsp], 161		; 000000a1H
	jmp	SHORT $LN5@pic_read_d
$LN4@pic_read_d:
	mov	DWORD PTR tv68[rsp], 33			; 00000021H
$LN5@pic_read_d:
	movzx	eax, BYTE PTR tv68[rsp]
	mov	BYTE PTR reg$[rsp], al

; 39   : 	return x64_inportb (reg);

	movzx	eax, BYTE PTR reg$[rsp]
	movzx	ecx, ax
	call	x64_inportb
$LN2@pic_read_d:

; 40   : }

	add	rsp, 56					; 00000038H
	ret	0
?pic_read_data@@YAEE@Z ENDP				; pic_read_data
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\pic.cpp
_TEXT	SEGMENT
reg$ = 32
tv68 = 36
data$ = 64
pic_num$ = 72
?pic_send_data@@YAXEE@Z PROC				; pic_send_data

; 24   : void pic_send_data (uint8_t data, uint8_t pic_num) {

$LN6:
	mov	BYTE PTR [rsp+16], dl
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 56					; 00000038H

; 25   : 
; 26   : 	if (pic_num > 1)

	movzx	eax, BYTE PTR pic_num$[rsp]
	cmp	eax, 1
	jle	SHORT $LN1@pic_send_d

; 27   : 		return;

	jmp	SHORT $LN2@pic_send_d
$LN1@pic_send_d:

; 28   : 
; 29   : 	uint8_t reg = (pic_num == 1) ? I86_PIC2_REG_DATA : I86_PIC1_REG_DATA;

	movzx	eax, BYTE PTR pic_num$[rsp]
	cmp	eax, 1
	jne	SHORT $LN4@pic_send_d
	mov	DWORD PTR tv68[rsp], 161		; 000000a1H
	jmp	SHORT $LN5@pic_send_d
$LN4@pic_send_d:
	mov	DWORD PTR tv68[rsp], 33			; 00000021H
$LN5@pic_send_d:
	movzx	eax, BYTE PTR tv68[rsp]
	mov	BYTE PTR reg$[rsp], al

; 30   : 	x64_outportb (reg, data);

	movzx	eax, BYTE PTR reg$[rsp]
	movzx	edx, BYTE PTR data$[rsp]
	movzx	ecx, ax
	call	x64_outportb
$LN2@pic_send_d:

; 31   : }

	add	rsp, 56					; 00000038H
	ret	0
?pic_send_data@@YAXEE@Z ENDP				; pic_send_data
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\pic.cpp
_TEXT	SEGMENT
reg$ = 32
tv68 = 36
cmd$ = 64
pic_num$ = 72
?pic_send_command@@YAXEE@Z PROC				; pic_send_command

; 15   : void pic_send_command (uint8_t cmd, uint8_t pic_num) {

$LN6:
	mov	BYTE PTR [rsp+16], dl
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 56					; 00000038H

; 16   : 	
; 17   : 	if (pic_num > 1)

	movzx	eax, BYTE PTR pic_num$[rsp]
	cmp	eax, 1
	jle	SHORT $LN1@pic_send_c

; 18   : 		return;

	jmp	SHORT $LN2@pic_send_c
$LN1@pic_send_c:

; 19   : 
; 20   : 	uint8_t reg = (pic_num == 1) ? I86_PIC2_REG_COMMAND : I86_PIC1_REG_COMMAND;

	movzx	eax, BYTE PTR pic_num$[rsp]
	cmp	eax, 1
	jne	SHORT $LN4@pic_send_c
	mov	DWORD PTR tv68[rsp], 160		; 000000a0H
	jmp	SHORT $LN5@pic_send_c
$LN4@pic_send_c:
	mov	DWORD PTR tv68[rsp], 32			; 00000020H
$LN5@pic_send_c:
	movzx	eax, BYTE PTR tv68[rsp]
	mov	BYTE PTR reg$[rsp], al

; 21   : 	x64_outportb (reg, cmd);

	movzx	eax, BYTE PTR reg$[rsp]
	movzx	edx, BYTE PTR cmd$[rsp]
	movzx	ecx, ax
	call	x64_outportb
$LN2@pic_send_c:

; 22   : }

	add	rsp, 56					; 00000038H
	ret	0
?pic_send_command@@YAXEE@Z ENDP				; pic_send_command
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\pic.cpp
_TEXT	SEGMENT
icw$ = 32
base0$ = 64
base1$ = 72
?initialize_pic@@YAXEE@Z PROC				; initialize_pic

; 55   : void initialize_pic ( uint8_t base0, uint8_t base1) {

$LN3:
	mov	BYTE PTR [rsp+16], dl
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 56					; 00000038H

; 56   : 
; 57   : 	uint8_t icw = 0;

	mov	BYTE PTR icw$[rsp], 0

; 58   : 
; 59   : 	x64_cli ();

	call	x64_cli

; 60   : 
; 61   : 	icw = (icw & ~I86_PIC_ICW1_MASK_INIT) | I86_PIC_ICW1_INIT_YES;

	movzx	eax, BYTE PTR icw$[rsp]
	and	eax, -17
	or	eax, 16
	mov	BYTE PTR icw$[rsp], al

; 62   : 	icw = (icw & ~I86_PIC_ICW1_MASK_IC4) | I86_PIC_ICW1_IC4_EXPECT;

	movzx	eax, BYTE PTR icw$[rsp]
	and	eax, -2
	or	eax, 1
	mov	BYTE PTR icw$[rsp], al

; 63   : 
; 64   : 	pic_send_command (icw, 0);

	xor	edx, edx
	movzx	ecx, BYTE PTR icw$[rsp]
	call	?pic_send_command@@YAXEE@Z		; pic_send_command

; 65   : 	pic_send_command (icw, 1);

	mov	dl, 1
	movzx	ecx, BYTE PTR icw$[rsp]
	call	?pic_send_command@@YAXEE@Z		; pic_send_command

; 66   : 
; 67   : 	//! send init control word 2
; 68   : 	pic_send_data (base0, 0);

	xor	edx, edx
	movzx	ecx, BYTE PTR base0$[rsp]
	call	?pic_send_data@@YAXEE@Z			; pic_send_data

; 69   : 	pic_send_data (base1, 1);

	mov	dl, 1
	movzx	ecx, BYTE PTR base1$[rsp]
	call	?pic_send_data@@YAXEE@Z			; pic_send_data

; 70   : 
; 71   : 	pic_send_data (0x04, 0);

	xor	edx, edx
	mov	cl, 4
	call	?pic_send_data@@YAXEE@Z			; pic_send_data

; 72   : 	pic_send_data (0x02, 1);

	mov	dl, 1
	mov	cl, 2
	call	?pic_send_data@@YAXEE@Z			; pic_send_data

; 73   : 
; 74   : 	icw = (icw & ~I86_PIC_ICW4_MASK_UPM) | I86_PIC_ICW4_UPM_86MODE;

	movzx	eax, BYTE PTR icw$[rsp]
	and	eax, -2
	or	eax, 1
	mov	BYTE PTR icw$[rsp], al

; 75   : 
; 76   : 	pic_send_data (icw, 0);

	xor	edx, edx
	movzx	ecx, BYTE PTR icw$[rsp]
	call	?pic_send_data@@YAXEE@Z			; pic_send_data

; 77   : 	pic_send_data (icw, 1);

	mov	dl, 1
	movzx	ecx, BYTE PTR icw$[rsp]
	call	?pic_send_data@@YAXEE@Z			; pic_send_data

; 78   : }

	add	rsp, 56					; 00000038H
	ret	0
?initialize_pic@@YAXEE@Z ENDP				; initialize_pic
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\pic.cpp
_TEXT	SEGMENT
intno$ = 48
?pic_interrupt_eoi@@YAXI@Z PROC				; pic_interrupt_eoi

; 42   : void pic_interrupt_eoi (unsigned int intno) {

$LN5:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 40					; 00000028H

; 43   : 
; 44   : 	if (intno > 16)

	cmp	DWORD PTR intno$[rsp], 16
	jbe	SHORT $LN2@pic_interr

; 45   : 		return;

	jmp	SHORT $LN3@pic_interr
$LN2@pic_interr:

; 46   : 
; 47   : 	if (intno >= 8)

	cmp	DWORD PTR intno$[rsp], 8
	jb	SHORT $LN1@pic_interr

; 48   : 		pic_send_command(I86_PIC_OCW2_MASK_EOI, 1);

	mov	dl, 1
	mov	cl, 32					; 00000020H
	call	?pic_send_command@@YAXEE@Z		; pic_send_command
$LN1@pic_interr:

; 49   : 
; 50   : 	pic_send_command (I86_PIC_OCW2_MASK_EOI, 0);

	xor	edx, edx
	mov	cl, 32					; 00000020H
	call	?pic_send_command@@YAXEE@Z		; pic_send_command
$LN3@pic_interr:

; 51   : }

	add	rsp, 40					; 00000028H
	ret	0
?pic_interrupt_eoi@@YAXI@Z ENDP				; pic_interrupt_eoi
_TEXT	ENDS
END
