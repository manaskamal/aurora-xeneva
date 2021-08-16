; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?hal_init@@YAXXZ				; hal_init
PUBLIC	?hal_set_vect@@YAX_KP6AX0PEAX@Z@Z		; hal_set_vect
PUBLIC	?inportb@@YAEG@Z				; inportb
PUBLIC	?inportw@@YAGG@Z				; inportw
PUBLIC	?inportd@@YAIG@Z				; inportd
PUBLIC	?outportb@@YAXGE@Z				; outportb
PUBLIC	?outportw@@YAXGG@Z				; outportw
PUBLIC	?outportd@@YAXGI@Z				; outportd
PUBLIC	?interrupt_end@@YAXI@Z				; interrupt_end
PUBLIC	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z		; interrupt_set
PUBLIC	?irq_mask@@YAXE_N@Z				; irq_mask
EXTRN	?apic_local_eoi@@YAXXZ:PROC			; apic_local_eoi
EXTRN	x64_inportb:PROC
EXTRN	x64_inportw:PROC
EXTRN	x64_inportd:PROC
EXTRN	x64_outportb:PROC
EXTRN	x64_outportw:PROC
EXTRN	x64_outportd:PROC
EXTRN	?hal_x86_64_init@@YAXXZ:PROC			; hal_x86_64_init
EXTRN	?setvect@@YAX_KP6AX0PEAX@Z@Z:PROC		; setvect
EXTRN	?ioapic_register_irq@@YAX_KP6AX0PEAX@ZE@Z:PROC	; ioapic_register_irq
EXTRN	?ioapic_mask_irq@@YAXE_N@Z:PROC			; ioapic_mask_irq
pdata	SEGMENT
$pdata$?hal_init@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+14
	DD	imagerel $unwind$?hal_init@@YAXXZ
$pdata$?hal_set_vect@@YAX_KP6AX0PEAX@Z@Z DD imagerel $LN3
	DD	imagerel $LN3+34
	DD	imagerel $unwind$?hal_set_vect@@YAX_KP6AX0PEAX@Z@Z
$pdata$?inportb@@YAEG@Z DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$?inportb@@YAEG@Z
$pdata$?inportw@@YAGG@Z DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$?inportw@@YAGG@Z
$pdata$?inportd@@YAIG@Z DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$?inportd@@YAIG@Z
$pdata$?outportb@@YAXGE@Z DD imagerel $LN3
	DD	imagerel $LN3+33
	DD	imagerel $unwind$?outportb@@YAXGE@Z
$pdata$?outportw@@YAXGG@Z DD imagerel $LN3
	DD	imagerel $LN3+34
	DD	imagerel $unwind$?outportw@@YAXGG@Z
$pdata$?outportd@@YAXGI@Z DD imagerel $LN3
	DD	imagerel $LN3+32
	DD	imagerel $unwind$?outportd@@YAXGI@Z
$pdata$?interrupt_end@@YAXI@Z DD imagerel $LN3
	DD	imagerel $LN3+18
	DD	imagerel $unwind$?interrupt_end@@YAXI@Z
$pdata$?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z DD imagerel $LN3
	DD	imagerel $LN3+45
	DD	imagerel $unwind$?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z
$pdata$?irq_mask@@YAXE_N@Z DD imagerel $LN3
	DD	imagerel $LN3+32
	DD	imagerel $unwind$?irq_mask@@YAXE_N@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?hal_init@@YAXXZ DD 010401H
	DD	04204H
$unwind$?hal_set_vect@@YAX_KP6AX0PEAX@Z@Z DD 010e01H
	DD	0420eH
$unwind$?inportb@@YAEG@Z DD 010901H
	DD	04209H
$unwind$?inportw@@YAGG@Z DD 010901H
	DD	04209H
$unwind$?inportd@@YAIG@Z DD 010901H
	DD	04209H
$unwind$?outportb@@YAXGE@Z DD 010d01H
	DD	0420dH
$unwind$?outportw@@YAXGG@Z DD 010e01H
	DD	0420eH
$unwind$?outportd@@YAXGI@Z DD 010d01H
	DD	0420dH
$unwind$?interrupt_end@@YAXI@Z DD 010801H
	DD	04208H
$unwind$?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z DD 011301H
	DD	04213H
$unwind$?irq_mask@@YAXE_N@Z DD 010c01H
	DD	0420cH
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\hal.cpp
_TEXT	SEGMENT
irq$ = 48
value$ = 56
?irq_mask@@YAXE_N@Z PROC				; irq_mask

; 153  : void irq_mask (uint8_t irq, bool value) {

$LN3:
	mov	BYTE PTR [rsp+16], dl
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 40					; 00000028H

; 154  : 	ioapic_mask_irq(irq, value);

	movzx	edx, BYTE PTR value$[rsp]
	movzx	ecx, BYTE PTR irq$[rsp]
	call	?ioapic_mask_irq@@YAXE_N@Z		; ioapic_mask_irq

; 155  : }

	add	rsp, 40					; 00000028H
	ret	0
