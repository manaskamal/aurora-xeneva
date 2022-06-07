; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	funct
_BSS	SEGMENT
funct	DQ	01H DUP (?)
_BSS	ENDS
CONST	SEGMENT
$SG4214	DB	'System Call Fault!! Halting System', 0aH, 00H
CONST	ENDS
PUBLIC	x64_syscall_handler
EXTRN	printf:PROC
EXTRN	?message_send@@YAXGPEAU_message_@@@Z:PROC	; message_send
EXTRN	?message_receive@@YAXPEAU_message_@@@Z:PROC	; message_receive
EXTRN	?wait@@YAXXZ:PROC				; wait
EXTRN	?create__sys_process@@YAHPEBDPEAD@Z:PROC	; create__sys_process
EXTRN	?valloc@@YAX_K@Z:PROC				; valloc
EXTRN	?vfree@@YAX_K@Z:PROC				; vfree
EXTRN	?get_thread_id@@YAGXZ:PROC			; get_thread_id
EXTRN	?sys_unblock_id@@YAXG@Z:PROC			; sys_unblock_id
EXTRN	?create_uthread@@YAXP6AXPEAX@ZPEAD@Z:PROC	; create_uthread
EXTRN	?sys_open_file@@YAHPEADPEAU_file_@@@Z:PROC	; sys_open_file
EXTRN	?sys_read_file@@YAXHPEAEPEAU_file_@@@Z:PROC	; sys_read_file
EXTRN	?sys_close_file@@YAXH@Z:PROC			; sys_close_file
EXTRN	?sys_write_file@@YAXHPEA_KPEAU_file_@@@Z:PROC	; sys_write_file
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
EXTRN	?sys_attach_ttype@@YAXH@Z:PROC			; sys_attach_ttype
EXTRN	?copy_memory@@YAXG_K0@Z:PROC			; copy_memory
EXTRN	?unmap_memory@@YAXPEAXI@Z:PROC			; unmap_memory
EXTRN	?ttype_create@@YAHPEAH0@Z:PROC			; ttype_create
EXTRN	?ttype_dup_master@@YAXHH@Z:PROC			; ttype_dup_master
EXTRN	?allocate_pipe@@YAXPEAHPEAD@Z:PROC		; allocate_pipe
EXTRN	?create_timer@@YAHIG@Z:PROC			; create_timer
EXTRN	?destroy_timer@@YAXH@Z:PROC			; destroy_timer
EXTRN	?pause_timer@@YAXH@Z:PROC			; pause_timer
EXTRN	?start_timer@@YAXH@Z:PROC			; start_timer
EXTRN	_debug_print_:PROC
EXTRN	?AuCreateShMem@@YAII_KI@Z:PROC			; AuCreateShMem
EXTRN	?AuObtainShMem@@YAPEAXIPEAXH@Z:PROC		; AuObtainShMem
EXTRN	?shm_unlink@@YAXI@Z:PROC			; shm_unlink
EXTRN	?au_mmap@@YAPEAXPEAX_KHHH1@Z:PROC		; au_mmap
EXTRN	?process_heap_break@@YAPEAX_K@Z:PROC		; process_heap_break
EXTRN	?process_link_libraries@@YAXXZ:PROC		; process_link_libraries
EXTRN	__ImageBase:BYTE
pdata	SEGMENT
$pdata$x64_syscall_handler DD imagerel $LN50
	DD	imagerel $LN50+1004
	DD	imagerel $unwind$x64_syscall_handler
pdata	ENDS
xdata	SEGMENT
$unwind$x64_syscall_handler DD 010801H
	DD	06208H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\systable.cpp
_TEXT	SEGMENT
idx$ = 32
tv66 = 36
a$ = 64
x64_syscall_handler PROC

