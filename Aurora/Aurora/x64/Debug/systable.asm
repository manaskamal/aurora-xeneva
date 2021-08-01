; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	funct
EXTRN	?message_send@@YAXGPEAU_message_@@@Z:PROC	; message_send
EXTRN	?message_receive@@YAXPEAU_message_@@@Z:PROC	; message_receive
EXTRN	?wait@@YAXXZ:PROC				; wait
EXTRN	?create__sys_process@@YAXPEBD@Z:PROC		; create__sys_process
EXTRN	?valloc@@YAX_K@Z:PROC				; valloc
EXTRN	?map_shared_memory@@YAXG_K0@Z:PROC		; map_shared_memory
EXTRN	?get_thread_id@@YAGXZ:PROC			; get_thread_id
EXTRN	?sys_get_fb_mem@@YAPEAIXZ:PROC			; sys_get_fb_mem
EXTRN	?sys_fb_update@@YAXXZ:PROC			; sys_fb_update
EXTRN	?sys_set_mouse_data@@YAXXZ:PROC			; sys_set_mouse_data
EXTRN	?sys_get_mouse_pack@@YA_NPEAU_mouse_packet_@@@Z:PROC ; sys_get_mouse_pack
EXTRN	?sys_move_cursor@@YAXIII@Z:PROC			; sys_move_cursor
EXTRN	?sys_unblock_id@@YAXG@Z:PROC			; sys_unblock_id
EXTRN	?create_uthread@@YAXP6AXPEAX@Z@Z:PROC		; create_uthread
EXTRN	?sys_open_file@@YAXPEAU_file_@@PEBD@Z:PROC	; sys_open_file
EXTRN	?sys_read_file@@YAXPEAU_file_@@PEAEH@Z:PROC	; sys_read_file
EXTRN	?sys_get_used_ram@@YA_KXZ:PROC			; sys_get_used_ram
EXTRN	?sys_get_free_ram@@YA_KXZ:PROC			; sys_get_free_ram
EXTRN	?sys_sleep@@YAX_K@Z:PROC			; sys_sleep
EXTRN	?sys_exit@@YAXXZ:PROC				; sys_exit
EXTRN	?sys_fb_move_cursor@@YAXII@Z:PROC		; sys_fb_move_cursor
EXTRN	?dwm_put_message@@YAXPEAU_dwm_message_@@@Z:PROC	; dwm_put_message
EXTRN	?dwm_dispatch_message@@YAXPEAU_dwm_message_@@@Z:PROC ; dwm_dispatch_message
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?get_screen_width@@YAIXZ:PROC			; get_screen_width
EXTRN	?get_screen_height@@YAIXZ:PROC			; get_screen_height
EXTRN	?get_screen_scanline@@YAGXZ:PROC		; get_screen_scanline
_BSS	SEGMENT
funct	DQ	01H DUP (?)
_BSS	ENDS
CONST	SEGMENT
$SG5815	DB	'System Call Fault!! Halting System', 0aH, 00H
CONST	ENDS
_DATA	SEGMENT
_syscalls DQ	FLAT:?printf@@YAXPEBDZZ
	DQ	FLAT:?wait@@YAXXZ
	DQ	FLAT:?create__sys_process@@YAXPEBD@Z
	DQ	FLAT:?get_screen_width@@YAIXZ
	DQ	FLAT:?get_screen_height@@YAIXZ
	DQ	FLAT:?valloc@@YAX_K@Z
	DQ	FLAT:?message_send@@YAXGPEAU_message_@@@Z
	DQ	FLAT:?message_receive@@YAXPEAU_message_@@@Z
	DQ	FLAT:?map_shared_memory@@YAXG_K0@Z
	DQ	FLAT:?get_thread_id@@YAGXZ
	DQ	FLAT:?dwm_put_message@@YAXPEAU_dwm_message_@@@Z
	DQ	FLAT:?dwm_dispatch_message@@YAXPEAU_dwm_message_@@@Z
	DQ	FLAT:?sys_get_fb_mem@@YAPEAIXZ
	DQ	FLAT:?sys_fb_update@@YAXXZ
	DQ	FLAT:?sys_set_mouse_data@@YAXXZ
	DQ	FLAT:?sys_get_mouse_pack@@YA_NPEAU_mouse_packet_@@@Z
	DQ	FLAT:?sys_move_cursor@@YAXIII@Z
	DQ	FLAT:?sys_unblock_id@@YAXG@Z
	DQ	FLAT:?create_uthread@@YAXP6AXPEAX@Z@Z
	DQ	FLAT:?sys_open_file@@YAXPEAU_file_@@PEBD@Z
	DQ	FLAT:?sys_read_file@@YAXPEAU_file_@@PEAEH@Z
	DQ	FLAT:?get_screen_scanline@@YAGXZ
	DQ	FLAT:?sys_get_used_ram@@YA_KXZ
	DQ	FLAT:?sys_get_free_ram@@YA_KXZ
	DQ	FLAT:?sys_sleep@@YAX_K@Z
	DQ	FLAT:?sys_exit@@YAXXZ
	DQ	FLAT:?sys_fb_move_cursor@@YAXII@Z
	DQ	0000000000000000H
_DATA	ENDS
PUBLIC	x64_syscall_handler
pdata	SEGMENT
$pdata$x64_syscall_handler DD imagerel $LN6
	DD	imagerel $LN6+69
	DD	imagerel $unwind$x64_syscall_handler
pdata	ENDS
xdata	SEGMENT
$unwind$x64_syscall_handler DD 010901H
	DD	06209H
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\systable.cpp
_TEXT	SEGMENT
idx$ = 32
a$ = 64
x64_syscall_handler PROC

; 14   : extern "C" void x64_syscall_handler (void* a) {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 15   : 
; 16   : 	//! get the index number
; 17   : 	int idx = (int)a;

	mov	eax, DWORD PTR a$[rsp]
	mov	DWORD PTR idx$[rsp], eax

; 18   : 
; 19   : 	//! check for index limit
; 20   : 	if (idx > 256) {

	cmp	DWORD PTR idx$[rsp], 256		; 00000100H
	jle	SHORT $LN3@x64_syscal

; 21   : 		printf ("System Call Fault!! Halting System\n");

	lea	rcx, OFFSET FLAT:$SG5815
	call	?printf@@YAXPEBDZZ			; printf
$LN2@x64_syscal:

; 22   : 		for(;;);  //Loop forever for now

	jmp	SHORT $LN2@x64_syscal
$LN3@x64_syscal:

; 23   : 	}
; 24   : 	
; 25   : 	//! update the function pointer to syscall table index
; 26   : 	funct = (uint64_t*)_syscalls[idx];

	movsxd	rax, DWORD PTR idx$[rsp]
	lea	rcx, OFFSET FLAT:_syscalls
	mov	rax, QWORD PTR [rcx+rax*8]
	mov	QWORD PTR funct, rax

; 27   : 
; 28   : 	//return to the caller
; 29   : }

	add	rsp, 56					; 00000038H
	ret	0
x64_syscall_handler ENDP
_TEXT	ENDS
END