?irq_mask@@YAXE_N@Z ENDP				; irq_mask
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\hal.cpp
_TEXT	SEGMENT
vector$ = 48
fn$ = 56
irq$ = 64
?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z PROC		; interrupt_set

; 137  : void interrupt_set (size_t vector, void (*fn)(size_t, void* p),uint8_t irq){

$LN3:
	mov	BYTE PTR [rsp+24], r8b
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 138  : #ifdef ARCH_X64
; 139  : #ifdef USE_PIC
; 140  : 	setvect(32 + vector, fn);
; 141  : #endif
; 142  : #ifdef USE_APIC
; 143  : 	ioapic_register_irq(vector,fn,irq);

	movzx	r8d, BYTE PTR irq$[rsp]
	mov	rdx, QWORD PTR fn$[rsp]
	mov	rcx, QWORD PTR vector$[rsp]
	call	?ioapic_register_irq@@YAX_KP6AX0PEAX@ZE@Z ; ioapic_register_irq

; 144  : #endif
; 145  : #elif  ARCH_ARM
; 146  : 	//! update comming soon..
; 147  : #elif ARCH_ARM64
; 148  : 	//! update comming soon...
; 149  : #endif
; 150  : }

	add	rsp, 40					; 00000028H
	ret	0
?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z ENDP		; interrupt_set
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\hal.cpp
_TEXT	SEGMENT
irq$ = 48
?interrupt_end@@YAXI@Z PROC				; interrupt_end

; 122  : void interrupt_end (uint32_t irq) { 

$LN3:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 40					; 00000028H

; 123  : #ifdef ARCH_X64
; 124  : #ifdef USE_PIC
; 125  : 	pic_interrupt_eoi(irq);
; 126  : #endif
; 127  : #ifdef USE_APIC
; 128  : 	apic_local_eoi ();

	call	?apic_local_eoi@@YAXXZ			; apic_local_eoi

; 129  : #endif
; 130  : #elif ARCH_ARM
; 131  : 	//! update comming soon..
; 132  : #elif ARCH_ARM64
; 133  : 	//! update comming soon..
; 134  : #endif
; 135  : }

	add	rsp, 40					; 00000028H
	ret	0
?interrupt_end@@YAXI@Z ENDP				; interrupt_end
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\hal.cpp
_TEXT	SEGMENT
port$ = 48
data$ = 56
?outportd@@YAXGI@Z PROC					; outportd

; 111  : void  outportd (uint16_t port, uint32_t data) {

$LN3:
	mov	DWORD PTR [rsp+16], edx
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 40					; 00000028H

; 112  : #ifdef ARCH_X64
; 113  : 	x64_outportd (port, data);

	mov	edx, DWORD PTR data$[rsp]
	movzx	ecx, WORD PTR port$[rsp]
	call	x64_outportd

; 114  : #elif ARCH_ARM
; 115  : 	//! arm32_outportd (port, data);
; 116  : #elif ARCH_ARM64
; 117  : 	//! arm64_outportw (port, data);
; 118  : #endif
; 119  : }

	add	rsp, 40					; 00000028H
	ret	0
?outportd@@YAXGI@Z ENDP					; outportd
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\hal.cpp
_TEXT	SEGMENT
port$ = 48
data$ = 56
?outportw@@YAXGG@Z PROC					; outportw

; 99   : void outportw (uint16_t port, uint16_t data) {

$LN3:
	mov	WORD PTR [rsp+16], dx
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 40					; 00000028H

; 100  : #ifdef ARCH_X64
; 101  : 	x64_outportw (port, data);

	movzx	edx, WORD PTR data$[rsp]
	movzx	ecx, WORD PTR port$[rsp]
	call	x64_outportw

; 102  : #elif  ARCH_ARM
; 103  : 	//! arm32_outportw (port, data);
; 104  : #elif ARCH_ARM64
; 105  : 	//! arm64_outportw (port, data);
; 106  : #endif
; 107  : }

	add	rsp, 40					; 00000028H
	ret	0
?outportw@@YAXGG@Z ENDP					; outportw
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\hal.cpp
_TEXT	SEGMENT
port$ = 48
data$ = 56
?outportb@@YAXGE@Z PROC					; outportb

