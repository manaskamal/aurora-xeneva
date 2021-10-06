; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?scheduler_enable@@3_NA				; scheduler_enable
PUBLIC	?block_mutex@@3PEAUmutex_t@@EA			; block_mutex
PUBLIC	?scheduler_mutex@@3PEAUmutex_t@@EA		; scheduler_mutex
PUBLIC	?scheduler_initialized@@3_NA			; scheduler_initialized
PUBLIC	?task_id@@3GA					; task_id
PUBLIC	?blocked_list@@3PEAU_list_@@EA			; blocked_list
PUBLIC	?task_list_head@@3PEAU_thread_@@EA		; task_list_head
PUBLIC	?task_list_last@@3PEAU_thread_@@EA		; task_list_last
PUBLIC	?system_tick@@3IA				; system_tick
PUBLIC	current_thread
_BSS	SEGMENT
?scheduler_enable@@3_NA DB 01H DUP (?)			; scheduler_enable
	ALIGN	8

?block_mutex@@3PEAUmutex_t@@EA DQ 01H DUP (?)		; block_mutex
?scheduler_mutex@@3PEAUmutex_t@@EA DQ 01H DUP (?)	; scheduler_mutex
?scheduler_initialized@@3_NA DB 01H DUP (?)		; scheduler_initialized
	ALIGN	4

?task_id@@3GA DW 01H DUP (?)				; task_id
	ALIGN	8

?blocked_list@@3PEAU_list_@@EA DQ 01H DUP (?)		; blocked_list
?task_list_head@@3PEAU_thread_@@EA DQ 01H DUP (?)	; task_list_head
?task_list_last@@3PEAU_thread_@@EA DQ 01H DUP (?)	; task_list_last
?system_tick@@3IA DD 01H DUP (?)			; system_tick
	ALIGN	8

current_thread DQ 01H DUP (?)
_BSS	ENDS
CONST	SEGMENT
$SG3300	DB	'Idle', 00H
CONST	ENDS
PUBLIC	?initialize_scheduler@@YAXXZ			; initialize_scheduler
PUBLIC	?scheduler_start@@YAXXZ				; scheduler_start
PUBLIC	?create_user_thread@@YAPEAU_thread_@@P6AXPEAX@Z_K2QEADE@Z ; create_user_thread
PUBLIC	?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z ; create_kthread
PUBLIC	?block_thread@@YAXPEAU_thread_@@@Z		; block_thread
PUBLIC	?unblock_thread@@YAXPEAU_thread_@@@Z		; unblock_thread
PUBLIC	?get_current_thread@@YAPEAU_thread_@@XZ		; get_current_thread
PUBLIC	?set_multi_task_enable@@YAX_N@Z			; set_multi_task_enable
PUBLIC	?is_multi_task_enable@@YA_NXZ			; is_multi_task_enable
PUBLIC	?force_sched@@YAXXZ				; force_sched
PUBLIC	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z	; thread_iterate_ready_list
PUBLIC	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z	; thread_iterate_block_list
PUBLIC	?thread_get_id_by_name@@YAGPEAD@Z		; thread_get_id_by_name
PUBLIC	?set_current_thread@@YAXPEAU_thread_@@@Z	; set_current_thread
PUBLIC	?sleep_thread@@YAXPEAU_thread_@@_K@Z		; sleep_thread
PUBLIC	?task_delete@@YAXPEAU_thread_@@@Z		; task_delete
PUBLIC	?is_scheduler_initialized@@YA_NXZ		; is_scheduler_initialized
PUBLIC	?sched_get_tick@@YAIXZ				; sched_get_tick
PUBLIC	?thread_insert@@YAXPEAU_thread_@@@Z		; thread_insert
PUBLIC	?idle_thread@@YAXXZ				; idle_thread
PUBLIC	?next_task@@YAXXZ				; next_task
PUBLIC	?scheduler_isr@@YAX_KPEAX@Z			; scheduler_isr
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?pmmngr_free@@YAXPEAX@Z:PROC			; pmmngr_free
EXTRN	x64_cli:PROC
EXTRN	x64_read_cr3:PROC
EXTRN	?setvect@@YAX_KP6AX0PEAX@Z@Z:PROC		; setvect
EXTRN	?map_page_ex@@YA_NPEA_K_K1@Z:PROC		; map_page_ex
EXTRN	save_context:PROC
EXTRN	execute_idle:PROC
EXTRN	get_kernel_tss:PROC
EXTRN	?allocate_kstack@@YA_KPEA_K@Z:PROC		; allocate_kstack
EXTRN	?apic_local_eoi@@YAXXZ:PROC			; apic_local_eoi
EXTRN	?create_mutex@@YAPEAUmutex_t@@XZ:PROC		; create_mutex
EXTRN	?mutex_lock@@YAXPEAUmutex_t@@@Z:PROC		; mutex_lock
EXTRN	?mutex_unlock@@YAXPEAUmutex_t@@@Z:PROC		; mutex_unlock
EXTRN	?initialize_list@@YAPEAU_list_@@XZ:PROC		; initialize_list
EXTRN	?list_add@@YAXPEAU_list_@@PEAX@Z:PROC		; list_add
EXTRN	?list_remove@@YAPEAXPEAU_list_@@I@Z:PROC	; list_remove
EXTRN	?list_get_at@@YAPEAXPEAU_list_@@I@Z:PROC	; list_get_at
EXTRN	x64_hlt:PROC
EXTRN	force_sched_apic:PROC
pdata	SEGMENT
$pdata$?initialize_scheduler@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+126
	DD	imagerel $unwind$?initialize_scheduler@@YAXXZ
$pdata$?scheduler_start@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+51
	DD	imagerel $unwind$?scheduler_start@@YAXXZ
$pdata$?create_user_thread@@YAPEAU_thread_@@P6AXPEAX@Z_K2QEADE@Z DD imagerel $LN3
	DD	imagerel $LN3+623
	DD	imagerel $unwind$?create_user_thread@@YAPEAU_thread_@@P6AXPEAX@Z_K2QEADE@Z
$pdata$?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z DD imagerel $LN3
	DD	imagerel $LN3+549
	DD	imagerel $unwind$?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z
$pdata$?block_thread@@YAXPEAU_thread_@@@Z DD imagerel $LN3
	DD	imagerel $LN3+53
	DD	imagerel $unwind$?block_thread@@YAXPEAU_thread_@@@Z