; 17   : extern "C" void x64_syscall_handler (int a) {

$LN50:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 18   : 
; 19   : 	//! get the index number
; 20   : 	int idx = a;

	mov	eax, DWORD PTR a$[rsp]
	mov	DWORD PTR idx$[rsp], eax

; 21   : 
; 22   : 	//! check for index limit
; 23   : 	if (idx > 256) {

	cmp	DWORD PTR idx$[rsp], 256		; 00000100H
	jle	SHORT $LN46@x64_syscal

; 24   : 		printf ("System Call Fault!! Halting System\n");

	lea	rcx, OFFSET FLAT:$SG4214
	call	printf
$LN45@x64_syscal:

; 25   : 		for(;;);  //Loop forever for now

	jmp	SHORT $LN45@x64_syscal
$LN46@x64_syscal:

; 26   : 	}
; 27   : 
; 28   : 	switch (idx) {

	mov	eax, DWORD PTR idx$[rsp]
	mov	DWORD PTR tv66[rsp], eax
	cmp	DWORD PTR tv66[rsp], 40			; 00000028H
	ja	$LN42@x64_syscal
	movsxd	rax, DWORD PTR tv66[rsp]
	lea	rcx, OFFSET FLAT:__ImageBase
	mov	eax, DWORD PTR $LN49@x64_syscal[rcx+rax*4]
	add	rax, rcx
	jmp	rax
$LN41@x64_syscal:

; 29   : 	case 0:
; 30   : 		funct = (uint64_t*)_debug_print_; //

	lea	rax, OFFSET FLAT:_debug_print_
	mov	QWORD PTR funct, rax

; 31   : 		break;

	jmp	$LN42@x64_syscal
$LN40@x64_syscal:

; 32   : 	case 1:
; 33   : 		funct = (uint64_t*)wait;

	lea	rax, OFFSET FLAT:?wait@@YAXXZ		; wait
	mov	QWORD PTR funct, rax

; 34   : 		break;

	jmp	$LN42@x64_syscal
$LN39@x64_syscal:

; 35   : 	case 2:
; 36   : 		funct = (uint64_t*)create__sys_process;

	lea	rax, OFFSET FLAT:?create__sys_process@@YAHPEBDPEAD@Z ; create__sys_process
	mov	QWORD PTR funct, rax

; 37   : 		break;

	jmp	$LN42@x64_syscal
$LN38@x64_syscal:

; 38   : 	case 3:
; 39   : 		funct = (uint64_t*)copy_memory;

	lea	rax, OFFSET FLAT:?copy_memory@@YAXG_K0@Z ; copy_memory
	mov	QWORD PTR funct, rax

; 40   : 		break;

	jmp	$LN42@x64_syscal
$LN37@x64_syscal:

; 41   : 	case 4:
; 42   : 		funct = (uint64_t*)AuCreateShMem;

	lea	rax, OFFSET FLAT:?AuCreateShMem@@YAII_KI@Z ; AuCreateShMem
	mov	QWORD PTR funct, rax

; 43   : 		break;

	jmp	$LN42@x64_syscal
$LN36@x64_syscal:

; 44   : 	case 5:
; 45   : 		funct = (uint64_t*)valloc;

	lea	rax, OFFSET FLAT:?valloc@@YAX_K@Z	; valloc
	mov	QWORD PTR funct, rax

; 46   : 		break;

	jmp	$LN42@x64_syscal
$LN35@x64_syscal:

; 47   : 	case 6:
; 48   : 		funct = (uint64_t*)message_send;

	lea	rax, OFFSET FLAT:?message_send@@YAXGPEAU_message_@@@Z ; message_send
	mov	QWORD PTR funct, rax

; 49   : 		break;

	jmp	$LN42@x64_syscal
$LN34@x64_syscal:

; 50   : 	case 7:
; 51   : 		funct = (uint64_t*)message_receive;

	lea	rax, OFFSET FLAT:?message_receive@@YAXPEAU_message_@@@Z ; message_receive
	mov	QWORD PTR funct, rax

; 52   : 		break;

	jmp	$LN42@x64_syscal
$LN33@x64_syscal:

; 53   : 	case 8:
; 54   : 		funct = (uint64_t*)process_link_libraries;

	lea	rax, OFFSET FLAT:?process_link_libraries@@YAXXZ ; process_link_libraries
	mov	QWORD PTR funct, rax

; 55   : 		break;

	jmp	$LN42@x64_syscal
$LN32@x64_syscal:

; 56   : 	case 9:
; 57   : 		funct = (uint64_t*)get_thread_id;

	lea	rax, OFFSET FLAT:?get_thread_id@@YAGXZ	; get_thread_id
	mov	QWORD PTR funct, rax

; 58   : 		break;

	jmp	$LN42@x64_syscal
$LN31@x64_syscal:

; 59   : 	case 10:
; 60   : 		funct = (uint64_t*)create_timer;

	lea	rax, OFFSET FLAT:?create_timer@@YAHIG@Z	; create_timer
	mov	QWORD PTR funct, rax

; 61   : 		break;

	jmp	$LN42@x64_syscal
$LN30@x64_syscal:

; 62   : 	case 11:
; 63   : 		funct = (uint64_t*)destroy_timer;

	lea	rax, OFFSET FLAT:?destroy_timer@@YAXH@Z	; destroy_timer
	mov	QWORD PTR funct, rax

; 64   : 		break;

	jmp	$LN42@x64_syscal
$LN29@x64_syscal:

; 65   : 	case 12:
; 66   : 		funct = (uint64_t*)AuObtainShMem;

	lea	rax, OFFSET FLAT:?AuObtainShMem@@YAPEAXIPEAXH@Z ; AuObtainShMem
	mov	QWORD PTR funct, rax

; 67   : 		break;

	jmp	$LN42@x64_syscal
$LN28@x64_syscal:

; 68   : 	case 13:
; 69   : 		funct = (uint64_t*)ttype_create;

	lea	rax, OFFSET FLAT:?ttype_create@@YAHPEAH0@Z ; ttype_create
	mov	QWORD PTR funct, rax

; 70   : 		break;

	jmp	$LN42@x64_syscal
$LN27@x64_syscal:

; 71   : 	case 14:
; 72   : 		funct = (uint64_t*)start_timer;

	lea	rax, OFFSET FLAT:?start_timer@@YAXH@Z	; start_timer
	mov	QWORD PTR funct, rax

; 73   : 		break;

	jmp	$LN42@x64_syscal
$LN26@x64_syscal:

; 74   : 	case 15:
; 75   : 		funct = (uint64_t*)pause_timer;

	lea	rax, OFFSET FLAT:?pause_timer@@YAXH@Z	; pause_timer
	mov	QWORD PTR funct, rax

; 76   : 		break;

	jmp	$LN42@x64_syscal
$LN25@x64_syscal:

; 77   : 	case 16:
; 78   : 		funct = (uint64_t*)allocate_pipe;

	lea	rax, OFFSET FLAT:?allocate_pipe@@YAXPEAHPEAD@Z ; allocate_pipe
	mov	QWORD PTR funct, rax

; 79   : 		break;

	jmp	$LN42@x64_syscal
$LN24@x64_syscal:

; 80   : 	case 17:
; 81   : 		funct = (uint64_t*)sys_unblock_id;

	lea	rax, OFFSET FLAT:?sys_unblock_id@@YAXG@Z ; sys_unblock_id
	mov	QWORD PTR funct, rax

; 82   : 		break;

	jmp	$LN42@x64_syscal
$LN23@x64_syscal:

; 83   : 	case 18:
; 84   : 		funct = (uint64_t*)create_uthread;

	lea	rax, OFFSET FLAT:?create_uthread@@YAXP6AXPEAX@ZPEAD@Z ; create_uthread
	mov	QWORD PTR funct, rax

; 85   : 		break;

	jmp	$LN42@x64_syscal
$LN22@x64_syscal:

; 86   : 	case 19:
; 87   : 		funct = (uint64_t*)sys_open_file;

	lea	rax, OFFSET FLAT:?sys_open_file@@YAHPEADPEAU_file_@@@Z ; sys_open_file
	mov	QWORD PTR funct, rax

; 88   : 		break;

	jmp	$LN42@x64_syscal
$LN21@x64_syscal:

; 89   : 	case 20:
; 90   : 		funct = (uint64_t*)sys_read_file;

	lea	rax, OFFSET FLAT:?sys_read_file@@YAXHPEAEPEAU_file_@@@Z ; sys_read_file
	mov	QWORD PTR funct, rax

; 91   : 		break;

	jmp	$LN42@x64_syscal
$LN20@x64_syscal:

; 92   : 	case 21:
; 93   : 		funct = (uint64_t*)ttype_dup_master;

	lea	rax, OFFSET FLAT:?ttype_dup_master@@YAXHH@Z ; ttype_dup_master
	mov	QWORD PTR funct, rax

; 94   : 		break;

	jmp	$LN42@x64_syscal
$LN19@x64_syscal:

; 95   : 	case 22:
; 96   : 		funct = (uint64_t*)sys_get_used_ram;

	lea	rax, OFFSET FLAT:?sys_get_used_ram@@YA_KXZ ; sys_get_used_ram
	mov	QWORD PTR funct, rax

; 97   : 		break;

	jmp	$LN42@x64_syscal
$LN18@x64_syscal:

; 98   : 	case 23:
; 99   : 		funct = (uint64_t*)sys_get_free_ram;

	lea	rax, OFFSET FLAT:?sys_get_free_ram@@YA_KXZ ; sys_get_free_ram
	mov	QWORD PTR funct, rax

; 100  : 		break;

	jmp	$LN42@x64_syscal
$LN17@x64_syscal:

; 101  : 	case 24:
; 102  : 		funct = (uint64_t*)sys_sleep;

	lea	rax, OFFSET FLAT:?sys_sleep@@YAX_K@Z	; sys_sleep
	mov	QWORD PTR funct, rax

; 103  : 		break;

	jmp	$LN42@x64_syscal
$LN16@x64_syscal:

; 104  : 	case 25:
; 105  : 		funct = (uint64_t*)sys_exit;

	lea	rax, OFFSET FLAT:?sys_exit@@YAXXZ	; sys_exit
	mov	QWORD PTR funct, rax

; 106  : 		break;

	jmp	$LN42@x64_syscal
$LN15@x64_syscal:

; 107  : 	case 26:
; 108  : 		funct = (uint64_t*)sys_attach_ttype;

	lea	rax, OFFSET FLAT:?sys_attach_ttype@@YAXH@Z ; sys_attach_ttype
	mov	QWORD PTR funct, rax

; 109  : 		break;

	jmp	$LN42@x64_syscal
$LN14@x64_syscal:

; 110  : 	case 27:
; 111  : 		funct = (uint64_t*)fork;

	lea	rax, OFFSET FLAT:?fork@@YAIXZ		; fork
	mov	QWORD PTR funct, rax

; 112  : 		break;

	jmp	$LN42@x64_syscal
$LN13@x64_syscal:

; 113  : 	case 28:
; 114  : 		funct = (uint64_t*)exec;

	lea	rax, OFFSET FLAT:?exec@@YAXPEBDI@Z	; exec
	mov	QWORD PTR funct, rax

; 115  : 		break;

	jmp	$LN42@x64_syscal
$LN12@x64_syscal:

; 116  : 	case 29:
; 117  : 		funct = (uint64_t*)au_mmap;

	lea	rax, OFFSET FLAT:?au_mmap@@YAPEAXPEAX_KHHH1@Z ; au_mmap
	mov	QWORD PTR funct, rax

; 118  : 		break;

	jmp	$LN42@x64_syscal
$LN11@x64_syscal:

; 119  : 	case 30:
; 120  : 		funct = (uint64_t*)unmap_memory;

	lea	rax, OFFSET FLAT:?unmap_memory@@YAXPEAXI@Z ; unmap_memory
	mov	QWORD PTR funct, rax

; 121  : 		break;

	jmp	$LN42@x64_syscal
$LN10@x64_syscal:

; 122  : 	case 31:
; 123  : 		funct = (uint64_t*)ioquery;

	lea	rax, OFFSET FLAT:?ioquery@@YAXHHPEAX@Z	; ioquery
	mov	QWORD PTR funct, rax

; 124  : 		break;

	jmp	$LN42@x64_syscal
$LN9@x64_syscal:

; 125  : 	case 32:
; 126  : 		funct = (uint64_t*)sys_get_current_time;

	lea	rax, OFFSET FLAT:?sys_get_current_time@@YAXPEAU_sys_time_@@@Z ; sys_get_current_time
	mov	QWORD PTR funct, rax

; 127  : 		break;

	jmp	SHORT $LN42@x64_syscal
$LN8@x64_syscal:

; 128  : 	case 33:
; 129  : 		funct = (uint64_t*)sys_get_system_tick;

	lea	rax, OFFSET FLAT:?sys_get_system_tick@@YAIXZ ; sys_get_system_tick
	mov	QWORD PTR funct, rax

; 130  : 		break;

	jmp	SHORT $LN42@x64_syscal
$LN7@x64_syscal:

; 131  : 	case 34:
; 132  : 		funct = (uint64_t*)sys_kill;

	lea	rax, OFFSET FLAT:?sys_kill@@YAXHH@Z	; sys_kill
	mov	QWORD PTR funct, rax

; 133  : 		break;

	jmp	SHORT $LN42@x64_syscal
$LN6@x64_syscal:

; 134  : 	case 35:
; 135  : 		funct = (uint64_t*)sys_set_signal;

	lea	rax, OFFSET FLAT:?sys_set_signal@@YAXHP6AXH@Z@Z ; sys_set_signal
	mov	QWORD PTR funct, rax

; 136  : 		break;

	jmp	SHORT $LN42@x64_syscal
$LN5@x64_syscal:

; 137  : 	case 36:
; 138  : 		funct = (uint64_t*)shm_unlink;

	lea	rax, OFFSET FLAT:?shm_unlink@@YAXI@Z	; shm_unlink
	mov	QWORD PTR funct, rax

; 139  : 		break;

	jmp	SHORT $LN42@x64_syscal
$LN4@x64_syscal:

; 140  : 	case 37:
; 141  : 		funct = (uint64_t*)sys_write_file;

	lea	rax, OFFSET FLAT:?sys_write_file@@YAXHPEA_KPEAU_file_@@@Z ; sys_write_file
	mov	QWORD PTR funct, rax

; 142  : 		break;

	jmp	SHORT $LN42@x64_syscal
$LN3@x64_syscal:

; 143  : 	case 38:
; 144  : 		funct = (uint64_t*)vfree;

	lea	rax, OFFSET FLAT:?vfree@@YAX_K@Z	; vfree
	mov	QWORD PTR funct, rax

; 145  : 		break;

	jmp	SHORT $LN42@x64_syscal
$LN2@x64_syscal:

; 146  : 	case 39:
; 147  : 		funct = (uint64_t*)process_heap_break;

	lea	rax, OFFSET FLAT:?process_heap_break@@YAPEAX_K@Z ; process_heap_break
	mov	QWORD PTR funct, rax

; 148  : 		break;

	jmp	SHORT $LN42@x64_syscal
$LN1@x64_syscal:

; 149  : 	case 40:
; 150  : 		funct = (uint64_t*)sys_close_file; //dwm_dispatch_message;

	lea	rax, OFFSET FLAT:?sys_close_file@@YAXH@Z ; sys_close_file
	mov	QWORD PTR funct, rax
$LN42@x64_syscal:

; 151  : 		break;
; 152  : 	}
; 153  : 
; 154  : 	
; 155  : 	//! update the function pointer to syscall table index
; 156  : 	//funct = (uint64_t*)_syscalls[idx];
; 157  : 
; 158  : 	//return to the caller
; 159  : }

	add	rsp, 56					; 00000038H
	ret	0
	npad	2