; 87   : void  outportb (uint16_t port, uint8_t data ) {

$LN3:
	mov	BYTE PTR [rsp+16], dl
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 40					; 00000028H

; 88   : #ifdef ARCH_X64
; 89   : 	x64_outportb (port,data);

	movzx	edx, BYTE PTR data$[rsp]
	movzx	ecx, WORD PTR port$[rsp]
	call	x64_outportb

; 90   : #elif ARCH_ARM
; 91   : 	//!arm32_outportb (port, data);
; 92   : #elif ARCH_ARM64
; 93   : 	//!arm64_outportb (port, data);
; 94   : #endif
; 95   : }

	add	rsp, 40					; 00000028H
	ret	0
?outportb@@YAXGE@Z ENDP					; outportb
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\hal.cpp
_TEXT	SEGMENT
port$ = 48
?inportd@@YAIG@Z PROC					; inportd

; 74   : uint32_t  inportd (uint16_t port) {

$LN3:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 40					; 00000028H

; 75   : #ifdef ARCH_X64
; 76   : 	return x64_inportd (port);

	movzx	ecx, WORD PTR port$[rsp]
	call	x64_inportd

; 77   : #elif ARCH_ARM
; 78   : 	//! return arm32_inportd (port);
; 79   : #elif ARCH_ARM64
; 80   : 	//! return arm64_inportd (port);
; 81   : #endif
; 82   : 
; 83   : }

	add	rsp, 40					; 00000028H
	ret	0
?inportd@@YAIG@Z ENDP					; inportd
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\hal.cpp
_TEXT	SEGMENT
port$ = 48
?inportw@@YAGG@Z PROC					; inportw

; 62   : uint16_t inportw (uint16_t port) {

$LN3:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 40					; 00000028H

; 63   : #ifdef ARCH_X64
; 64   : 	return x64_inportw (port);

	movzx	ecx, WORD PTR port$[rsp]
	call	x64_inportw

; 65   : #elif ARCH_ARM
; 66   : 	//return arm32_inportw (port);
; 67   : #elif ARCH_ARM64
; 68   : 	//return arm64_inportw (port);
; 69   : #endif
; 70   : 
; 71   : }

	add	rsp, 40					; 00000028H
	ret	0
?inportw@@YAGG@Z ENDP					; inportw
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\hal.cpp
_TEXT	SEGMENT
port$ = 48
?inportb@@YAEG@Z PROC					; inportb

; 51   : uint8_t inportb (uint16_t port) {

$LN3:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 40					; 00000028H

; 52   : #ifdef ARCH_X64
; 53   : 	return x64_inportb (port);

	movzx	ecx, WORD PTR port$[rsp]
	call	x64_inportb

; 54   : #elif ARCH_ARM
; 55   : 	//return arm32_inportb (port);
; 56   : #elif ARCH_ARM64
; 57   : 	//return arm64_inportb (port);
; 58   : #endif
; 59   : }

	add	rsp, 40					; 00000028H
	ret	0
?inportb@@YAEG@Z ENDP					; inportb
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\hal.cpp
_TEXT	SEGMENT
vector$ = 48
function$ = 56
?hal_set_vect@@YAX_KP6AX0PEAX@Z@Z PROC			; hal_set_vect

; 17   : void hal_set_vect (size_t vector, void (*function)(size_t vector, void* param)) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 18   : #ifdef ARCH_X64
; 19   : 	//! initialize x86_64 hal initializer
; 20   : 	setvect (vector,function);

	mov	rdx, QWORD PTR function$[rsp]
	mov	rcx, QWORD PTR vector$[rsp]
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 21   : #elif  ARCH_ARM
; 22   : 	//! initialize arm32 hal initializer
; 23   : 	arm_set_vect(vector,function);
; 24   : #elif  ARCH_ARM64
; 25   : 	//! initialize arm64 hal initializer
; 26   : 	arm64_set_vect(vector,function);
; 27   : #endif
; 28   : }

	add	rsp, 40					; 00000028H
	ret	0
?hal_set_vect@@YAX_KP6AX0PEAX@Z@Z ENDP			; hal_set_vect
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\hal.cpp
_TEXT	SEGMENT
?hal_init@@YAXXZ PROC					; hal_init

; 32   : void hal_init () {

$LN3:
	sub	rsp, 40					; 00000028H

; 33   : 
; 34   : 	//! Check processor type
; 35   : #ifdef ARCH_X64
; 36   : 	//! initialize x86_64 hal initializer
; 37   : 	hal_x86_64_init ();

	call	?hal_x86_64_init@@YAXXZ			; hal_x86_64_init

; 38   : #elif  ARCH_ARM
; 39   : 	//! initialize arm32 hal initializer
; 40   : 	hal_arm_init ();
; 41   : #elif  ARCH_ARM64
; 42   : 	//! initialize arm64 hal initializer
; 43   : 	hal_arm64_init ();
; 44   : #endif
; 45   : 
; 46   : }

	add	rsp, 40					; 00000028H
	ret	0
?hal_init@@YAXXZ ENDP					; hal_init
_TEXT	ENDS
END