$pdata$?unblock_thread@@YAXPEAU_thread_@@@Z DD imagerel $LN7
	DD	imagerel $LN7+127
	DD	imagerel $unwind$?unblock_thread@@YAXPEAU_thread_@@@Z
$pdata$?force_sched@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+14
	DD	imagerel $unwind$?force_sched@@YAXXZ
$pdata$?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z DD imagerel $LN7
	DD	imagerel $LN7+79
	DD	imagerel $unwind$?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z
$pdata$?thread_iterate_block_list@@YAPEAU_thread_@@H@Z DD imagerel $LN8
	DD	imagerel $LN8+110
	DD	imagerel $unwind$?thread_iterate_block_list@@YAPEAU_thread_@@H@Z
$pdata$?thread_get_id_by_name@@YAGPEAD@Z DD imagerel $LN14
	DD	imagerel $LN14+223
	DD	imagerel $unwind$?thread_get_id_by_name@@YAGPEAD@Z
$pdata$?task_delete@@YAXPEAU_thread_@@@Z DD imagerel $LN8
	DD	imagerel $LN8+173
	DD	imagerel $unwind$?task_delete@@YAXPEAU_thread_@@@Z
$pdata$?idle_thread@@YAXXZ DD imagerel $LN5
	DD	imagerel $LN5+23
	DD	imagerel $unwind$?idle_thread@@YAXXZ
$pdata$?next_task@@YAXXZ DD imagerel $LN9
	DD	imagerel $LN9+147
	DD	imagerel $unwind$?next_task@@YAXXZ
$pdata$?scheduler_isr@@YAX_KPEAX@Z DD imagerel $LN8
	DD	imagerel $LN8+269
	DD	imagerel $unwind$?scheduler_isr@@YAX_KPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?initialize_scheduler@@YAXXZ DD 010401H
	DD	08204H
$unwind$?scheduler_start@@YAXXZ DD 010401H
	DD	04204H
$unwind$?create_user_thread@@YAPEAU_thread_@@P6AXPEAX@Z_K2QEADE@Z DD 011801H
	DD	06218H
$unwind$?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z DD 011801H
	DD	06218H
$unwind$?block_thread@@YAXPEAU_thread_@@@Z DD 010901H
	DD	04209H
$unwind$?unblock_thread@@YAXPEAU_thread_@@@Z DD 010901H
	DD	06209H
$unwind$?force_sched@@YAXXZ DD 010401H
	DD	04204H
$unwind$?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z DD 010901H
	DD	02209H
$unwind$?thread_iterate_block_list@@YAPEAU_thread_@@H@Z DD 010801H
	DD	06208H
$unwind$?thread_get_id_by_name@@YAGPEAD@Z DD 010901H
	DD	08209H
$unwind$?task_delete@@YAXPEAU_thread_@@@Z DD 010901H
	DD	04209H
$unwind$?idle_thread@@YAXXZ DD 010401H
	DD	04204H
$unwind$?next_task@@YAXXZ DD 010401H
	DD	02204H
$unwind$?scheduler_isr@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
v$ = 48
param$ = 56
?scheduler_isr@@YAX_KPEAX@Z PROC			; scheduler_isr

; 232  : void scheduler_isr (size_t v, void* param) {

$LN8:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 233  : 	x64_cli();

	call	x64_cli

; 234  : 	//interrupt_stack_frame *frame = (interrupt_stack_frame*)param;
; 235  : 	if (scheduler_enable == false)

	movzx	eax, BYTE PTR ?scheduler_enable@@3_NA	; scheduler_enable
	test	eax, eax
	jne	SHORT $LN5@scheduler_

; 236  : 		goto sched_end;

	jmp	$LN4@scheduler_
	jmp	$sched_end$9
$LN5@scheduler_:

; 237  : 	mutex_lock (scheduler_mutex);

	mov	rcx, QWORD PTR ?scheduler_mutex@@3PEAUmutex_t@@EA ; scheduler_mutex
	call	?mutex_lock@@YAXPEAUmutex_t@@@Z		; mutex_lock

; 238  :    
; 239  : 	if (save_context(current_thread,get_kernel_tss()) == 0) {

	call	get_kernel_tss
	mov	rdx, rax
	mov	rcx, QWORD PTR current_thread
	call	save_context
	test	eax, eax
	jne	$LN3@scheduler_

; 240  : 		current_thread->cr3 = x64_read_cr3();

	call	x64_read_cr3
	mov	rcx, QWORD PTR current_thread
	mov	QWORD PTR [rcx+192], rax

; 241  : 		if (current_thread->priviledge == THREAD_LEVEL_USER)

	mov	rax, QWORD PTR current_thread
	movzx	eax, BYTE PTR [rax+228]
	cmp	eax, 2
	jne	SHORT $LN2@scheduler_

; 242  : 			current_thread->kern_esp = get_kernel_tss()->rsp[0];

	call	get_kernel_tss
	mov	ecx, 8
	imul	rcx, 0
	mov	rdx, QWORD PTR current_thread
	mov	rax, QWORD PTR [rax+rcx+4]
	mov	QWORD PTR [rdx+200], rax
$LN2@scheduler_:

; 243  : 
; 244  : 		system_tick++;

	mov	eax, DWORD PTR ?system_tick@@3IA	; system_tick
	inc	eax
	mov	DWORD PTR ?system_tick@@3IA, eax	; system_tick

; 245  : #ifdef USE_APIC
; 246  : 		apic_local_eoi();

	call	?apic_local_eoi@@YAXXZ			; apic_local_eoi

; 247  : #endif
; 248  : #ifdef USE_PIC
; 249  : 		interrupt_end (0);
; 250  : #endif
; 251  : 		next_task();

	call	?next_task@@YAXXZ			; next_task

; 252  : 		if (current_thread->priviledge == THREAD_LEVEL_USER){

	mov	rax, QWORD PTR current_thread
	movzx	eax, BYTE PTR [rax+228]
	cmp	eax, 2
	jne	SHORT $LN1@scheduler_

; 253  : 			get_kernel_tss()->rsp[0] = current_thread->kern_esp;

	call	get_kernel_tss
	mov	ecx, 8
	imul	rcx, 0
	mov	rdx, QWORD PTR current_thread
	mov	rdx, QWORD PTR [rdx+200]
	mov	QWORD PTR [rax+rcx+4], rdx
$LN1@scheduler_:

; 254  : 		}
; 255  : 		
; 256  : 		mutex_unlock (scheduler_mutex);

	mov	rcx, QWORD PTR ?scheduler_mutex@@3PEAUmutex_t@@EA ; scheduler_mutex
	call	?mutex_unlock@@YAXPEAUmutex_t@@@Z	; mutex_unlock

; 257  : 		execute_idle (current_thread,get_kernel_tss());

	call	get_kernel_tss
	mov	rdx, rax
	mov	rcx, QWORD PTR current_thread
	call	execute_idle
$LN3@scheduler_:
$LN4@scheduler_:
$sched_end$9:

; 258  : 	}
; 259  : 
; 260  : sched_end:
; 261  : #ifdef USE_APIC
; 262  : 	apic_local_eoi();

	call	?apic_local_eoi@@YAXXZ			; apic_local_eoi

; 263  : #endif
; 264  : #ifdef USE_PIC
; 265  : 	interrupt_end(0);
; 266  : #endif
; 267  : 	//x64_sti();
; 268  : 	
; 269  : }

	add	rsp, 40					; 00000028H
	ret	0
