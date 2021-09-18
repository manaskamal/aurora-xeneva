; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?initialize_list@@YAPEAU_list_@@XZ		; initialize_list
PUBLIC	?list_add@@YAXPEAU_list_@@PEAX@Z		; list_add
PUBLIC	?list_remove@@YAPEAXPEAU_list_@@I@Z		; list_remove
PUBLIC	?list_get_at@@YAPEAXPEAU_list_@@I@Z		; list_get_at
EXTRN	?malloc@@YAPEAXI@Z:PROC				; malloc
EXTRN	?mfree@@YAXPEAX@Z:PROC				; mfree
pdata	SEGMENT
$pdata$?initialize_list@@YAPEAU_list_@@XZ DD imagerel $LN3
	DD	imagerel $LN3+53
	DD	imagerel $unwind$?initialize_list@@YAPEAU_list_@@XZ
$pdata$?list_add@@YAXPEAU_list_@@PEAX@Z DD imagerel $LN7
	DD	imagerel $LN7+184
	DD	imagerel $unwind$?list_add@@YAXPEAU_list_@@PEAX@Z
$pdata$?list_remove@@YAPEAXPEAU_list_@@I@Z DD imagerel $LN12
	DD	imagerel $LN12+263
	DD	imagerel $unwind$?list_remove@@YAPEAXPEAU_list_@@I@Z
$pdata$?list_get_at@@YAPEAXPEAU_list_@@I@Z DD imagerel $LN10
	DD	imagerel $LN10+146
	DD	imagerel $unwind$?list_get_at@@YAPEAXPEAU_list_@@I@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?initialize_list@@YAPEAU_list_@@XZ DD 010401H
	DD	06204H
$unwind$?list_add@@YAXPEAU_list_@@PEAX@Z DD 010e01H
	DD	0620eH
$unwind$?list_remove@@YAPEAXPEAU_list_@@I@Z DD 010d01H
	DD	0820dH
$unwind$?list_get_at@@YAPEAXPEAU_list_@@I@Z DD 010d01H
	DD	0420dH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\lnklist.cpp
_TEXT	SEGMENT
current_index$1 = 0
current_node$ = 8
tv75 = 16
list$ = 48
index$ = 56
?list_get_at@@YAPEAXPEAU_list_@@I@Z PROC		; list_get_at

; 45   : void * list_get_at(list_t* list, unsigned int index) {

$LN10:
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 46   : 
; 47   : 	if (list->pointer == 0 || index >= list->pointer)

	mov	rax, QWORD PTR list$[rsp]
	cmp	DWORD PTR [rax], 0
	je	SHORT $LN4@list_get_a
	mov	rax, QWORD PTR list$[rsp]
	mov	eax, DWORD PTR [rax]
	cmp	DWORD PTR index$[rsp], eax
	jb	SHORT $LN5@list_get_a
$LN4@list_get_a:

; 48   : 		return nullptr;

	xor	eax, eax
	jmp	SHORT $LN6@list_get_a
$LN5@list_get_a:

; 49   : 
; 50   : 	dataentry * current_node = list->entry_current;

	mov	rax, QWORD PTR list$[rsp]
	mov	rax, QWORD PTR [rax+8]
	mov	QWORD PTR current_node$[rsp], rax

; 51   : 	
; 52   : 	for (unsigned int current_index = 0; (current_index < index) && current_node; current_index++)

	mov	DWORD PTR current_index$1[rsp], 0
	jmp	SHORT $LN3@list_get_a
$LN2@list_get_a:
	mov	eax, DWORD PTR current_index$1[rsp]
	inc	eax
	mov	DWORD PTR current_index$1[rsp], eax
$LN3@list_get_a:
	mov	eax, DWORD PTR index$[rsp]
	cmp	DWORD PTR current_index$1[rsp], eax
	jae	SHORT $LN1@list_get_a
	cmp	QWORD PTR current_node$[rsp], 0
	je	SHORT $LN1@list_get_a

; 53   : 		current_node = current_node->next;

	mov	rax, QWORD PTR current_node$[rsp]
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR current_node$[rsp], rax
	jmp	SHORT $LN2@list_get_a
$LN1@list_get_a:

; 54   : 
; 55   : 	return current_node ? current_node->data : nullptr;

	cmp	QWORD PTR current_node$[rsp], 0
	je	SHORT $LN8@list_get_a
	mov	rax, QWORD PTR current_node$[rsp]
	mov	rax, QWORD PTR [rax+16]
	mov	QWORD PTR tv75[rsp], rax
	jmp	SHORT $LN9@list_get_a
$LN8@list_get_a:
	mov	QWORD PTR tv75[rsp], 0
$LN9@list_get_a:
	mov	rax, QWORD PTR tv75[rsp]
$LN6@list_get_a:

; 56   : }

	add	rsp, 40					; 00000028H
	ret	0
