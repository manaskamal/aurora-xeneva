; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?century@@3EA					; century
PUBLIC	?year@@3EA					; year
PUBLIC	?month@@3EA					; month
PUBLIC	?day@@3EA					; day
PUBLIC	?hour@@3EA					; hour
PUBLIC	?minute@@3EA					; minute
PUBLIC	?second@@3EA					; second
_BSS	SEGMENT
?century@@3EA DB 01H DUP (?)				; century
?year@@3EA DB	01H DUP (?)				; year
?month@@3EA DB	01H DUP (?)				; month
?day@@3EA DB	01H DUP (?)				; day
?hour@@3EA DB	01H DUP (?)				; hour
?minute@@3EA DB	01H DUP (?)				; minute
?second@@3EA DB	01H DUP (?)				; second
_BSS	ENDS
PUBLIC	?initialize_rtc@@YAXXZ				; initialize_rtc
PUBLIC	?rtc_get_year@@YAEXZ				; rtc_get_year
PUBLIC	?get_rtc_register@@YAEH@Z			; get_rtc_register
PUBLIC	?set_rtc_register@@YAXGE@Z			; set_rtc_register
PUBLIC	?is_updating_rtc@@YAHXZ				; is_updating_rtc
PUBLIC	?rtc_read_datetime@@YAXXZ			; rtc_read_datetime
PUBLIC	?rtc_clock_update@@YAX_KPEAX@Z			; rtc_clock_update
EXTRN	x64_inportb:PROC
EXTRN	x64_outportb:PROC
EXTRN	?interrupt_end@@YAXI@Z:PROC			; interrupt_end
EXTRN	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z:PROC	; interrupt_set
_BSS	SEGMENT
bcd	DB	01H DUP (?)
_BSS	ENDS
pdata	SEGMENT
$pdata$?initialize_rtc@@YAXXZ DD imagerel $LN5
	DD	imagerel $LN5+167
	DD	imagerel $unwind$?initialize_rtc@@YAXXZ
$pdata$?get_rtc_register@@YAEH@Z DD imagerel $LN3
	DD	imagerel $LN3+36
	DD	imagerel $unwind$?get_rtc_register@@YAEH@Z
$pdata$?set_rtc_register@@YAXGE@Z DD imagerel $LN3
	DD	imagerel $LN3+46
	DD	imagerel $unwind$?set_rtc_register@@YAXGE@Z
$pdata$?is_updating_rtc@@YAHXZ DD imagerel $LN3
	DD	imagerel $LN3+45
	DD	imagerel $unwind$?is_updating_rtc@@YAHXZ
$pdata$?rtc_read_datetime@@YAXXZ DD imagerel $LN6
	DD	imagerel $LN6+455
	DD	imagerel $unwind$?rtc_read_datetime@@YAXXZ
$pdata$?rtc_clock_update@@YAX_KPEAX@Z DD imagerel $LN6
	DD	imagerel $LN6+84
	DD	imagerel $unwind$?rtc_clock_update@@YAX_KPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?initialize_rtc@@YAXXZ DD 010401H
	DD	06204H
$unwind$?get_rtc_register@@YAEH@Z DD 010801H
	DD	04208H
$unwind$?set_rtc_register@@YAXGE@Z DD 010d01H
	DD	0420dH
$unwind$?is_updating_rtc@@YAHXZ DD 010401H
	DD	06204H
$unwind$?rtc_read_datetime@@YAXXZ DD 010401H
	DD	08204H
$unwind$?rtc_clock_update@@YAX_KPEAX@Z DD 010e01H
	DD	0620eH
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\rtc.cpp
_TEXT	SEGMENT
tv69 = 32
ready$ = 33
s$ = 64
p$ = 72
?rtc_clock_update@@YAX_KPEAX@Z PROC			; rtc_clock_update