?scheduler_isr@@YAX_KPEAX@Z ENDP			; scheduler_isr
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
task$ = 0
?next_task@@YAXXZ PROC					; next_task

; 195  : void next_task () {

$LN9:
	sub	rsp, 24

; 196  : 	thread_t* task = current_thread;

	mov	rax, QWORD PTR current_thread
	mov	QWORD PTR task$[rsp], rax
$LN6@next_task:

; 197  : 	do {
; 198  : 		if (task->state == THREAD_STATE_SLEEP) {

	mov	rax, QWORD PTR task$[rsp]
	movzx	eax, BYTE PTR [rax+224]
	cmp	eax, 4
	jne	SHORT $LN3@next_task

; 199  : 			if (task->quanta == 0) {

	mov	rax, QWORD PTR task$[rsp]
	movzx	eax, WORD PTR [rax+230]
	test	eax, eax
	jne	SHORT $LN2@next_task

; 200  : 				task->state = THREAD_STATE_READY;

	mov	rax, QWORD PTR task$[rsp]
	mov	BYTE PTR [rax+224], 1
$LN2@next_task:

; 201  : 			}
; 202  : 			task->quanta--;

	mov	rax, QWORD PTR task$[rsp]
	movzx	eax, WORD PTR [rax+230]
	dec	ax
	mov	rcx, QWORD PTR task$[rsp]
	mov	WORD PTR [rcx+230], ax
$LN3@next_task:

; 203  : 		}
; 204  : 		task = task->next;

	mov	rax, QWORD PTR task$[rsp]
	mov	rax, QWORD PTR [rax+264]
	mov	QWORD PTR task$[rsp], rax

; 205  : 		if (task == NULL) {

	cmp	QWORD PTR task$[rsp], 0
	jne	SHORT $LN1@next_task

; 206  : 			task = task_list_head;

	mov	rax, QWORD PTR ?task_list_head@@3PEAU_thread_@@EA ; task_list_head
	mov	QWORD PTR task$[rsp], rax
$LN1@next_task:

; 207  : 		}
; 208  : 	}while (task->state != THREAD_STATE_READY);

	mov	rax, QWORD PTR task$[rsp]
	movzx	eax, BYTE PTR [rax+224]
	cmp	eax, 1
	jne	SHORT $LN6@next_task
$end$10:

; 209  : 
; 210  : 	//if (task->state == THREAD_STATE_BLOCKED) {
; 211  : 	//	task = task->next;
; 212  : 
; 213  : 	//	if (task == NULL) {
; 214  : 	//		task = task_list_head;
; 215  : 	//	}
; 216  : 	//	goto end;
; 217  : 	//}
; 218  : 
; 219  : 	//if (task->next != NULL) {
; 220  : 	//	task = task->next;
; 221  : 	//} else {
; 222  : 	//	task = task_list_head;
; 223  : 	//}
; 224  : 
; 225  : end:
; 226  : 	current_thread = task;

	mov	rax, QWORD PTR task$[rsp]
	mov	QWORD PTR current_thread, rax

; 227  : }

	add	rsp, 24
	ret	0
?next_task@@YAXXZ ENDP					; next_task
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
?idle_thread@@YAXXZ PROC				; idle_thread

; 176  : void idle_thread () {

$LN5:
	sub	rsp, 40					; 00000028H
$LN2@idle_threa:

; 177  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@idle_threa

; 178  : 		x64_hlt();

	call	x64_hlt

; 179  : 	}

	jmp	SHORT $LN2@idle_threa
$LN1@idle_threa:

; 180  : }

	add	rsp, 40					; 00000028H
	ret	0
?idle_thread@@YAXXZ ENDP				; idle_thread
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
new_task$ = 8
?thread_insert@@YAXPEAU_thread_@@@Z PROC		; thread_insert

; 46   : void thread_insert (thread_t* new_task ) {

	mov	QWORD PTR [rsp+8], rcx

; 47   : 	new_task->next = NULL;

	mov	rax, QWORD PTR new_task$[rsp]
	mov	QWORD PTR [rax+264], 0

; 48   : 	new_task->prev = NULL;

	mov	rax, QWORD PTR new_task$[rsp]
	mov	QWORD PTR [rax+272], 0

; 49   : 
; 50   : 	if (task_list_head == NULL) {

	cmp	QWORD PTR ?task_list_head@@3PEAU_thread_@@EA, 0 ; task_list_head
	jne	SHORT $LN2@thread_ins

; 51   : 		task_list_last = new_task;

	mov	rax, QWORD PTR new_task$[rsp]
	mov	QWORD PTR ?task_list_last@@3PEAU_thread_@@EA, rax ; task_list_last

; 52   : 		task_list_head = new_task;

	mov	rax, QWORD PTR new_task$[rsp]
	mov	QWORD PTR ?task_list_head@@3PEAU_thread_@@EA, rax ; task_list_head

; 53   : 		current_thread = task_list_last;

	mov	rax, QWORD PTR ?task_list_last@@3PEAU_thread_@@EA ; task_list_last
	mov	QWORD PTR current_thread, rax

; 54   : 	} else {

	jmp	SHORT $LN1@thread_ins
$LN2@thread_ins:

; 55   : 		task_list_last->next = new_task;

	mov	rax, QWORD PTR ?task_list_last@@3PEAU_thread_@@EA ; task_list_last
	mov	rcx, QWORD PTR new_task$[rsp]
	mov	QWORD PTR [rax+264], rcx

; 56   : 		new_task->prev = task_list_last;

	mov	rax, QWORD PTR new_task$[rsp]
	mov	rcx, QWORD PTR ?task_list_last@@3PEAU_thread_@@EA ; task_list_last
	mov	QWORD PTR [rax+272], rcx
$LN1@thread_ins:

; 57   : 	}
; 58   : 	task_list_last = new_task;

	mov	rax, QWORD PTR new_task$[rsp]
	mov	QWORD PTR ?task_list_last@@3PEAU_thread_@@EA, rax ; task_list_last

; 59   : }

	ret	0