?list_get_at@@YAPEAXPEAU_list_@@I@Z ENDP		; list_get_at
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\lnklist.cpp
_TEXT	SEGMENT
current_index$1 = 32
current_node$ = 40
payload$ = 48
list$ = 80
index$ = 88
?list_remove@@YAPEAXPEAU_list_@@I@Z PROC		; list_remove

; 58   : void* list_remove(list_t* list, unsigned int index) {

$LN12:
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 59   : 
; 60   : 	void* payload;
; 61   : 
; 62   : 	if (list->pointer == 0 || index >= list->pointer)

	mov	rax, QWORD PTR list$[rsp]
	cmp	DWORD PTR [rax], 0
	je	SHORT $LN8@list_remov
	mov	rax, QWORD PTR list$[rsp]
	mov	eax, DWORD PTR [rax]
	cmp	DWORD PTR index$[rsp], eax
	jb	SHORT $LN9@list_remov
$LN8@list_remov:

; 63   : 		return nullptr;

	xor	eax, eax
	jmp	$LN10@list_remov
$LN9@list_remov:

; 64   : 
; 65   : 	dataentry* current_node = list->entry_current;

	mov	rax, QWORD PTR list$[rsp]
	mov	rax, QWORD PTR [rax+8]
	mov	QWORD PTR current_node$[rsp], rax

; 66   : 
; 67   : 	for (unsigned int current_index = 0; (current_index < index) && current_node; current_index++)

	mov	DWORD PTR current_index$1[rsp], 0
	jmp	SHORT $LN7@list_remov
$LN6@list_remov:
	mov	eax, DWORD PTR current_index$1[rsp]
	inc	eax
	mov	DWORD PTR current_index$1[rsp], eax
$LN7@list_remov:
	mov	eax, DWORD PTR index$[rsp]
	cmp	DWORD PTR current_index$1[rsp], eax
	jae	SHORT $LN5@list_remov
	cmp	QWORD PTR current_node$[rsp], 0
	je	SHORT $LN5@list_remov

; 68   : 		current_node = current_node->next;

	mov	rax, QWORD PTR current_node$[rsp]
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR current_node$[rsp], rax
	jmp	SHORT $LN6@list_remov
$LN5@list_remov:

; 69   : 
; 70   : 	if (!current_node)

	cmp	QWORD PTR current_node$[rsp], 0
	jne	SHORT $LN4@list_remov

; 71   : 		return nullptr;

	xor	eax, eax
	jmp	$LN10@list_remov
$LN4@list_remov:

; 72   : 	payload = current_node->data;

	mov	rax, QWORD PTR current_node$[rsp]
	mov	rax, QWORD PTR [rax+16]
	mov	QWORD PTR payload$[rsp], rax

; 73   : 
; 74   : 	if (current_node->prev)

	mov	rax, QWORD PTR current_node$[rsp]
	cmp	QWORD PTR [rax+8], 0
	je	SHORT $LN3@list_remov

; 75   : 		current_node->prev->next = current_node->next;

	mov	rax, QWORD PTR current_node$[rsp]
	mov	rax, QWORD PTR [rax+8]
	mov	rcx, QWORD PTR current_node$[rsp]
	mov	rcx, QWORD PTR [rcx]
	mov	QWORD PTR [rax], rcx
$LN3@list_remov:

; 76   : 
; 77   : 	if (current_node->next)

	mov	rax, QWORD PTR current_node$[rsp]
	cmp	QWORD PTR [rax], 0
	je	SHORT $LN2@list_remov

; 78   : 		current_node->next->prev = current_node->prev;

	mov	rax, QWORD PTR current_node$[rsp]
	mov	rax, QWORD PTR [rax]
	mov	rcx, QWORD PTR current_node$[rsp]
	mov	rcx, QWORD PTR [rcx+8]
	mov	QWORD PTR [rax+8], rcx
$LN2@list_remov:

; 79   : 
; 80   : 	if (index == 0)

	cmp	DWORD PTR index$[rsp], 0
	jne	SHORT $LN1@list_remov

; 81   : 		list->entry_current = current_node->next;

	mov	rax, QWORD PTR list$[rsp]
	mov	rcx, QWORD PTR current_node$[rsp]
	mov	rcx, QWORD PTR [rcx]
	mov	QWORD PTR [rax+8], rcx
$LN1@list_remov:

; 82   : 
; 83   : 	mfree(current_node);

	mov	rcx, QWORD PTR current_node$[rsp]
	call	?mfree@@YAXPEAX@Z			; mfree

; 84   : 
; 85   : 	list->pointer--;

	mov	rax, QWORD PTR list$[rsp]
	mov	eax, DWORD PTR [rax]
	dec	eax
	mov	rcx, QWORD PTR list$[rsp]
	mov	DWORD PTR [rcx], eax

; 86   : 
; 87   : 	return payload;

	mov	rax, QWORD PTR payload$[rsp]
$LN10@list_remov:

; 88   : }

	add	rsp, 72					; 00000048H
	ret	0