; 79   : void rtc_clock_update(size_t s, void* p) {

$LN6:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 80   : 	bool ready = get_rtc_register(0x0C) & 0x10;

	mov	ecx, 12
	call	?get_rtc_register@@YAEH@Z		; get_rtc_register
	movzx	eax, al
	and	eax, 16
	test	eax, eax
	je	SHORT $LN4@rtc_clock_
	mov	BYTE PTR tv69[rsp], 1
	jmp	SHORT $LN5@rtc_clock_
$LN4@rtc_clock_:
	mov	BYTE PTR tv69[rsp], 0
$LN5@rtc_clock_:
	movzx	eax, BYTE PTR tv69[rsp]
	mov	BYTE PTR ready$[rsp], al

; 81   : 	if (ready) {

	movzx	eax, BYTE PTR ready$[rsp]
	test	eax, eax
	je	SHORT $LN1@rtc_clock_

; 82   : 		rtc_read_datetime();

	call	?rtc_read_datetime@@YAXXZ		; rtc_read_datetime
$LN1@rtc_clock_:

; 83   : 	}
; 84   : 	//!send a EOI to apic
; 85   : 	interrupt_end(8);

	mov	ecx, 8
	call	?interrupt_end@@YAXI@Z			; interrupt_end

; 86   : }

	add	rsp, 56					; 00000038H
	ret	0
?rtc_clock_update@@YAX_KPEAX@Z ENDP			; rtc_clock_update
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\rtc.cpp
_TEXT	SEGMENT
registerB$ = 32
tv84 = 36
tv91 = 40
tv130 = 44
tv141 = 48
tv148 = 52
tv155 = 56
?rtc_read_datetime@@YAXXZ PROC				; rtc_read_datetime

; 53   : void rtc_read_datetime() {

$LN6:
	sub	rsp, 72					; 00000048H
$LN3@rtc_read_d:

; 54   :     // Wait until rtc is not updating
; 55   :     while(is_updating_rtc());

	call	?is_updating_rtc@@YAHXZ			; is_updating_rtc
	test	eax, eax
	je	SHORT $LN2@rtc_read_d
	jmp	SHORT $LN3@rtc_read_d
$LN2@rtc_read_d:

; 56   : 
; 57   :     second = get_rtc_register(0x00);

	xor	ecx, ecx
	call	?get_rtc_register@@YAEH@Z		; get_rtc_register
	mov	BYTE PTR ?second@@3EA, al		; second

; 58   :     minute = get_rtc_register(0x02);

	mov	ecx, 2
	call	?get_rtc_register@@YAEH@Z		; get_rtc_register
	mov	BYTE PTR ?minute@@3EA, al		; minute

; 59   :     hour = get_rtc_register(0x04);

	mov	ecx, 4
	call	?get_rtc_register@@YAEH@Z		; get_rtc_register
	mov	BYTE PTR ?hour@@3EA, al			; hour

; 60   :     day = get_rtc_register(0x07);

	mov	ecx, 7
	call	?get_rtc_register@@YAEH@Z		; get_rtc_register
	mov	BYTE PTR ?day@@3EA, al			; day

; 61   :     month = get_rtc_register(0x08);

	mov	ecx, 8
	call	?get_rtc_register@@YAEH@Z		; get_rtc_register
	mov	BYTE PTR ?month@@3EA, al		; month

; 62   :     year = get_rtc_register(0x09);

	mov	ecx, 9
	call	?get_rtc_register@@YAEH@Z		; get_rtc_register
	mov	BYTE PTR ?year@@3EA, al			; year

; 63   : 
; 64   :     uint8_t registerB = get_rtc_register(0x0B);

	mov	ecx, 11
	call	?get_rtc_register@@YAEH@Z		; get_rtc_register
	mov	BYTE PTR registerB$[rsp], al

; 65   : 
; 66   :     // Convert BCD to binary values if necessary
; 67   :     if (!(registerB & 0x04)) {

	movzx	eax, BYTE PTR registerB$[rsp]
	and	eax, 4
	test	eax, eax
	jne	$LN1@rtc_read_d

; 68   :         second = (second & 0x0F) + ((second / 16) * 10);

	movzx	eax, BYTE PTR ?second@@3EA		; second
	and	eax, 15
	mov	DWORD PTR tv84[rsp], eax
	movzx	ecx, BYTE PTR ?second@@3EA		; second
	mov	eax, ecx
	cdq
	and	edx, 15
	add	eax, edx
	sar	eax, 4
	imul	eax, 10
	mov	ecx, DWORD PTR tv84[rsp]
	add	ecx, eax
	mov	eax, ecx
	mov	BYTE PTR ?second@@3EA, al		; second

; 69   :         minute = (minute & 0x0F) + ((minute / 16) * 10);

	movzx	eax, BYTE PTR ?minute@@3EA		; minute
	and	eax, 15
	mov	DWORD PTR tv91[rsp], eax
	movzx	ecx, BYTE PTR ?minute@@3EA		; minute
	mov	eax, ecx
	cdq
	and	edx, 15
	add	eax, edx
	sar	eax, 4
	imul	eax, 10
	mov	ecx, DWORD PTR tv91[rsp]
	add	ecx, eax
	mov	eax, ecx
	mov	BYTE PTR ?minute@@3EA, al		; minute

; 70   :         hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);

	movzx	eax, BYTE PTR ?hour@@3EA		; hour
	and	eax, 15
	mov	DWORD PTR tv130[rsp], eax
	movzx	ecx, BYTE PTR ?hour@@3EA		; hour
	and	ecx, 112				; 00000070H
	mov	eax, ecx
	cdq
	and	edx, 15
	add	eax, edx
	sar	eax, 4
	imul	eax, 10
	mov	ecx, DWORD PTR tv130[rsp]
	add	ecx, eax
	mov	eax, ecx
	movzx	ecx, BYTE PTR ?hour@@3EA		; hour
	and	ecx, 128				; 00000080H
	or	eax, ecx
	mov	BYTE PTR ?hour@@3EA, al			; hour

; 71   :         day = (day & 0x0F) + ((day / 16) * 10);

	movzx	eax, BYTE PTR ?day@@3EA			; day
	and	eax, 15
	mov	DWORD PTR tv141[rsp], eax
	movzx	ecx, BYTE PTR ?day@@3EA			; day
	mov	eax, ecx
	cdq
	and	edx, 15
	add	eax, edx
	sar	eax, 4
	imul	eax, 10
	mov	ecx, DWORD PTR tv141[rsp]
	add	ecx, eax
	mov	eax, ecx
	mov	BYTE PTR ?day@@3EA, al			; day

; 72   :         month = (month & 0x0F) + ((month / 16) * 10);

	movzx	eax, BYTE PTR ?month@@3EA		; month
	and	eax, 15
	mov	DWORD PTR tv148[rsp], eax
	movzx	ecx, BYTE PTR ?month@@3EA		; month
	mov	eax, ecx
	cdq
	and	edx, 15
	add	eax, edx
	sar	eax, 4
	imul	eax, 10
	mov	ecx, DWORD PTR tv148[rsp]
	add	ecx, eax
	mov	eax, ecx
	mov	BYTE PTR ?month@@3EA, al		; month

; 73   :         year = (year & 0x0F) + ((year / 16) * 10);

	movzx	eax, BYTE PTR ?year@@3EA		; year
	and	eax, 15
	mov	DWORD PTR tv155[rsp], eax
	movzx	ecx, BYTE PTR ?year@@3EA		; year
	mov	eax, ecx
	cdq
	and	edx, 15
	add	eax, edx
	sar	eax, 4
	imul	eax, 10
	mov	ecx, DWORD PTR tv155[rsp]
	add	ecx, eax
	mov	eax, ecx
	mov	BYTE PTR ?year@@3EA, al			; year
$LN1@rtc_read_d:

; 74   :     }
; 75   : }

	add	rsp, 72					; 00000048H
	ret	0