?thread_insert@@YAXPEAU_thread_@@@Z ENDP		; thread_insert
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
?sched_get_tick@@YAIXZ PROC				; sched_get_tick

; 399  : 	return system_tick;

	mov	eax, DWORD PTR ?system_tick@@3IA	; system_tick

; 400  : }

	ret	0
?sched_get_tick@@YAIXZ ENDP				; sched_get_tick
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
?is_scheduler_initialized@@YA_NXZ PROC			; is_scheduler_initialized

; 395  : 	return scheduler_initialized;

	movzx	eax, BYTE PTR ?scheduler_initialized@@3_NA ; scheduler_initialized

; 396  : }

	ret	0
?is_scheduler_initialized@@YA_NXZ ENDP			; is_scheduler_initialized
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
thread$ = 48
?task_delete@@YAXPEAU_thread_@@@Z PROC			; task_delete

; 62   : void task_delete (thread_t* thread) {

$LN8:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 63   : 
; 64   : 	if (task_list_head == NULL)

	cmp	QWORD PTR ?task_list_head@@3PEAU_thread_@@EA, 0 ; task_list_head
	jne	SHORT $LN5@task_delet

; 65   : 		return;

	jmp	$LN6@task_delet
$LN5@task_delet:

; 66   : 
; 67   : 	if (thread == task_list_head) {

	mov	rax, QWORD PTR ?task_list_head@@3PEAU_thread_@@EA ; task_list_head
	cmp	QWORD PTR thread$[rsp], rax
	jne	SHORT $LN4@task_delet

; 68   : 		task_list_head = task_list_head->next;

	mov	rax, QWORD PTR ?task_list_head@@3PEAU_thread_@@EA ; task_list_head
	mov	rax, QWORD PTR [rax+264]
	mov	QWORD PTR ?task_list_head@@3PEAU_thread_@@EA, rax ; task_list_head

; 69   : 	} else {

	jmp	SHORT $LN3@task_delet
$LN4@task_delet:

; 70   : 		thread->prev->next = thread->next;

	mov	rax, QWORD PTR thread$[rsp]
	mov	rax, QWORD PTR [rax+272]
	mov	rcx, QWORD PTR thread$[rsp]
	mov	rcx, QWORD PTR [rcx+264]
	mov	QWORD PTR [rax+264], rcx
$LN3@task_delet:

; 71   : 	}
; 72   : 
; 73   : 	if (thread == task_list_last) {

	mov	rax, QWORD PTR ?task_list_last@@3PEAU_thread_@@EA ; task_list_last
	cmp	QWORD PTR thread$[rsp], rax
	jne	SHORT $LN2@task_delet

; 74   : 		task_list_last = thread->prev;

	mov	rax, QWORD PTR thread$[rsp]
	mov	rax, QWORD PTR [rax+272]
	mov	QWORD PTR ?task_list_last@@3PEAU_thread_@@EA, rax ; task_list_last

; 75   : 	} else {

	jmp	SHORT $LN1@task_delet
$LN2@task_delet:

; 76   : 		thread->next->prev = thread->prev;

	mov	rax, QWORD PTR thread$[rsp]
	mov	rax, QWORD PTR [rax+264]
	mov	rcx, QWORD PTR thread$[rsp]
	mov	rcx, QWORD PTR [rcx+272]
	mov	QWORD PTR [rax+272], rcx
$LN1@task_delet:

; 77   : 	}
; 78   : 
; 79   : 	pmmngr_free (thread);

	mov	rcx, QWORD PTR thread$[rsp]
	call	?pmmngr_free@@YAXPEAX@Z			; pmmngr_free
$LN6@task_delet:

; 80   : }

	add	rsp, 40					; 00000028H
	ret	0
?task_delete@@YAXPEAU_thread_@@@Z ENDP			; task_delete
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
t$ = 8
ms$ = 16
?sleep_thread@@YAXPEAU_thread_@@_K@Z PROC		; sleep_thread

; 374  : void sleep_thread (thread_t *t, uint64_t ms) {

	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx

; 375  : 	t->quanta = ms;

	mov	rax, QWORD PTR t$[rsp]
	movzx	ecx, WORD PTR ms$[rsp]
	mov	WORD PTR [rax+230], cx

; 376  : 	//printf ("Sleeping thread -> %d\n", t->quanta);
; 377  : 	t->state = THREAD_STATE_SLEEP;

	mov	rax, QWORD PTR t$[rsp]
	mov	BYTE PTR [rax+224], 4

; 378  : }

	ret	0
?sleep_thread@@YAXPEAU_thread_@@_K@Z ENDP		; sleep_thread
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
thread$ = 8
?set_current_thread@@YAXPEAU_thread_@@@Z PROC		; set_current_thread

; 293  : void set_current_thread (thread_t *thread) {

	mov	QWORD PTR [rsp+8], rcx

; 294  : 	current_thread = thread;

	mov	rax, QWORD PTR thread$[rsp]
	mov	QWORD PTR current_thread, rax

; 295  : }

	ret	0
?set_current_thread@@YAXPEAU_thread_@@@Z ENDP		; set_current_thread
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
id$ = 32
i$1 = 36
it$2 = 40
t$3 = 48
name$ = 80
?thread_get_id_by_name@@YAGPEAD@Z PROC			; thread_get_id_by_name

