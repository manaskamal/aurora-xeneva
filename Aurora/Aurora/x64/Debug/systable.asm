; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	funct
EXTRN	?message_send@@YAXGPEAU_message_@@@Z:PROC	; message_send
EXTRN	?message_receive@@YAXPEAU_message_@@@Z:PROC	; message_receive
EXTRN	?wait@@YAXXZ:PROC				; wait
EXTRN	?create__sys_process@@YAHPEBDPEAD@Z:PROC	; create__sys_process
EXTRN	?valloc@@YAX_K@Z:PROC				; valloc
EXTRN	?vfree@@YAX_K@Z:PROC				; vfree
EXTRN	?map_shared_memory@@YAXG_K0@Z:PROC		; map_shared_memory
EXTRN	?get_thread_id@@YAGXZ:PROC			; get_thread_id
EXTRN	?sys_unblock_id@@YAXG@Z:PROC			; sys_unblock_id
EXTRN	?create_uthread@@YAXP6AXPEAX@ZPEAD@Z:PROC	; create_uthread
EXTRN	?sys_open_file@@YAHPEADPEAU_file_@@@Z:PROC	; sys_open_file
EXTRN	?sys_read_file@@YAXHPEAEPEAU_file_@@@Z:PROC	; sys_read_file
EXTRN	?sys_write_file@@YAXHPEAEPEAU_file_@@@Z:PROC	; sys_write_file
EXTRN	?sys_get_used_ram@@YA_KXZ:PROC			; sys_get_used_ram
EXTRN	?sys_get_free_ram@@YA_KXZ:PROC			; sys_get_free_ram
EXTRN	?sys_sleep@@YAX_K@Z:PROC			; sys_sleep
EXTRN	?sys_exit@@YAXXZ:PROC				; sys_exit
EXTRN	?fork@@YAIXZ:PROC				; fork
EXTRN	?exec@@YAXPEBDI@Z:PROC				; exec
EXTRN	?ioquery@@YAXHHPEAX@Z:PROC			; ioquery
EXTRN	?sys_get_current_time@@YAXPEAU_sys_time_@@@Z:PROC ; sys_get_current_time
EXTRN	?sys_get_system_tick@@YAIXZ:PROC		; sys_get_system_tick
EXTRN	?sys_kill@@YAXHH@Z:PROC				; sys_kill
EXTRN	?sys_set_signal@@YAXHP6AXH@Z@Z:PROC		; sys_set_signal
EXTRN	?unmap_shared_memory@@YAXG_K0@Z:PROC		; unmap_shared_memory
EXTRN	?sys_attach_ttype@@YAXH@Z:PROC			; sys_attach_ttype
EXTRN	?copy_memory@@YAXG_K0@Z:PROC			; copy_memory
EXTRN	?map_memory@@YAPEAX_KIE@Z:PROC			; map_memory
EXTRN	?unmap_memory@@YAXPEAXI@Z:PROC			; unmap_memory
EXTRN	?ttype_create@@YAXPEAH0@Z:PROC			; ttype_create
EXTRN	?ttype_dup_master@@YAXHH@Z:PROC			; ttype_dup_master
EXTRN	?allocate_pipe@@YAXPEAHPEAD@Z:PROC		; allocate_pipe
EXTRN	?create_timer@@YAHIG@Z:PROC			; create_timer
EXTRN	?destroy_timer@@YAXH@Z:PROC			; destroy_timer
EXTRN	?pause_timer@@YAXH@Z:PROC			; pause_timer
EXTRN	?start_timer@@YAXH@Z:PROC			; start_timer
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
_BSS	SEGMENT
funct	DQ	01H DUP (?)
_BSS	ENDS
CONST	SEGMENT
$SG3599	DB	'System Call Fault!! Halting System', 0aH, 00H
CONST	ENDS
_DATA	SEGMENT
_syscalls DQ	FLAT:?printf@@YAXPEBDZZ
	DQ	FLAT:?wait@@YAXXZ
	DQ	FLAT:?create__sys_process@@YAHPEBDPEAD@Z
	DQ	FLAT:?copy_memory@@YAXG_K0@Z
	DQ	0000000000000000H
	DQ	FLAT:?valloc@@YAX_K@Z
	DQ	FLAT:?message_send@@YAXGPEAU_message_@@@Z
	DQ	FLAT:?message_receive@@YAXPEAU_message_@@@Z
	DQ	FLAT:?map_shared_memory@@YAXG_K0@Z
	DQ	FLAT:?get_thread_id@@YAGXZ
	DQ	FLAT:?create_timer@@YAHIG@Z
	DQ	FLAT:?destroy_timer@@YAXH@Z
	DQ	0000000000000000H
	DQ	FLAT:?ttype_create@@YAXPEAH0@Z
	DQ	FLAT:?start_timer@@YAXH@Z
	DQ	FLAT:?pause_timer@@YAXH@Z
	DQ	FLAT:?allocate_pipe@@YAXPEAHPEAD@Z
	DQ	FLAT:?sys_unblock_id@@YAXG@Z
	DQ	FLAT:?create_uthread@@YAXP6AXPEAX@ZPEAD@Z
	DQ	FLAT:?sys_open_file@@YAHPEADPEAU_file_@@@Z
	DQ	FLAT:?sys_read_file@@YAXHPEAEPEAU_file_@@@Z
	DQ	FLAT:?ttype_dup_master@@YAXHH@Z
	DQ	FLAT:?sys_get_used_ram@@YA_KXZ
	DQ	FLAT:?sys_get_free_ram@@YA_KXZ
	DQ	FLAT:?sys_sleep@@YAX_K@Z
	DQ	FLAT:?sys_exit@@YAXXZ
	DQ	FLAT:?sys_attach_ttype@@YAXH@Z
	DQ	FLAT:?fork@@YAIXZ
	DQ	FLAT:?exec@@YAXPEBDI@Z
	DQ	FLAT:?map_memory@@YAPEAX_KIE@Z
	DQ	FLAT:?unmap_memory@@YAXPEAXI@Z
	DQ	FLAT:?ioquery@@YAXHHPEAX@Z
	DQ	FLAT:?sys_get_current_time@@YAXPEAU_sys_time_@@@Z
	DQ	FLAT:?sys_get_system_tick@@YAIXZ
	DQ	FLAT:?sys_kill@@YAXHH@Z
	DQ	FLAT:?sys_set_signal@@YAXHP6AXH@Z@Z
	DQ	FLAT:?unmap_shared_memory@@YAXG_K0@Z
	DQ	FLAT:?sys_write_file@@YAXHPEAEPEAU_file_@@@Z
	DQ	FLAT:?vfree@@YAX_K@Z
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
; Function compile flags: /Odtpy
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

	lea	rcx, OFFSET FLAT:$SG3599
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