?rtc_read_datetime@@YAXXZ ENDP				; rtc_read_datetime
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\rtc.cpp
_TEXT	SEGMENT
status$ = 32
?is_updating_rtc@@YAHXZ PROC				; is_updating_rtc

; 43   : int is_updating_rtc() {

$LN3:
	sub	rsp, 56					; 00000038H

; 44   : 	x64_outportb(CMOS_ADDR, 0x0A);

	mov	dl, 10
	mov	cx, 112					; 00000070H
	call	x64_outportb

; 45   :     uint32_t status = x64_inportb(CMOS_DATA);

	mov	cx, 113					; 00000071H
	call	x64_inportb
	movzx	eax, al
	mov	DWORD PTR status$[rsp], eax

; 46   :     return (status & 0x80);

	mov	eax, DWORD PTR status$[rsp]
	and	eax, 128				; 00000080H

; 47   : }

	add	rsp, 56					; 00000038H
	ret	0
?is_updating_rtc@@YAHXZ ENDP				; is_updating_rtc
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\rtc.cpp
_TEXT	SEGMENT
reg_num$ = 48
val$ = 56
?set_rtc_register@@YAXGE@Z PROC				; set_rtc_register

; 34   : void set_rtc_register(uint16_t reg_num, uint8_t val) {

$LN3:
	mov	BYTE PTR [rsp+16], dl
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 40					; 00000028H

; 35   :     x64_outportb(CMOS_ADDR, reg_num);

	movzx	edx, BYTE PTR reg_num$[rsp]
	mov	cx, 112					; 00000070H
	call	x64_outportb

; 36   :     x64_outportb(CMOS_DATA, val);

	movzx	edx, BYTE PTR val$[rsp]
	mov	cx, 113					; 00000071H
	call	x64_outportb

; 37   : }

	add	rsp, 40					; 00000028H
	ret	0