; 337  : uint16_t thread_get_id_by_name (char* name) {

$LN14:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 338  : 	uint16_t id = 0;

	xor	eax, eax
	mov	WORD PTR id$[rsp], ax

; 339  : 	for (thread_t *it = task_list_head; it != NULL; it = it->next) {

	mov	rax, QWORD PTR ?task_list_head@@3PEAU_thread_@@EA ; task_list_head
	mov	QWORD PTR it$2[rsp], rax
	jmp	SHORT $LN11@thread_get
$LN10@thread_get:
	mov	rax, QWORD PTR it$2[rsp]
	mov	rax, QWORD PTR [rax+264]
	mov	QWORD PTR it$2[rsp], rax
$LN11@thread_get:
	cmp	QWORD PTR it$2[rsp], 0
	je	SHORT $LN9@thread_get

; 340  : 		if (it->name == name) {

	mov	rax, QWORD PTR it$2[rsp]
	mov	rcx, QWORD PTR name$[rsp]
	cmp	QWORD PTR [rax+216], rcx
	jne	SHORT $LN8@thread_get

; 341  : 			id = it->id;

	mov	rax, QWORD PTR it$2[rsp]
	movzx	eax, WORD PTR [rax+226]
	mov	WORD PTR id$[rsp], ax

; 342  : 			break;

	jmp	SHORT $LN9@thread_get
$LN8@thread_get:

; 343  : 		}
; 344  : 	}

	jmp	SHORT $LN10@thread_get
$LN9@thread_get:

; 345  : 
; 346  : 	if (id > 0)

	movzx	eax, WORD PTR id$[rsp]
	test	eax, eax
	jle	SHORT $LN7@thread_get

; 347  : 		return id;

	movzx	eax, WORD PTR id$[rsp]
	jmp	SHORT $LN12@thread_get

; 348  : 	else{

	jmp	SHORT $LN6@thread_get
$LN7@thread_get:

; 349  : 		if (blocked_list->pointer >0)

	mov	rax, QWORD PTR ?blocked_list@@3PEAU_list_@@EA ; blocked_list
	cmp	DWORD PTR [rax], 0
	jbe	SHORT $LN5@thread_get

; 350  : 			for (int i = 0; i < blocked_list->pointer; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN4@thread_get
$LN3@thread_get:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN4@thread_get:
	mov	rax, QWORD PTR ?blocked_list@@3PEAU_list_@@EA ; blocked_list
	mov	eax, DWORD PTR [rax]
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN2@thread_get

; 351  : 				thread_t*  t = (thread_t*)list_get_at (blocked_list,i);

	mov	edx, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR ?blocked_list@@3PEAU_list_@@EA ; blocked_list
	call	?list_get_at@@YAPEAXPEAU_list_@@I@Z	; list_get_at
	mov	QWORD PTR t$3[rsp], rax

; 352  : 				if (t->name == name) {

	mov	rax, QWORD PTR t$3[rsp]
	mov	rcx, QWORD PTR name$[rsp]
	cmp	QWORD PTR [rax+216], rcx
	jne	SHORT $LN1@thread_get

; 353  : 					return t->id;

	mov	rax, QWORD PTR t$3[rsp]
	movzx	eax, WORD PTR [rax+226]
	jmp	SHORT $LN12@thread_get
$LN1@thread_get:

; 354  : 				}
; 355  : 			}

	jmp	SHORT $LN3@thread_get
$LN2@thread_get:
$LN5@thread_get:
$LN6@thread_get:

; 356  : 	}
; 357  : 
; 358  : 	return NULL;

	xor	eax, eax
$LN12@thread_get:

; 359  : }

	add	rsp, 72					; 00000048H
	ret	0
?thread_get_id_by_name@@YAGPEAD@Z ENDP			; thread_get_id_by_name
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
i$1 = 32
t$2 = 40
id$ = 64
?thread_iterate_block_list@@YAPEAU_thread_@@H@Z PROC	; thread_iterate_block_list

; 315  : thread_t* thread_iterate_block_list (int id) {

$LN8:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 316  : 	if (blocked_list->pointer >0)

	mov	rax, QWORD PTR ?blocked_list@@3PEAU_list_@@EA ; blocked_list
	cmp	DWORD PTR [rax], 0
	jbe	SHORT $LN5@thread_ite

; 317  : 		for (int i = 0; i < blocked_list->pointer; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN4@thread_ite
$LN3@thread_ite:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN4@thread_ite:
	mov	rax, QWORD PTR ?blocked_list@@3PEAU_list_@@EA ; blocked_list
	mov	eax, DWORD PTR [rax]
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN2@thread_ite

; 318  : 			thread_t*  t = (thread_t*)list_get_at (blocked_list,i);

	mov	edx, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR ?blocked_list@@3PEAU_list_@@EA ; blocked_list
	call	?list_get_at@@YAPEAXPEAU_list_@@I@Z	; list_get_at
	mov	QWORD PTR t$2[rsp], rax

; 319  : 			if (t->id == id) {

	mov	rax, QWORD PTR t$2[rsp]
	movzx	eax, WORD PTR [rax+226]
	cmp	eax, DWORD PTR id$[rsp]
	jne	SHORT $LN1@thread_ite

; 320  : 				return t;

	mov	rax, QWORD PTR t$2[rsp]
	jmp	SHORT $LN6@thread_ite
$LN1@thread_ite:

; 321  : 		}
; 322  : 	}

	jmp	SHORT $LN3@thread_ite
$LN2@thread_ite:
$LN5@thread_ite:

; 323  : 	return NULL;

	xor	eax, eax
$LN6@thread_ite:

; 324  : }

	add	rsp, 56					; 00000038H
	ret	0
?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ENDP	; thread_iterate_block_list
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
it$1 = 0
id$ = 32
?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z PROC	; thread_iterate_ready_list