?list_remove@@YAPEAXPEAU_list_@@I@Z ENDP		; list_remove
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\lnklist.cpp
_TEXT	SEGMENT
current_data$ = 32
current_entry$1 = 40
list$ = 64
data$ = 72
?list_add@@YAXPEAU_list_@@PEAX@Z PROC			; list_add

; 24   : void list_add(list_t* list, void* data) {

$LN7:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 25   : 	dataentry *current_data = (dataentry*)malloc(sizeof(dataentry));

	mov	ecx, 24
	call	?malloc@@YAPEAXI@Z			; malloc
	mov	QWORD PTR current_data$[rsp], rax

; 26   : 	current_data->next = nullptr;

	mov	rax, QWORD PTR current_data$[rsp]
	mov	QWORD PTR [rax], 0

; 27   : 	current_data->prev = nullptr;

	mov	rax, QWORD PTR current_data$[rsp]
	mov	QWORD PTR [rax+8], 0

; 28   : 	current_data->data = data;

	mov	rax, QWORD PTR current_data$[rsp]
	mov	rcx, QWORD PTR data$[rsp]
	mov	QWORD PTR [rax+16], rcx

; 29   : 
; 30   : 
; 31   : 	if (!list->entry_current) {

	mov	rax, QWORD PTR list$[rsp]
	cmp	QWORD PTR [rax+8], 0
	jne	SHORT $LN4@list_add

; 32   : 		list->entry_current = current_data;

	mov	rax, QWORD PTR list$[rsp]
	mov	rcx, QWORD PTR current_data$[rsp]
	mov	QWORD PTR [rax+8], rcx

; 33   : 	}else {

	jmp	SHORT $LN3@list_add
$LN4@list_add:

; 34   : 		dataentry * current_entry = list->entry_current;

	mov	rax, QWORD PTR list$[rsp]
	mov	rax, QWORD PTR [rax+8]
	mov	QWORD PTR current_entry$1[rsp], rax
$LN2@list_add:

; 35   : 		while (current_entry->next) {

	mov	rax, QWORD PTR current_entry$1[rsp]
	cmp	QWORD PTR [rax], 0
	je	SHORT $LN1@list_add

; 36   : 			current_entry = current_entry->next;

	mov	rax, QWORD PTR current_entry$1[rsp]
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR current_entry$1[rsp], rax

; 37   : 		}

	jmp	SHORT $LN2@list_add
$LN1@list_add:

; 38   : 		current_entry->next = current_data;

	mov	rax, QWORD PTR current_entry$1[rsp]
	mov	rcx, QWORD PTR current_data$[rsp]
	mov	QWORD PTR [rax], rcx

; 39   : 		current_data->prev = current_entry;

	mov	rax, QWORD PTR current_data$[rsp]
	mov	rcx, QWORD PTR current_entry$1[rsp]
	mov	QWORD PTR [rax+8], rcx
$LN3@list_add:

; 40   : 	}
; 41   : 
; 42   : 	list->pointer++;

	mov	rax, QWORD PTR list$[rsp]
	mov	eax, DWORD PTR [rax]
	inc	eax
	mov	rcx, QWORD PTR list$[rsp]
	mov	DWORD PTR [rcx], eax

; 43   : }

	add	rsp, 56					; 00000038H
	ret	0
?list_add@@YAXPEAU_list_@@PEAX@Z ENDP			; list_add
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\utils\lnklist.cpp
_TEXT	SEGMENT
list$ = 32
?initialize_list@@YAPEAU_list_@@XZ PROC			; initialize_list

; 16   : list_t* initialize_list() {

$LN3:
	sub	rsp, 56					; 00000038H

; 17   : 	list_t *list = (list_t*)malloc(4096);

	mov	ecx, 4096				; 00001000H
	call	?malloc@@YAPEAXI@Z			; malloc
	mov	QWORD PTR list$[rsp], rax

; 18   : 	list->entry_current = nullptr;

	mov	rax, QWORD PTR list$[rsp]
	mov	QWORD PTR [rax+8], 0

; 19   : 	list->pointer = 0;

	mov	rax, QWORD PTR list$[rsp]
	mov	DWORD PTR [rax], 0

; 20   : 	return list;

	mov	rax, QWORD PTR list$[rsp]

; 21   : }

	add	rsp, 56					; 00000038H
	ret	0
?initialize_list@@YAPEAU_list_@@XZ ENDP			; initialize_list
_TEXT	ENDS
END