?set_rtc_register@@YAXGE@Z ENDP				; set_rtc_register
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\rtc.cpp
_TEXT	SEGMENT
reg_num$ = 48
?get_rtc_register@@YAEH@Z PROC				; get_rtc_register

; 26   : uint8_t get_rtc_register(int reg_num) {

$LN3:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 40					; 00000028H

; 27   :     x64_outportb(CMOS_ADDR, reg_num);

	movzx	edx, BYTE PTR reg_num$[rsp]
	mov	cx, 112					; 00000070H
	call	x64_outportb

; 28   :     return x64_inportb(CMOS_DATA);

	mov	cx, 113					; 00000071H
	call	x64_inportb

; 29   : }

	add	rsp, 40					; 00000028H
	ret	0
?get_rtc_register@@YAEH@Z ENDP				; get_rtc_register
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\rtc.cpp
_TEXT	SEGMENT
?rtc_get_year@@YAEXZ PROC				; rtc_get_year

; 114  : 	return year;

	movzx	eax, BYTE PTR ?year@@3EA		; year

; 115  : }

	ret	0
?rtc_get_year@@YAEXZ ENDP				; rtc_get_year
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\rtc.cpp
_TEXT	SEGMENT
status$ = 32
tv81 = 36
?initialize_rtc@@YAXXZ PROC				; initialize_rtc

; 88   : void initialize_rtc () {

$LN5:
	sub	rsp, 56					; 00000038H

; 89   : 
; 90   : 	unsigned char status = get_rtc_register (0x0B);

	mov	ecx, 11
	call	?get_rtc_register@@YAEH@Z		; get_rtc_register
	mov	BYTE PTR status$[rsp], al

; 91   : 	status |= 0x02;

	movzx	eax, BYTE PTR status$[rsp]
	or	eax, 2
	mov	BYTE PTR status$[rsp], al

; 92   : 	status |= 0x10;

	movzx	eax, BYTE PTR status$[rsp]
	or	eax, 16
	mov	BYTE PTR status$[rsp], al

; 93   : 	status &= ~0x20;

	movzx	eax, BYTE PTR status$[rsp]
	and	eax, -33				; ffffffffffffffdfH
	mov	BYTE PTR status$[rsp], al

; 94   : 	status &= ~0x40;

	movzx	eax, BYTE PTR status$[rsp]
	and	eax, -65				; ffffffffffffffbfH
	mov	BYTE PTR status$[rsp], al

; 95   : 	bcd = !(status & 0x04);

	movzx	eax, BYTE PTR status$[rsp]
	and	eax, 4
	test	eax, eax
	jne	SHORT $LN3@initialize
	mov	DWORD PTR tv81[rsp], 1
	jmp	SHORT $LN4@initialize
$LN3@initialize:
	mov	DWORD PTR tv81[rsp], 0
$LN4@initialize:
	movzx	eax, BYTE PTR tv81[rsp]
	mov	BYTE PTR bcd, al

; 96   : 
; 97   : 	//! Write status to rtc
; 98   : 	x64_outportb (0x70, 0x0B);

	mov	dl, 11
	mov	cx, 112					; 00000070H
	call	x64_outportb

; 99   : 	x64_outportb (0x71, status);

	movzx	edx, BYTE PTR status$[rsp]
	mov	cx, 113					; 00000071H
	call	x64_outportb

; 100  : 
; 101  : 	//! Read status from RTC
; 102  : 	get_rtc_register (0x0C);

	mov	ecx, 12
	call	?get_rtc_register@@YAEH@Z		; get_rtc_register

; 103  : 
; 104  : 	//!register interrupt
; 105  : 	interrupt_set (8,rtc_clock_update, 8);

	mov	r8b, 8
	lea	rdx, OFFSET FLAT:?rtc_clock_update@@YAX_KPEAX@Z ; rtc_clock_update
	mov	ecx, 8
	call	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z	; interrupt_set

; 106  : 
; 107  : #ifdef USE_PIC
; 108  : 	irq_mask(8,false);
; 109  : #endif
; 110  : }

	add	rsp, 56					; 00000038H
	ret	0
?initialize_rtc@@YAXXZ ENDP				; initialize_rtc
_TEXT	ENDS
END