; 327  : thread_t * thread_iterate_ready_list (uint16_t id) {

$LN7:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 24

; 328  : 	for (thread_t *it = task_list_head; it != NULL; it = it->next) {

	mov	rax, QWORD PTR ?task_list_head@@3PEAU_thread_@@EA ; task_list_head
	mov	QWORD PTR it$1[rsp], rax
	jmp	SHORT $LN4@thread_ite
$LN3@thread_ite:
	mov	rax, QWORD PTR it$1[rsp]
	mov	rax, QWORD PTR [rax+264]
	mov	QWORD PTR it$1[rsp], rax
$LN4@thread_ite:
	cmp	QWORD PTR it$1[rsp], 0
	je	SHORT $LN2@thread_ite

; 329  : 		if (it->id == id) {

	mov	rax, QWORD PTR it$1[rsp]
	movzx	eax, WORD PTR [rax+226]
	movzx	ecx, WORD PTR id$[rsp]
	cmp	eax, ecx
	jne	SHORT $LN1@thread_ite

; 330  : 			return it;

	mov	rax, QWORD PTR it$1[rsp]
	jmp	SHORT $LN5@thread_ite
$LN1@thread_ite:

; 331  : 		}
; 332  : 	}

	jmp	SHORT $LN3@thread_ite
$LN2@thread_ite:

; 333  : 	return NULL;

	xor	eax, eax
$LN5@thread_ite:

; 334  : }

	add	rsp, 24
	ret	0
?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z ENDP	; thread_iterate_ready_list
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
?force_sched@@YAXXZ PROC				; force_sched

; 386  : void force_sched () {

$LN3:
	sub	rsp, 40					; 00000028H

; 387  : #ifdef USE_APIC
; 388  : 	force_sched_apic();

	call	force_sched_apic

; 389  : #elif USE_PIC
; 390  : 	force_sched_pic();
; 391  : #endif
; 392  : }

	add	rsp, 40					; 00000028H
	ret	0
?force_sched@@YAXXZ ENDP				; force_sched
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
?is_multi_task_enable@@YA_NXZ PROC			; is_multi_task_enable

; 301  : 	return scheduler_enable;

	movzx	eax, BYTE PTR ?scheduler_enable@@3_NA	; scheduler_enable

; 302  : }

	ret	0
?is_multi_task_enable@@YA_NXZ ENDP			; is_multi_task_enable
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
value$ = 8
?set_multi_task_enable@@YAX_N@Z PROC			; set_multi_task_enable

; 286  : void set_multi_task_enable (bool value) {

	mov	BYTE PTR [rsp+8], cl

; 287  : 	if (scheduler_enable == value)

	movzx	eax, BYTE PTR ?scheduler_enable@@3_NA	; scheduler_enable
	movzx	ecx, BYTE PTR value$[rsp]
	cmp	eax, ecx
	jne	SHORT $LN1@set_multi_

; 288  : 		return;

	jmp	SHORT $LN2@set_multi_
$LN1@set_multi_:

; 289  : 
; 290  : 	scheduler_enable = value;

	movzx	eax, BYTE PTR value$[rsp]
	mov	BYTE PTR ?scheduler_enable@@3_NA, al	; scheduler_enable
$LN2@set_multi_:

; 291  : }

	fatret	0
?set_multi_task_enable@@YAX_N@Z ENDP			; set_multi_task_enable
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
?get_current_thread@@YAPEAU_thread_@@XZ PROC		; get_current_thread

; 382  : 	return current_thread;

	mov	rax, QWORD PTR current_thread

; 383  : }

	ret	0
?get_current_thread@@YAPEAU_thread_@@XZ ENDP		; get_current_thread
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
i$1 = 32
thr$2 = 40
t$ = 64
?unblock_thread@@YAXPEAU_thread_@@@Z PROC		; unblock_thread

; 362  : void unblock_thread (thread_t *t) {

$LN7:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 363  : 	x64_cli();

	call	x64_cli

; 364  : 	t->state = THREAD_STATE_READY;

	mov	rax, QWORD PTR t$[rsp]
	mov	BYTE PTR [rax+224], 1

; 365  : 	thread_insert (t);

	mov	rcx, QWORD PTR t$[rsp]
	call	?thread_insert@@YAXPEAU_thread_@@@Z	; thread_insert

; 366  : 	for (int i = 0; i < blocked_list->pointer; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN4@unblock_th
$LN3@unblock_th:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN4@unblock_th:
	mov	rax, QWORD PTR ?blocked_list@@3PEAU_list_@@EA ; blocked_list
	mov	eax, DWORD PTR [rax]
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN2@unblock_th

; 367  : 		thread_t *thr = (thread_t*)list_get_at(blocked_list,i);

	mov	edx, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR ?blocked_list@@3PEAU_list_@@EA ; blocked_list
	call	?list_get_at@@YAPEAXPEAU_list_@@I@Z	; list_get_at
	mov	QWORD PTR thr$2[rsp], rax

; 368  : 		if (thr == t) 

	mov	rax, QWORD PTR t$[rsp]
	cmp	QWORD PTR thr$2[rsp], rax
	jne	SHORT $LN1@unblock_th

; 369  : 			list_remove (blocked_list,i);

	mov	edx, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR ?blocked_list@@3PEAU_list_@@EA ; blocked_list
	call	?list_remove@@YAPEAXPEAU_list_@@I@Z	; list_remove
$LN1@unblock_th:

; 370  : 	}

	jmp	SHORT $LN3@unblock_th
$LN2@unblock_th:

; 371  : }

	add	rsp, 56					; 00000038H
	ret	0
?unblock_thread@@YAXPEAU_thread_@@@Z ENDP		; unblock_thread
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
thread$ = 48
?block_thread@@YAXPEAU_thread_@@@Z PROC			; block_thread

; 306  : void block_thread (thread_t *thread) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 307  : 	thread->state = THREAD_STATE_BLOCKED;

	mov	rax, QWORD PTR thread$[rsp]
	mov	BYTE PTR [rax+224], 3

; 308  : 	task_delete (thread);

	mov	rcx, QWORD PTR thread$[rsp]
	call	?task_delete@@YAXPEAU_thread_@@@Z	; task_delete

; 309  : 	list_add (blocked_list,thread);

	mov	rdx, QWORD PTR thread$[rsp]
	mov	rcx, QWORD PTR ?blocked_list@@3PEAU_list_@@EA ; blocked_list
	call	?list_add@@YAXPEAU_list_@@PEAX@Z	; list_add

; 310  : }

	add	rsp, 40					; 00000028H
	ret	0
?block_thread@@YAXPEAU_thread_@@@Z ENDP			; block_thread
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
t$ = 32
entry$ = 64
stack$ = 72
cr3$ = 80
name$ = 88
priority$ = 96
?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z PROC	; create_kthread