$LN49@x64_syscal:
	DD	$LN41@x64_syscal
	DD	$LN40@x64_syscal
	DD	$LN39@x64_syscal
	DD	$LN38@x64_syscal
	DD	$LN37@x64_syscal
	DD	$LN36@x64_syscal
	DD	$LN35@x64_syscal
	DD	$LN34@x64_syscal
	DD	$LN33@x64_syscal
	DD	$LN32@x64_syscal
	DD	$LN31@x64_syscal
	DD	$LN30@x64_syscal
	DD	$LN29@x64_syscal
	DD	$LN28@x64_syscal
	DD	$LN27@x64_syscal
	DD	$LN26@x64_syscal
	DD	$LN25@x64_syscal
	DD	$LN24@x64_syscal
	DD	$LN23@x64_syscal
	DD	$LN22@x64_syscal
	DD	$LN21@x64_syscal
	DD	$LN20@x64_syscal
	DD	$LN19@x64_syscal
	DD	$LN18@x64_syscal
	DD	$LN17@x64_syscal
	DD	$LN16@x64_syscal
	DD	$LN15@x64_syscal
	DD	$LN14@x64_syscal
	DD	$LN13@x64_syscal
	DD	$LN12@x64_syscal
	DD	$LN11@x64_syscal
	DD	$LN10@x64_syscal
	DD	$LN9@x64_syscal
	DD	$LN8@x64_syscal
	DD	$LN7@x64_syscal
	DD	$LN6@x64_syscal
	DD	$LN5@x64_syscal
	DD	$LN4@x64_syscal
	DD	$LN3@x64_syscal
	DD	$LN2@x64_syscal
	DD	$LN1@x64_syscal
x64_syscall_handler ENDP
_TEXT	ENDS
END