; 89   : {

$LN3:
	mov	QWORD PTR [rsp+32], r9
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 90   : 	thread_t *t = (thread_t*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR t$[rsp], rax

; 91   : 	t->ss = 0x10;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax], 16

; 92   : 	t->rsp = (uint64_t*)stack;

	mov	rax, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR stack$[rsp]
	mov	QWORD PTR [rax+8], rcx

; 93   : 	t->rflags = 0x202;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+16], 514			; 00000202H

; 94   : 	t->cs = 0x08;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+24], 8

; 95   : 	t->rip = (uint64_t)entry;

	mov	rax, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR entry$[rsp]
	mov	QWORD PTR [rax+32], rcx

; 96   : 	t->rax = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+40], 0

; 97   : 	t->rbx = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+48], 0

; 98   : 	t->rcx = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+56], 0

; 99   : 	t->rdx = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+64], 0

; 100  : 	t->rsi = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+72], 0

; 101  : 	t->rdi = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+80], 0

; 102  : 	t->rbp = (uint64_t)t->rsp;

	mov	rax, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR [rcx+8]
	mov	QWORD PTR [rax+88], rcx

; 103  : 	t->r8 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+96], 0

; 104  : 	t->r9 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+104], 0

; 105  : 	t->r10 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+112], 0

; 106  : 	t->r11 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+120], 0

; 107  : 	t->r12 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+128], 0

; 108  : 	t->r13 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+136], 0

; 109  : 	t->r14 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+144], 0

; 110  : 	t->r15 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+152], 0

; 111  : 	t->ds = 0x10;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+160], 16

; 112  : 	t->es = 0x10;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+168], 16

; 113  : 	t->fs = 0x10;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+176], 16

; 114  : 	t->gs = 0x10;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+184], 16

; 115  : 	t->kern_esp = stack;

	mov	rax, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR stack$[rsp]
	mov	QWORD PTR [rax+200], rcx

; 116  : 	t->_is_user = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	BYTE PTR [rax+208], 0

; 117  : 	t->cr3 = cr3;

	mov	rax, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR cr3$[rsp]
	mov	QWORD PTR [rax+192], rcx

; 118  : 	t->name = name;

	mov	rax, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR name$[rsp]
	mov	QWORD PTR [rax+216], rcx

; 119  : 	t->id = task_id++;

	mov	rax, QWORD PTR t$[rsp]
	movzx	ecx, WORD PTR ?task_id@@3GA		; task_id
	mov	WORD PTR [rax+226], cx
	movzx	eax, WORD PTR ?task_id@@3GA		; task_id
	inc	ax
	mov	WORD PTR ?task_id@@3GA, ax		; task_id

; 120  : 	t->quanta = 0;

	xor	eax, eax
	mov	rcx, QWORD PTR t$[rsp]
	mov	WORD PTR [rcx+230], ax

; 121  : 	t->priviledge = THREAD_LEVEL_KERNEL;

	mov	rax, QWORD PTR t$[rsp]
	mov	BYTE PTR [rax+228], 1

; 122  : 	t->state = THREAD_STATE_READY;

	mov	rax, QWORD PTR t$[rsp]
	mov	BYTE PTR [rax+224], 1

; 123  : 	t->priority = priority;

	mov	rax, QWORD PTR t$[rsp]
	movzx	ecx, BYTE PTR priority$[rsp]
	mov	BYTE PTR [rax+256], cl

; 124  : 	thread_insert(t);

	mov	rcx, QWORD PTR t$[rsp]
	call	?thread_insert@@YAXPEAU_thread_@@@Z	; thread_insert

; 125  : 	return t;

	mov	rax, QWORD PTR t$[rsp]

; 126  : }

	add	rsp, 56					; 00000038H
	ret	0
?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z ENDP	; create_kthread
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
t$ = 32
entry$ = 64
stack$ = 72
cr3$ = 80
name$ = 88
priority$ = 96
?create_user_thread@@YAPEAU_thread_@@P6AXPEAX@Z_K2QEADE@Z PROC ; create_user_thread

; 132  : {

$LN3:
	mov	QWORD PTR [rsp+32], r9
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 133  : 	thread_t *t = (thread_t*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR t$[rsp], rax

; 134  : 	t->ss = SEGVAL(GDT_ENTRY_USER_DATA,3);//0x23; 

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax], 35			; 00000023H

; 135  : 	t->rsp = (uint64_t*)stack;

	mov	rax, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR stack$[rsp]
	mov	QWORD PTR [rax+8], rcx

; 136  : 	t->rflags = 0x286;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+16], 646			; 00000286H

; 137  : 	t->cs = SEGVAL (GDT_ENTRY_USER_CODE,3);// 0x2b;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+24], 43			; 0000002bH

; 138  : 	t->rip = (uint64_t)entry;

	mov	rax, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR entry$[rsp]
	mov	QWORD PTR [rax+32], rcx

; 139  : 	t->rax = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+40], 0

; 140  : 	t->rbx = 10;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+48], 10

; 141  : 	t->rcx = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+56], 0

; 142  : 	t->rdx = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+64], 0

; 143  : 	t->rsi = 10;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+72], 10

; 144  : 	t->rdi = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+80], 0

; 145  : 	t->rbp = (uint64_t)t->rsp;

	mov	rax, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR [rcx+8]
	mov	QWORD PTR [rax+88], rcx

; 146  : 	t->r8 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+96], 0

; 147  : 	t->r9 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+104], 0

; 148  : 	t->r10 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+112], 0

; 149  : 	t->r11 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+120], 0

; 150  : 	t->r12 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+128], 0

; 151  : 	t->r13 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+136], 0

; 152  : 	t->r14 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+144], 0

; 153  : 	t->r15 = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+152], 0

; 154  : 	t->kern_esp = (uint64_t)allocate_kstack((uint64_t*)cr3);

	mov	rcx, QWORD PTR cr3$[rsp]
	call	?allocate_kstack@@YA_KPEA_K@Z		; allocate_kstack
	mov	rcx, QWORD PTR t$[rsp]
	mov	QWORD PTR [rcx+200], rax

; 155  : 	t->ds = 0x23;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+160], 35			; 00000023H

; 156  : 	t->es = 0x23;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+168], 35			; 00000023H

; 157  : 	t->fs = 0x23;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+176], 35			; 00000023H

; 158  : 	t->gs = 0x23;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+184], 35			; 00000023H

; 159  : 	t->cr3 = cr3;

	mov	rax, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR cr3$[rsp]
	mov	QWORD PTR [rax+192], rcx

; 160  : 	t->name = name;

	mov	rax, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR name$[rsp]
	mov	QWORD PTR [rax+216], rcx

; 161  : 	t->id = task_id++;

	mov	rax, QWORD PTR t$[rsp]
	movzx	ecx, WORD PTR ?task_id@@3GA		; task_id
	mov	WORD PTR [rax+226], cx
	movzx	eax, WORD PTR ?task_id@@3GA		; task_id
	inc	ax
	mov	WORD PTR ?task_id@@3GA, ax		; task_id

; 162  : 	t->quanta = 0;

	xor	eax, eax
	mov	rcx, QWORD PTR t$[rsp]
	mov	WORD PTR [rcx+230], ax

; 163  : 	t->blocked_stack_resv = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	QWORD PTR [rax+232], 0

; 164  : 	t->mouse_box = (uint64_t*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	rcx, QWORD PTR t$[rsp]
	mov	QWORD PTR [rcx+240], rax

; 165  : 	map_page_ex((uint64_t*)t->cr3,(uint64_t)t->mouse_box,(uint64_t)0xFFFFFFFFB0000000);

	mov	r8, -1342177280				; ffffffffb0000000H
	mov	rax, QWORD PTR t$[rsp]
	mov	rdx, QWORD PTR [rax+240]
	mov	rax, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR [rax+192]
	call	?map_page_ex@@YA_NPEA_K_K1@Z		; map_page_ex

; 166  : 	t->_is_user = 1;

	mov	rax, QWORD PTR t$[rsp]
	mov	BYTE PTR [rax+208], 1

; 167  : 	t->priviledge = THREAD_LEVEL_USER;

	mov	rax, QWORD PTR t$[rsp]
	mov	BYTE PTR [rax+228], 2

; 168  : 	t->state = THREAD_STATE_READY;

	mov	rax, QWORD PTR t$[rsp]
	mov	BYTE PTR [rax+224], 1

; 169  : 	t->priority = priority;

	mov	rax, QWORD PTR t$[rsp]
	movzx	ecx, BYTE PTR priority$[rsp]
	mov	BYTE PTR [rax+256], cl

; 170  : 	thread_insert (t);

	mov	rcx, QWORD PTR t$[rsp]
	call	?thread_insert@@YAXPEAU_thread_@@@Z	; thread_insert

; 171  : 	return t;

	mov	rax, QWORD PTR t$[rsp]

; 172  : }

	add	rsp, 56					; 00000038H
	ret	0
?create_user_thread@@YAPEAU_thread_@@P6AXPEAX@Z_K2QEADE@Z ENDP ; create_user_thread
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
?scheduler_start@@YAXXZ PROC				; scheduler_start

; 273  : void scheduler_start () {

$LN3:
	sub	rsp, 40					; 00000028H

; 274  : 	x64_cli();

	call	x64_cli

; 275  : #ifdef USE_APIC
; 276  : 	setvect(0x40, scheduler_isr);

	lea	rdx, OFFSET FLAT:?scheduler_isr@@YAX_KPEAX@Z ; scheduler_isr
	mov	ecx, 64					; 00000040H
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 277  : #endif
; 278  : #ifdef USE_PIC
; 279  : 	interrupt_set(0,scheduler_isr,0);
; 280  : #endif
; 281  : 	execute_idle(current_thread,get_kernel_tss());

	call	get_kernel_tss
	mov	rdx, rax
	mov	rcx, QWORD PTR current_thread
	call	execute_idle

; 282  : }

	add	rsp, 40					; 00000028H
	ret	0
?scheduler_start@@YAXXZ ENDP				; scheduler_start
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\thread.cpp
_TEXT	SEGMENT
tv70 = 48
idle_$ = 56
?initialize_scheduler@@YAXXZ PROC			; initialize_scheduler

; 185  : void initialize_scheduler () {

$LN3:
	sub	rsp, 72					; 00000048H

; 186  : 	blocked_list = initialize_list();

	call	?initialize_list@@YAPEAU_list_@@XZ	; initialize_list
	mov	QWORD PTR ?blocked_list@@3PEAU_list_@@EA, rax ; blocked_list

; 187  : 	block_mutex = create_mutex();

	call	?create_mutex@@YAPEAUmutex_t@@XZ	; create_mutex
	mov	QWORD PTR ?block_mutex@@3PEAUmutex_t@@EA, rax ; block_mutex

; 188  : 	scheduler_mutex = create_mutex ();

	call	?create_mutex@@YAPEAUmutex_t@@XZ	; create_mutex
	mov	QWORD PTR ?scheduler_mutex@@3PEAUmutex_t@@EA, rax ; scheduler_mutex

; 189  : 	scheduler_enable = true;

	mov	BYTE PTR ?scheduler_enable@@3_NA, 1	; scheduler_enable

; 190  : 	scheduler_initialized = true;

	mov	BYTE PTR ?scheduler_initialized@@3_NA, 1 ; scheduler_initialized

; 191  : 	thread_t *idle_ = create_kthread (idle_thread,(uint64_t)pmmngr_alloc(),x64_read_cr3(),"Idle",1);

	call	x64_read_cr3
	mov	QWORD PTR tv70[rsp], rax
	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	BYTE PTR [rsp+32], 1
	lea	r9, OFFSET FLAT:$SG3300
	mov	rcx, QWORD PTR tv70[rsp]
	mov	r8, rcx
	mov	rdx, rax
	lea	rcx, OFFSET FLAT:?idle_thread@@YAXXZ	; idle_thread
	call	?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z ; create_kthread
	mov	QWORD PTR idle_$[rsp], rax

; 192  : 	current_thread = idle_;

	mov	rax, QWORD PTR idle_$[rsp]
	mov	QWORD PTR current_thread, rax

; 193  : }

	add	rsp, 72					; 00000048H
	ret	0
?initialize_scheduler@@YAXXZ ENDP			; initialize_scheduler
_TEXT	ENDS
END
