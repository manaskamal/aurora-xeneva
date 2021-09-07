; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3067	DB	'Address already present', 0aH, 00H
CONST	ENDS
PUBLIC	?pml4_index@@YA_K_K@Z				; pml4_index
PUBLIC	?pdp_index@@YA_K_K@Z				; pdp_index
PUBLIC	?pd_index@@YA_K_K@Z				; pd_index
PUBLIC	?pt_index@@YA_K_K@Z				; pt_index
PUBLIC	?p_index@@YA_K_K@Z				; p_index
PUBLIC	?vmmngr_x86_64_init@@YAXXZ			; vmmngr_x86_64_init
PUBLIC	?map_page@@YA_N_K0@Z				; map_page
PUBLIC	?map_page_ex@@YA_NPEA_K_K1@Z			; map_page_ex
PUBLIC	?create_user_address_space@@YAPEA_KXZ		; create_user_address_space
PUBLIC	?unmap_page@@YAX_K@Z				; unmap_page
PUBLIC	?get_physical_address@@YAPEA_K_K@Z		; get_physical_address
PUBLIC	?get_free_page@@YAPEA_K_K_N@Z			; get_free_page
PUBLIC	?vmmngr_update_flags@@YA_N_K0@Z			; vmmngr_update_flags
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?pmmngr_free@@YAXPEAX@Z:PROC			; pmmngr_free
EXTRN	x64_mfence:PROC
EXTRN	x64_read_cr3:PROC
EXTRN	x64_write_cr3:PROC
EXTRN	flush_tlb:PROC
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?get_screen_width@@YAIXZ:PROC			; get_screen_width
EXTRN	?get_screen_height@@YAIXZ:PROC			; get_screen_height
pdata	SEGMENT
$pdata$?vmmngr_x86_64_init@@YAXXZ DD imagerel $LN7
	DD	imagerel $LN7+123
	DD	imagerel $unwind$?vmmngr_x86_64_init@@YAXXZ
$pdata$?map_page@@YA_N_K0@Z DD imagerel $LN6
	DD	imagerel $LN6+524
	DD	imagerel $unwind$?map_page@@YA_N_K0@Z
$pdata$?map_page_ex@@YA_NPEA_K_K1@Z DD imagerel $LN7
	DD	imagerel $LN7+549
	DD	imagerel $unwind$?map_page_ex@@YA_NPEA_K_K1@Z
$pdata$?create_user_address_space@@YAPEA_KXZ DD imagerel $LN15
	DD	imagerel $LN15+694
	DD	imagerel $unwind$?create_user_address_space@@YAPEA_KXZ
$pdata$?unmap_page@@YAX_K@Z DD imagerel $LN4
	DD	imagerel $LN4+219
	DD	imagerel $unwind$?unmap_page@@YAX_K@Z
$pdata$?get_physical_address@@YAPEA_K_K@Z DD imagerel $LN4
	DD	imagerel $LN4+171
	DD	imagerel $unwind$?get_physical_address@@YAPEA_K_K@Z
$pdata$?get_free_page@@YAPEA_K_K_N@Z DD imagerel $LN9
	DD	imagerel $LN9+316
	DD	imagerel $unwind$?get_free_page@@YAPEA_K_K_N@Z
$pdata$?vmmngr_update_flags@@YA_N_K0@Z DD imagerel $LN7
	DD	imagerel $LN7+574
	DD	imagerel $unwind$?vmmngr_update_flags@@YA_N_K0@Z
$pdata$?clear@@YAXPEAX@Z DD imagerel ?clear@@YAXPEAX@Z
	DD	imagerel ?clear@@YAXPEAX@Z+74
	DD	imagerel $unwind$?clear@@YAXPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?vmmngr_x86_64_init@@YAXXZ DD 010401H
	DD	08204H
$unwind$?map_page@@YA_N_K0@Z DD 021101H
	DD	0110111H
$unwind$?map_page_ex@@YA_NPEA_K_K1@Z DD 011301H
	DD	0e213H
$unwind$?create_user_address_space@@YAPEA_KXZ DD 010401H
	DD	0e204H
$unwind$?unmap_page@@YAX_K@Z DD 010901H
	DD	0c209H
$unwind$?get_physical_address@@YAPEA_K_K@Z DD 010901H
	DD	0a209H
$unwind$?get_free_page@@YAPEA_K_K_N@Z DD 010d01H
	DD	0e20dH
$unwind$?vmmngr_update_flags@@YA_N_K0@Z DD 021101H
	DD	0110111H
$unwind$?clear@@YAXPEAX@Z DD 010901H
	DD	02209H
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\vmmngr.cpp
_TEXT	SEGMENT
n$1 = 0
t$ = 8
addr$ = 32
?clear@@YAXPEAX@Z PROC					; clear

; 52   : static void clear(void* addr){

	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 53   : 	uint64_t* t = (uint64_t*)addr;

	mov	rax, QWORD PTR addr$[rsp]
	mov	QWORD PTR t$[rsp], rax

; 54   : 	for (size_t n = 0; n < 4096 / sizeof(uint64_t); ++n){

	mov	QWORD PTR n$1[rsp], 0
	jmp	SHORT $LN3@clear
$LN2@clear:
	mov	rax, QWORD PTR n$1[rsp]
	inc	rax
	mov	QWORD PTR n$1[rsp], rax
$LN3@clear:
	cmp	QWORD PTR n$1[rsp], 512			; 00000200H
	jae	SHORT $LN1@clear

; 55   : 		t[n] = 0;

	mov	rax, QWORD PTR t$[rsp]
	mov	rcx, QWORD PTR n$1[rsp]
	mov	QWORD PTR [rax+rcx*8], 0

; 56   : 	}

	jmp	SHORT $LN2@clear
$LN1@clear:

; 57   : }

	add	rsp, 24
	ret	0
?clear@@YAXPEAX@Z ENDP					; clear
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\vmmngr.cpp
_TEXT	SEGMENT
i2$ = 32
i4$ = 36
i3$ = 40
i1$ = 44
flags$ = 48
pml4i$ = 56
page$1 = 64
page$2 = 72
pml2$ = 80
pml3$ = 88
page$3 = 96
pml1$ = 104
phys_addr$ = 112
virtual_address$ = 144
flags_$ = 152
?vmmngr_update_flags@@YA_N_K0@Z PROC			; vmmngr_update_flags

; 130  : bool vmmngr_update_flags (uint64_t virtual_address, size_t flags_){

$LN7:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 136				; 00000088H

; 131  : 
; 132  : 	uint64_t phys_addr = (uint64_t)get_physical_address (virtual_address);

	mov	rcx, QWORD PTR virtual_address$[rsp]
	call	?get_physical_address@@YAPEA_K_K@Z	; get_physical_address
	mov	QWORD PTR phys_addr$[rsp], rax

; 133  : 
; 134  : 	size_t flags = PAGING_WRITABLE | PAGING_PRESENT | PAGING_USER;

	mov	QWORD PTR flags$[rsp], 7

; 135  : 
; 136  : 	const long i4 = (virtual_address >> 39) & 0x1FF;

	mov	rax, QWORD PTR virtual_address$[rsp]
	shr	rax, 39					; 00000027H
	and	rax, 511				; 000001ffH
	mov	DWORD PTR i4$[rsp], eax

; 137  : 	const long i3 = (virtual_address >> 30) & 0x1FF;

	mov	rax, QWORD PTR virtual_address$[rsp]
	shr	rax, 30
	and	rax, 511				; 000001ffH
	mov	DWORD PTR i3$[rsp], eax

; 138  : 	const long i2 = (virtual_address >> 21) & 0x1FF;

	mov	rax, QWORD PTR virtual_address$[rsp]
	shr	rax, 21
	and	rax, 511				; 000001ffH
	mov	DWORD PTR i2$[rsp], eax

; 139  : 	const long i1 = (virtual_address >> 12) & 0x1FF;

	mov	rax, QWORD PTR virtual_address$[rsp]
	shr	rax, 12
	and	rax, 511				; 000001ffH
	mov	DWORD PTR i1$[rsp], eax

; 140  : 
; 141  : 	uint64_t *pml4i = (uint64_t*)x64_read_cr3();

	call	x64_read_cr3
	mov	QWORD PTR pml4i$[rsp], rax

; 142  : 	if (!(pml4i[i4] & PAGING_PRESENT))

	movsxd	rax, DWORD PTR i4$[rsp]
	mov	rcx, QWORD PTR pml4i$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, 1
	test	rax, rax
	jne	SHORT $LN4@vmmngr_upd

; 143  : 	{
; 144  : 		const uint64_t page = (uint64_t)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR page$2[rsp], rax

; 145  : 		pml4i[i4] = page | flags;

	mov	rax, QWORD PTR flags$[rsp]
	mov	rcx, QWORD PTR page$2[rsp]
	or	rcx, rax
	mov	rax, rcx
	movsxd	rcx, DWORD PTR i4$[rsp]
	mov	rdx, QWORD PTR pml4i$[rsp]
	mov	QWORD PTR [rdx+rcx*8], rax

; 146  : 		clear((void*)page);

	mov	rcx, QWORD PTR page$2[rsp]
	call	?clear@@YAXPEAX@Z			; clear

; 147  : 		flush_tlb((void*)page);

	mov	rcx, QWORD PTR page$2[rsp]
	call	flush_tlb

; 148  : 		x64_mfence();

	call	x64_mfence
$LN4@vmmngr_upd:

; 149  : 	}
; 150  : 	uint64_t* pml3 = (uint64_t*)(pml4i[i4] & ~(4096 - 1));

	movsxd	rax, DWORD PTR i4$[rsp]
	mov	rcx, QWORD PTR pml4i$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pml3$[rsp], rax

; 151  : 	if (!(pml3[i3] & PAGING_PRESENT))

	movsxd	rax, DWORD PTR i3$[rsp]
	mov	rcx, QWORD PTR pml3$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, 1
	test	rax, rax
	jne	SHORT $LN3@vmmngr_upd

; 152  : 	{
; 153  : 		const uint64_t page = (uint64_t)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR page$3[rsp], rax

; 154  : 		pml3[i3] = page | flags;

	mov	rax, QWORD PTR flags$[rsp]
	mov	rcx, QWORD PTR page$3[rsp]
	or	rcx, rax
	mov	rax, rcx
	movsxd	rcx, DWORD PTR i3$[rsp]
	mov	rdx, QWORD PTR pml3$[rsp]
	mov	QWORD PTR [rdx+rcx*8], rax

; 155  : 		clear((void*)page);

	mov	rcx, QWORD PTR page$3[rsp]
	call	?clear@@YAXPEAX@Z			; clear

; 156  : 		flush_tlb((void*)page);

	mov	rcx, QWORD PTR page$3[rsp]
	call	flush_tlb

; 157  : 		x64_mfence();

	call	x64_mfence
$LN3@vmmngr_upd:

; 158  : 		
; 159  : 	}
; 160  : 
; 161  : 	uint64_t* pml2 = (uint64_t*)(pml3[i3] & ~(4096 - 1));

	movsxd	rax, DWORD PTR i3$[rsp]
	mov	rcx, QWORD PTR pml3$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pml2$[rsp], rax

; 162  : 	if (!(pml2[i2] & PAGING_PRESENT))

	movsxd	rax, DWORD PTR i2$[rsp]
	mov	rcx, QWORD PTR pml2$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, 1
	test	rax, rax
	jne	SHORT $LN2@vmmngr_upd

; 163  : 	{
; 164  : 		const uint64_t page = (uint64_t)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR page$1[rsp], rax

; 165  : 		pml2[i2] = page | flags;

	mov	rax, QWORD PTR flags$[rsp]
	mov	rcx, QWORD PTR page$1[rsp]
	or	rcx, rax
	mov	rax, rcx
	movsxd	rcx, DWORD PTR i2$[rsp]
	mov	rdx, QWORD PTR pml2$[rsp]
	mov	QWORD PTR [rdx+rcx*8], rax

; 166  : 		clear((void*)page);

	mov	rcx, QWORD PTR page$1[rsp]
	call	?clear@@YAXPEAX@Z			; clear

; 167  : 		flush_tlb((void*)page);

	mov	rcx, QWORD PTR page$1[rsp]
	call	flush_tlb

; 168  : 		x64_mfence();

	call	x64_mfence
$LN2@vmmngr_upd:

; 169  : 		
; 170  : 	}
; 171  : 	uint64_t* pml1 = (uint64_t*)(pml2[i2] & ~(4096 - 1));

	movsxd	rax, DWORD PTR i2$[rsp]
	mov	rcx, QWORD PTR pml2$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pml1$[rsp], rax

; 172  : 	if (pml1[i1] & PAGING_PRESENT)

	movsxd	rax, DWORD PTR i1$[rsp]
	mov	rcx, QWORD PTR pml1$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, 1
	test	rax, rax
	je	SHORT $LN1@vmmngr_upd

; 173  : 	{
; 174  : 		printf ("Address already present\n");

	lea	rcx, OFFSET FLAT:$SG3067
	call	?printf@@YAXPEBDZZ			; printf
$LN1@vmmngr_upd:

; 175  : 	}
; 176  : 
; 177  : 	pml1[i1] = phys_addr | flags;

	mov	rax, QWORD PTR flags$[rsp]
	mov	rcx, QWORD PTR phys_addr$[rsp]
	or	rcx, rax
	mov	rax, rcx
	movsxd	rcx, DWORD PTR i1$[rsp]
	mov	rdx, QWORD PTR pml1$[rsp]
	mov	QWORD PTR [rdx+rcx*8], rax

; 178  : 	flush_tlb ((void*)virtual_address);

	mov	rcx, QWORD PTR virtual_address$[rsp]
	call	flush_tlb

; 179  : 	x64_mfence ();

	call	x64_mfence

; 180  : 	return true;

	mov	al, 1

; 181  : }

	add	rsp, 136				; 00000088H
	ret	0
?vmmngr_update_flags@@YA_N_K0@Z ENDP			; vmmngr_update_flags
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\vmmngr.cpp
_TEXT	SEGMENT
start$ = 32
i$1 = 40
pt$2 = 48
pdpt$3 = 56
pml4$ = 64
pd$4 = 72
page$ = 80
end$ = 88
page$5 = 96
s$ = 128
user$ = 136
?get_free_page@@YAPEA_K_K_N@Z PROC			; get_free_page

; 313  : uint64_t* get_free_page (size_t s, bool user) {

$LN9:
	mov	BYTE PTR [rsp+16], dl
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 120				; 00000078H

; 314  : 	uint64_t* page = 0;

	mov	QWORD PTR page$[rsp], 0

; 315  : 	uint64_t start = 0;

	mov	QWORD PTR start$[rsp], 0

; 316  : 	if (user)

	movzx	eax, BYTE PTR user$[rsp]
	test	eax, eax
	je	SHORT $LN6@get_free_p

; 317  : 		start = USER_BASE_ADDRESS;

	mov	rax, 70368744177664			; 0000400000000000H
	mov	QWORD PTR start$[rsp], rax

; 318  : 	else

	jmp	SHORT $LN5@get_free_p
$LN6@get_free_p:

; 319  : 		start = KERNEL_BASE_ADDRESS;

	mov	rax, -35184372088832			; ffffe00000000000H
	mov	QWORD PTR start$[rsp], rax
$LN5@get_free_p:

; 320  : 
; 321  : 	uint64_t* end = 0;

	mov	QWORD PTR end$[rsp], 0

; 322  : 	uint64_t *pml4 = (uint64_t*)x64_read_cr3();

	call	x64_read_cr3
	mov	QWORD PTR pml4$[rsp], rax

; 323  : 	for (int i = 0; i < s; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN4@get_free_p
$LN3@get_free_p:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN4@get_free_p:
	movsxd	rax, DWORD PTR i$1[rsp]
	cmp	rax, QWORD PTR s$[rsp]
	jae	$LN2@get_free_p

; 324  : 		uint64_t *pdpt = (uint64_t*)(pml4[pml4_index(start)] & ~(4096 - 1));

	mov	rcx, QWORD PTR start$[rsp]
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	rcx, QWORD PTR pml4$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pdpt$3[rsp], rax

; 325  : 	    uint64_t *pd = (uint64_t*)(pdpt[pdp_index(start)] & ~(4096 - 1));

	mov	rcx, QWORD PTR start$[rsp]
	call	?pdp_index@@YA_K_K@Z			; pdp_index
	mov	rcx, QWORD PTR pdpt$3[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pd$4[rsp], rax

; 326  : 		uint64_t *pt = (uint64_t*)(pd[pd_index(start)] & ~(4096 - 1));

	mov	rcx, QWORD PTR start$[rsp]
	call	?pd_index@@YA_K_K@Z			; pd_index
	mov	rcx, QWORD PTR pd$4[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pt$2[rsp], rax

; 327  : 		uint64_t *page = (uint64_t*)(pt[pt_index(start)] & ~(4096 - 1));

	mov	rcx, QWORD PTR start$[rsp]
	call	?pt_index@@YA_K_K@Z			; pt_index
	mov	rcx, QWORD PTR pt$2[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR page$5[rsp], rax

; 328  : 
; 329  : 		if ((pt[pt_index(start)] & PAGING_PRESENT) == 0){

	mov	rcx, QWORD PTR start$[rsp]
	call	?pt_index@@YA_K_K@Z			; pt_index
	mov	rcx, QWORD PTR pt$2[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, 1
	test	rax, rax
	jne	SHORT $LN1@get_free_p

; 330  : 			return (uint64_t*)start;

	mov	rax, QWORD PTR start$[rsp]
	jmp	SHORT $LN7@get_free_p
$LN1@get_free_p:

; 331  : 		}
; 332  : 		start+= 4096;

	mov	rax, QWORD PTR start$[rsp]
	add	rax, 4096				; 00001000H
	mov	QWORD PTR start$[rsp], rax

; 333  : 	}

	jmp	$LN3@get_free_p
$LN2@get_free_p:

; 334  : 	return 0;

	xor	eax, eax
$LN7@get_free_p:

; 335  : }

	add	rsp, 120				; 00000078H
	ret	0
?get_free_page@@YAPEA_K_K_N@Z ENDP			; get_free_page
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\vmmngr.cpp
_TEXT	SEGMENT
i1$ = 32
page$ = 40
pml4$ = 48
pdpt$ = 56
pd$ = 64
pt$ = 72
virt_addr$ = 96
?get_physical_address@@YAPEA_K_K@Z PROC			; get_physical_address

; 203  : uint64_t* get_physical_address (uint64_t virt_addr) {

$LN4:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 88					; 00000058H

; 204  : 	const long i1 = pml4_index(virt_addr);

	mov	rcx, QWORD PTR virt_addr$[rsp]
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	DWORD PTR i1$[rsp], eax

; 205  : 
; 206  : 	uint64_t *pml4 = (uint64_t*)x64_read_cr3();

	call	x64_read_cr3
	mov	QWORD PTR pml4$[rsp], rax

; 207  : 	uint64_t *pdpt = (uint64_t*)(pml4[pml4_index(virt_addr)] & ~(4096 - 1));

	mov	rcx, QWORD PTR virt_addr$[rsp]
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	rcx, QWORD PTR pml4$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pdpt$[rsp], rax

; 208  : 	uint64_t *pd = (uint64_t*)(pdpt[pdp_index(virt_addr)] & ~(4096 - 1));

	mov	rcx, QWORD PTR virt_addr$[rsp]
	call	?pdp_index@@YA_K_K@Z			; pdp_index
	mov	rcx, QWORD PTR pdpt$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pd$[rsp], rax

; 209  : 	uint64_t *pt = (uint64_t*)(pd[pd_index(virt_addr)] & ~(4096 - 1));

	mov	rcx, QWORD PTR virt_addr$[rsp]
	call	?pd_index@@YA_K_K@Z			; pd_index
	mov	rcx, QWORD PTR pd$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pt$[rsp], rax

; 210  : 	uint64_t *page = (uint64_t*)(pt[pt_index(virt_addr)] & ~(4096 - 1));

	mov	rcx, QWORD PTR virt_addr$[rsp]
	call	?pt_index@@YA_K_K@Z			; pt_index
	mov	rcx, QWORD PTR pt$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR page$[rsp], rax

; 211  : 
; 212  : 	if (page != NULL)

	cmp	QWORD PTR page$[rsp], 0
	je	SHORT $LN1@get_physic

; 213  : 		return page;

	mov	rax, QWORD PTR page$[rsp]
$LN1@get_physic:

; 214  : }

	add	rsp, 88					; 00000058H
	ret	0
?get_physical_address@@YAPEA_K_K@Z ENDP			; get_physical_address
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\vmmngr.cpp
_TEXT	SEGMENT
i1$ = 32
pml$ = 40
pml4$ = 48
pdpt$ = 56
pd$ = 64
pt$ = 72
page$ = 80
virt_addr$ = 112
?unmap_page@@YAX_K@Z PROC				; unmap_page

; 183  : void unmap_page(uint64_t virt_addr){

$LN4:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 104				; 00000068H

; 184  : 	
; 185  : 	const long i1 = pml4_index(virt_addr);

	mov	rcx, QWORD PTR virt_addr$[rsp]
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	DWORD PTR i1$[rsp], eax

; 186  : 
; 187  : 	uint64_t *pml4 = (uint64_t*)x64_read_cr3();

	call	x64_read_cr3
	mov	QWORD PTR pml4$[rsp], rax

; 188  : 	uint64_t *pdpt = (uint64_t*)(pml4[pml4_index(virt_addr)] & ~(4096 - 1));

	mov	rcx, QWORD PTR virt_addr$[rsp]
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	rcx, QWORD PTR pml4$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pdpt$[rsp], rax

; 189  : 	uint64_t *pd = (uint64_t*)(pdpt[pdp_index(virt_addr)] & ~(4096 - 1));

	mov	rcx, QWORD PTR virt_addr$[rsp]
	call	?pdp_index@@YA_K_K@Z			; pdp_index
	mov	rcx, QWORD PTR pdpt$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pd$[rsp], rax

; 190  : 	uint64_t *pt = (uint64_t*)(pd[pd_index(virt_addr)] & ~(4096 - 1));

	mov	rcx, QWORD PTR virt_addr$[rsp]
	call	?pd_index@@YA_K_K@Z			; pd_index
	mov	rcx, QWORD PTR pd$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pt$[rsp], rax

; 191  : 	uint64_t *page = (uint64_t*)(pt[pt_index(virt_addr)] & ~(4096 - 1));

	mov	rcx, QWORD PTR virt_addr$[rsp]
	call	?pt_index@@YA_K_K@Z			; pt_index
	mov	rcx, QWORD PTR pt$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR page$[rsp], rax

; 192  : 
; 193  : 	uint64_t *pml = (uint64_t*)x64_read_cr3();

	call	x64_read_cr3
	mov	QWORD PTR pml$[rsp], rax

; 194  : 	if (pml[i1] & PAGING_PRESENT){

	movsxd	rax, DWORD PTR i1$[rsp]
	mov	rcx, QWORD PTR pml$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, 1
	test	rax, rax
	je	SHORT $LN1@unmap_page

; 195  : 		pml[i1] = 0;

	movsxd	rax, DWORD PTR i1$[rsp]
	mov	rcx, QWORD PTR pml$[rsp]
	mov	QWORD PTR [rcx+rax*8], 0
$LN1@unmap_page:

; 196  : 	}
; 197  : 
; 198  : 	pmmngr_free(page);

	mov	rcx, QWORD PTR page$[rsp]
	call	?pmmngr_free@@YAXPEAX@Z			; pmmngr_free

; 199  : }

	add	rsp, 104				; 00000068H
	ret	0
?unmap_page@@YAX_K@Z ENDP				; unmap_page
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\vmmngr.cpp
_TEXT	SEGMENT
i$1 = 32
i$2 = 36
i$3 = 40
i$4 = 44
pml4_i$ = 48
old_pml4$ = 56
tv139 = 64
tv131 = 72
tv152 = 80
tv168 = 88
tv83 = 96
tv179 = 104
?create_user_address_space@@YAPEA_KXZ PROC		; create_user_address_space

; 274  : {

$LN15:
	sub	rsp, 120				; 00000078H

; 275  : 	
; 276  : 	uint64_t* pml4_i = (uint64_t*)pmmngr_alloc(); 

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR pml4_i$[rsp], rax

; 277  : 	uint64_t* old_pml4 = (uint64_t*)x64_read_cr3();

	call	x64_read_cr3
	mov	QWORD PTR old_pml4$[rsp], rax

; 278  : 
; 279  : 	//! copy the 0 and 1 entries from old address space to new one
; 280  : 	/*for (int i = 0; i < 512; i++) {
; 281  : 		if ((old_pml4[i] & 1) == 1)
; 282  : 			pml4_i[i] = old_pml4[i];
; 283  : 	}*/
; 284  : 
; 285  : 	pml4_i[0] = old_pml4[0];

	mov	eax, 8
	imul	rax, 0
	mov	ecx, 8
	imul	rcx, 0
	mov	rdx, QWORD PTR pml4_i$[rsp]
	mov	r8, QWORD PTR old_pml4$[rsp]
	mov	rax, QWORD PTR [r8+rax]
	mov	QWORD PTR [rdx+rcx], rax

; 286  : 	pml4_i[1] = old_pml4[1];

	mov	eax, 8
	imul	rax, 1
	mov	ecx, 8
	imul	rcx, 1
	mov	rdx, QWORD PTR pml4_i$[rsp]
	mov	r8, QWORD PTR old_pml4$[rsp]
	mov	rax, QWORD PTR [r8+rax]
	mov	QWORD PTR [rdx+rcx], rax

; 287  : 	//!**Copy the kernel stack to new address space
; 288  : 	for (int i=0; i < 0x200000/4096; i++)

	mov	DWORD PTR i$3[rsp], 0
	jmp	SHORT $LN12@create_use
$LN11@create_use:
	mov	eax, DWORD PTR i$3[rsp]
	inc	eax
	mov	DWORD PTR i$3[rsp], eax
$LN12@create_use:
	cmp	DWORD PTR i$3[rsp], 512			; 00000200H
	jge	SHORT $LN10@create_use

; 289  : 		pml4_i[pml4_index(0xFFFFA00000000000 + i *4096) ] = old_pml4[pml4_index(0xFFFFA00000000000 + i *4096) ];

	mov	eax, DWORD PTR i$3[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, 105553116266496			; 0000600000000000H
	sub	rax, rcx
	mov	rcx, rax
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	QWORD PTR tv83[rsp], rax
	mov	ecx, DWORD PTR i$3[rsp]
	imul	ecx, 4096				; 00001000H
	movsxd	rcx, ecx
	mov	rdx, 105553116266496			; 0000600000000000H
	sub	rcx, rdx
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	rcx, QWORD PTR pml4_i$[rsp]
	mov	rdx, QWORD PTR old_pml4$[rsp]
	mov	r8, QWORD PTR tv83[rsp]
	mov	rdx, QWORD PTR [rdx+r8*8]
	mov	QWORD PTR [rcx+rax*8], rdx
	jmp	SHORT $LN11@create_use
$LN10@create_use:

; 290  : 	
; 291  : 	//! copy the entire kernel to new address space {180kb kernel size}
; 292  : 	for (int i=0; i < 0x100000/4096; i++) 

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN9@create_use
$LN8@create_use:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN9@create_use:
	cmp	DWORD PTR i$1[rsp], 256			; 00000100H
	jge	SHORT $LN7@create_use

; 293  : 		pml4_i[pml4_index(0xFFFFC00000000000 + i*4096)] = old_pml4[pml4_index(0xFFFFC00000000000 + i*4096)];

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, 70368744177664			; 0000400000000000H
	sub	rax, rcx
	mov	rcx, rax
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	QWORD PTR tv131[rsp], rax
	mov	ecx, DWORD PTR i$1[rsp]
	imul	ecx, 4096				; 00001000H
	movsxd	rcx, ecx
	mov	rdx, 70368744177664			; 0000400000000000H
	sub	rcx, rdx
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	rcx, QWORD PTR pml4_i$[rsp]
	mov	rdx, QWORD PTR old_pml4$[rsp]
	mov	r8, QWORD PTR tv131[rsp]
	mov	rdx, QWORD PTR [rdx+r8*8]
	mov	QWORD PTR [rcx+rax*8], rdx
	jmp	SHORT $LN8@create_use
$LN7@create_use:

; 294  : 
; 295  : 	//
; 296  : 	for (int i=0; i < get_screen_width() * get_screen_height() * 32 / 4096; i++) 

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN6@create_use
$LN5@create_use:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN6@create_use:
	call	?get_screen_width@@YAIXZ		; get_screen_width
	mov	DWORD PTR tv139[rsp], eax
	call	?get_screen_height@@YAIXZ		; get_screen_height
	mov	ecx, DWORD PTR tv139[rsp]
	imul	ecx, eax
	mov	eax, ecx
	imul	eax, 32					; 00000020H
	xor	edx, edx
	mov	ecx, 4096				; 00001000H
	div	ecx
	cmp	DWORD PTR i$2[rsp], eax
	jae	SHORT $LN4@create_use

; 297  : 		pml4_i[pml4_index(0xFFFFF00000000000 + i * 4096)] = old_pml4[pml4_index(0xFFFFF00000000000 + i * 4096)];

	mov	eax, DWORD PTR i$2[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, 17592186044416			; 0000100000000000H
	sub	rax, rcx
	mov	rcx, rax
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	QWORD PTR tv152[rsp], rax
	mov	ecx, DWORD PTR i$2[rsp]
	imul	ecx, 4096				; 00001000H
	movsxd	rcx, ecx
	mov	rdx, 17592186044416			; 0000100000000000H
	sub	rcx, rdx
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	rcx, QWORD PTR pml4_i$[rsp]
	mov	rdx, QWORD PTR old_pml4$[rsp]
	mov	r8, QWORD PTR tv152[rsp]
	mov	rdx, QWORD PTR [rdx+r8*8]
	mov	QWORD PTR [rcx+rax*8], rdx
	jmp	$LN5@create_use
$LN4@create_use:

; 298  : 	
; 299  : 	////! copy the kernel heap area to new address space
; 300  : 	for (int i=0; i < 0x200000/4096; i++) 

	mov	DWORD PTR i$4[rsp], 0
	jmp	SHORT $LN3@create_use
$LN2@create_use:
	mov	eax, DWORD PTR i$4[rsp]
	inc	eax
	mov	DWORD PTR i$4[rsp], eax
$LN3@create_use:
	cmp	DWORD PTR i$4[rsp], 512			; 00000200H
	jge	SHORT $LN1@create_use

; 301  : 		pml4_i[pml4_index(0xFFFF800000000000 + i*4096)] = old_pml4[pml4_index(0xFFFF800000000000 + i*4096)];

	mov	eax, DWORD PTR i$4[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, 140737488355328			; 0000800000000000H
	sub	rax, rcx
	mov	rcx, rax
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	QWORD PTR tv168[rsp], rax
	mov	ecx, DWORD PTR i$4[rsp]
	imul	ecx, 4096				; 00001000H
	movsxd	rcx, ecx
	mov	rdx, 140737488355328			; 0000800000000000H
	sub	rcx, rdx
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	rcx, QWORD PTR pml4_i$[rsp]
	mov	rdx, QWORD PTR old_pml4$[rsp]
	mov	r8, QWORD PTR tv168[rsp]
	mov	rdx, QWORD PTR [rdx+r8*8]
	mov	QWORD PTR [rcx+rax*8], rdx
	jmp	SHORT $LN2@create_use
$LN1@create_use:

; 302  : 	
; 303  : 
; 304  : 
; 305  : 	pml4_i[pml4_index(0xFFFFD00000000000)] = old_pml4[pml4_index(0xFFFFD00000000000)];

	mov	rcx, -52776558133248			; ffffd00000000000H
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	QWORD PTR tv179[rsp], rax
	mov	rcx, -52776558133248			; ffffd00000000000H
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	rcx, QWORD PTR pml4_i$[rsp]
	mov	rdx, QWORD PTR old_pml4$[rsp]
	mov	r8, QWORD PTR tv179[rsp]
	mov	rdx, QWORD PTR [rdx+r8*8]
	mov	QWORD PTR [rcx+rax*8], rdx

; 306  : 	//! copy the user stack area to new address space
; 307  : 	//pml4_i[511] = *pml4_i | PAGING_PRESENT | PAGING_WRITABLE;
; 308  : 	//! return the new address space governor
; 309  : 	return pml4_i;

	mov	rax, QWORD PTR pml4_i$[rsp]

; 310  : }

	add	rsp, 120				; 00000078H
	ret	0
?create_user_address_space@@YAPEA_KXZ ENDP		; create_user_address_space
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\vmmngr.cpp
_TEXT	SEGMENT
i2$ = 32
i4$ = 36
i3$ = 40
i1$ = 44
flags$ = 48
page$1 = 56
page$2 = 64
page$3 = 72
pml2$ = 80
pml3$ = 88
pml1$ = 96
pml4i$ = 128
physical_address$ = 136
virtual_address$ = 144
?map_page_ex@@YA_NPEA_K_K1@Z PROC			; map_page_ex

; 218  : bool map_page_ex (uint64_t *pml4i,uint64_t physical_address, uint64_t virtual_address){

$LN7:
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 120				; 00000078H

; 219  : 
; 220  : 	size_t flags = PAGING_WRITABLE | PAGING_PRESENT | PAGING_USER;

	mov	QWORD PTR flags$[rsp], 7

; 221  : 
; 222  : 	const long i4 = (virtual_address >> 39) & 0x1FF;

	mov	rax, QWORD PTR virtual_address$[rsp]
	shr	rax, 39					; 00000027H
	and	rax, 511				; 000001ffH
	mov	DWORD PTR i4$[rsp], eax

; 223  : 	const long i3 = (virtual_address >> 30) & 0x1FF;

	mov	rax, QWORD PTR virtual_address$[rsp]
	shr	rax, 30
	and	rax, 511				; 000001ffH
	mov	DWORD PTR i3$[rsp], eax

; 224  : 	const long i2 = (virtual_address >> 21) & 0x1FF;

	mov	rax, QWORD PTR virtual_address$[rsp]
	shr	rax, 21
	and	rax, 511				; 000001ffH
	mov	DWORD PTR i2$[rsp], eax

; 225  : 	const long i1 = (virtual_address >> 12) & 0x1FF;

	mov	rax, QWORD PTR virtual_address$[rsp]
	shr	rax, 12
	and	rax, 511				; 000001ffH
	mov	DWORD PTR i1$[rsp], eax

; 226  : 
; 227  : 	if (!(pml4i[i4] & PAGING_PRESENT)){

	movsxd	rax, DWORD PTR i4$[rsp]
	mov	rcx, QWORD PTR pml4i$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, 1
	test	rax, rax
	jne	SHORT $LN4@map_page_e

; 228  : 		const uint64_t page = (uint64_t)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR page$1[rsp], rax

; 229  : 		pml4i[i4] = page | flags;

	mov	rax, QWORD PTR flags$[rsp]
	mov	rcx, QWORD PTR page$1[rsp]
	or	rcx, rax
	mov	rax, rcx
	movsxd	rcx, DWORD PTR i4$[rsp]
	mov	rdx, QWORD PTR pml4i$[rsp]
	mov	QWORD PTR [rdx+rcx*8], rax

; 230  : 		clear((void*)page);

	mov	rcx, QWORD PTR page$1[rsp]
	call	?clear@@YAXPEAX@Z			; clear

; 231  : 		flush_tlb((void*)page);

	mov	rcx, QWORD PTR page$1[rsp]
	call	flush_tlb

; 232  : 		x64_mfence();

	call	x64_mfence
$LN4@map_page_e:

; 233  : 	}
; 234  : 	uint64_t* pml3 = (uint64_t*)(pml4i[i4] & ~(4096 - 1));

	movsxd	rax, DWORD PTR i4$[rsp]
	mov	rcx, QWORD PTR pml4i$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pml3$[rsp], rax

; 235  : 
; 236  : 	if (!(pml3[i3] & PAGING_PRESENT)){

	movsxd	rax, DWORD PTR i3$[rsp]
	mov	rcx, QWORD PTR pml3$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, 1
	test	rax, rax
	jne	SHORT $LN3@map_page_e

; 237  : 		const uint64_t page = (uint64_t)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR page$3[rsp], rax

; 238  : 		pml3[i3] = page | flags;

	mov	rax, QWORD PTR flags$[rsp]
	mov	rcx, QWORD PTR page$3[rsp]
	or	rcx, rax
	mov	rax, rcx
	movsxd	rcx, DWORD PTR i3$[rsp]
	mov	rdx, QWORD PTR pml3$[rsp]
	mov	QWORD PTR [rdx+rcx*8], rax

; 239  : 		clear((void*)page);

	mov	rcx, QWORD PTR page$3[rsp]
	call	?clear@@YAXPEAX@Z			; clear

; 240  : 		flush_tlb((void*)page);

	mov	rcx, QWORD PTR page$3[rsp]
	call	flush_tlb

; 241  : 		x64_mfence();

	call	x64_mfence
$LN3@map_page_e:

; 242  : 		
; 243  : 	}
; 244  : 
; 245  : 	uint64_t* pml2 = (uint64_t*)(pml3[i3] & ~(4096 - 1));

	movsxd	rax, DWORD PTR i3$[rsp]
	mov	rcx, QWORD PTR pml3$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pml2$[rsp], rax

; 246  : 	if (!(pml2[i2] & PAGING_PRESENT)){

	movsxd	rax, DWORD PTR i2$[rsp]
	mov	rcx, QWORD PTR pml2$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, 1
	test	rax, rax
	jne	SHORT $LN2@map_page_e

; 247  : 
; 248  : 		const uint64_t page = (uint64_t)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR page$2[rsp], rax

; 249  : 		pml2[i2] = page | flags;

	mov	rax, QWORD PTR flags$[rsp]
	mov	rcx, QWORD PTR page$2[rsp]
	or	rcx, rax
	mov	rax, rcx
	movsxd	rcx, DWORD PTR i2$[rsp]
	mov	rdx, QWORD PTR pml2$[rsp]
	mov	QWORD PTR [rdx+rcx*8], rax

; 250  : 		clear((void*)page);

	mov	rcx, QWORD PTR page$2[rsp]
	call	?clear@@YAXPEAX@Z			; clear

; 251  : 		flush_tlb((void*)page);

	mov	rcx, QWORD PTR page$2[rsp]
	call	flush_tlb

; 252  : 		x64_mfence();

	call	x64_mfence
$LN2@map_page_e:

; 253  : 		
; 254  : 	}
; 255  : 
; 256  : 	uint64_t* pml1 = (uint64_t*)(pml2[i2] & ~(4096 - 1));

	movsxd	rax, DWORD PTR i2$[rsp]
	mov	rcx, QWORD PTR pml2$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pml1$[rsp], rax

; 257  : 
; 258  : 	if (pml1[i1] & PAGING_PRESENT){

	movsxd	rax, DWORD PTR i1$[rsp]
	mov	rcx, QWORD PTR pml1$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, 1
	test	rax, rax
	je	SHORT $LN1@map_page_e

; 259  : 
; 260  : 		return false;

	xor	al, al
	jmp	SHORT $LN5@map_page_e
$LN1@map_page_e:

; 261  : 	}
; 262  : 
; 263  : 	pml1[i1] = physical_address | flags;

	mov	rax, QWORD PTR flags$[rsp]
	mov	rcx, QWORD PTR physical_address$[rsp]
	or	rcx, rax
	mov	rax, rcx
	movsxd	rcx, DWORD PTR i1$[rsp]
	mov	rdx, QWORD PTR pml1$[rsp]
	mov	QWORD PTR [rdx+rcx*8], rax

; 264  : 	flush_tlb ((void*)virtual_address);

	mov	rcx, QWORD PTR virtual_address$[rsp]
	call	flush_tlb

; 265  : 	x64_mfence ();

	call	x64_mfence

; 266  : 	return true;

	mov	al, 1
$LN5@map_page_e:

; 267  : }

	add	rsp, 120				; 00000078H
	ret	0
?map_page_ex@@YA_NPEA_K_K1@Z ENDP			; map_page_ex
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\vmmngr.cpp
_TEXT	SEGMENT
i3$ = 32
i2$ = 36
i4$ = 40
flags$ = 48
page$1 = 56
pml3$ = 64
i1$ = 72
page$2 = 80
page$3 = 88
pml2$ = 96
pml4i$ = 104
pml1$ = 112
physical_address$ = 144
virtual_address$ = 152
?map_page@@YA_N_K0@Z PROC				; map_page

; 79   : {

$LN6:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 136				; 00000088H

; 80   : 	size_t flags = PAGING_WRITABLE | PAGING_PRESENT | PAGING_USER;

	mov	QWORD PTR flags$[rsp], 7

; 81   : 
; 82   : 	const long i4 = (virtual_address >> 39) & 0x1FF;

	mov	rax, QWORD PTR virtual_address$[rsp]
	shr	rax, 39					; 00000027H
	and	rax, 511				; 000001ffH
	mov	DWORD PTR i4$[rsp], eax

; 83   : 	const long i3 = (virtual_address >> 30) & 0x1FF;

	mov	rax, QWORD PTR virtual_address$[rsp]
	shr	rax, 30
	and	rax, 511				; 000001ffH
	mov	DWORD PTR i3$[rsp], eax

; 84   : 	const long i2 = (virtual_address >> 21) & 0x1FF;

	mov	rax, QWORD PTR virtual_address$[rsp]
	shr	rax, 21
	and	rax, 511				; 000001ffH
	mov	DWORD PTR i2$[rsp], eax

; 85   : 	const long i1 = (virtual_address >> 12) & 0x1FF;

	mov	rax, QWORD PTR virtual_address$[rsp]
	shr	rax, 12
	and	rax, 511				; 000001ffH
	mov	DWORD PTR i1$[rsp], eax

; 86   : 
; 87   : 	uint64_t *pml4i = (uint64_t*)x64_read_cr3();

	call	x64_read_cr3
	mov	QWORD PTR pml4i$[rsp], rax

; 88   : 	if (!(pml4i[i4] & PAGING_PRESENT))

	movsxd	rax, DWORD PTR i4$[rsp]
	mov	rcx, QWORD PTR pml4i$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, 1
	test	rax, rax
	jne	SHORT $LN3@map_page

; 89   : 	{
; 90   : 		const uint64_t page = (uint64_t)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR page$1[rsp], rax

; 91   : 		pml4i[i4] = page | flags;

	mov	rax, QWORD PTR flags$[rsp]
	mov	rcx, QWORD PTR page$1[rsp]
	or	rcx, rax
	mov	rax, rcx
	movsxd	rcx, DWORD PTR i4$[rsp]
	mov	rdx, QWORD PTR pml4i$[rsp]
	mov	QWORD PTR [rdx+rcx*8], rax

; 92   : 		clear((void*)page);

	mov	rcx, QWORD PTR page$1[rsp]
	call	?clear@@YAXPEAX@Z			; clear

; 93   : 		flush_tlb((void*)page);

	mov	rcx, QWORD PTR page$1[rsp]
	call	flush_tlb

; 94   : 		x64_mfence();

	call	x64_mfence
$LN3@map_page:

; 95   : 	}
; 96   : 	uint64_t* pml3 = (uint64_t*)(pml4i[i4] & ~(4096 - 1));

	movsxd	rax, DWORD PTR i4$[rsp]
	mov	rcx, QWORD PTR pml4i$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pml3$[rsp], rax

; 97   : 	if (!(pml3[i3] & PAGING_PRESENT))

	movsxd	rax, DWORD PTR i3$[rsp]
	mov	rcx, QWORD PTR pml3$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, 1
	test	rax, rax
	jne	SHORT $LN2@map_page

; 98   : 	{
; 99   : 		const uint64_t page = (uint64_t)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR page$3[rsp], rax

; 100  : 		pml3[i3] = page | flags;

	mov	rax, QWORD PTR flags$[rsp]
	mov	rcx, QWORD PTR page$3[rsp]
	or	rcx, rax
	mov	rax, rcx
	movsxd	rcx, DWORD PTR i3$[rsp]
	mov	rdx, QWORD PTR pml3$[rsp]
	mov	QWORD PTR [rdx+rcx*8], rax

; 101  : 		clear((void*)page);

	mov	rcx, QWORD PTR page$3[rsp]
	call	?clear@@YAXPEAX@Z			; clear

; 102  : 		flush_tlb((void*)page);

	mov	rcx, QWORD PTR page$3[rsp]
	call	flush_tlb

; 103  : 		x64_mfence();

	call	x64_mfence
$LN2@map_page:

; 104  : 		
; 105  : 	}
; 106  : 
; 107  : 	uint64_t* pml2 = (uint64_t*)(pml3[i3] & ~(4096 - 1));

	movsxd	rax, DWORD PTR i3$[rsp]
	mov	rcx, QWORD PTR pml3$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pml2$[rsp], rax

; 108  : 	if (!(pml2[i2] & PAGING_PRESENT))

	movsxd	rax, DWORD PTR i2$[rsp]
	mov	rcx, QWORD PTR pml2$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, 1
	test	rax, rax
	jne	SHORT $LN1@map_page

; 109  : 	{
; 110  : 		const uint64_t page = (uint64_t)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR page$2[rsp], rax

; 111  : 		pml2[i2] = page | flags;

	mov	rax, QWORD PTR flags$[rsp]
	mov	rcx, QWORD PTR page$2[rsp]
	or	rcx, rax
	mov	rax, rcx
	movsxd	rcx, DWORD PTR i2$[rsp]
	mov	rdx, QWORD PTR pml2$[rsp]
	mov	QWORD PTR [rdx+rcx*8], rax

; 112  : 		clear((void*)page);

	mov	rcx, QWORD PTR page$2[rsp]
	call	?clear@@YAXPEAX@Z			; clear

; 113  : 		flush_tlb((void*)page);

	mov	rcx, QWORD PTR page$2[rsp]
	call	flush_tlb

; 114  : 		x64_mfence();

	call	x64_mfence
$LN1@map_page:

; 115  : 		
; 116  : 	}
; 117  : 	uint64_t* pml1 = (uint64_t*)(pml2[i2] & ~(4096 - 1));

	movsxd	rax, DWORD PTR i2$[rsp]
	mov	rcx, QWORD PTR pml2$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, -4096				; fffffffffffff000H
	mov	QWORD PTR pml1$[rsp], rax

; 118  : 	/*if (pml1[i1] & PAGING_PRESENT)
; 119  : 	{
; 120  : 		return false;
; 121  : 	}
; 122  : */
; 123  : 	pml1[i1] = physical_address | flags;

	mov	rax, QWORD PTR flags$[rsp]
	mov	rcx, QWORD PTR physical_address$[rsp]
	or	rcx, rax
	mov	rax, rcx
	movsxd	rcx, DWORD PTR i1$[rsp]
	mov	rdx, QWORD PTR pml1$[rsp]
	mov	QWORD PTR [rdx+rcx*8], rax

; 124  : 	flush_tlb ((void*)virtual_address);

	mov	rcx, QWORD PTR virtual_address$[rsp]
	call	flush_tlb

; 125  : 	x64_mfence ();

	call	x64_mfence

; 126  : 	return true;

	mov	al, 1

; 127  : }

	add	rsp, 136				; 00000088H
	ret	0
?map_page@@YA_N_K0@Z ENDP				; map_page
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\vmmngr.cpp
_TEXT	SEGMENT
i$1 = 32
old_pml4$ = 40
pml4$ = 48
?vmmngr_x86_64_init@@YAXXZ PROC				; vmmngr_x86_64_init

; 60   : void vmmngr_x86_64_init () {

$LN7:
	sub	rsp, 72					; 00000048H

; 61   : 	//! FIXME: pml4 address should be relocatable
; 62   : 	//! FIXME: the address assigned should be 4 KB aligned
; 63   : 	uint64_t * pml4 = (uint64_t*)pmmngr_alloc(); 

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR pml4$[rsp], rax

; 64   : 	uint64_t* old_pml4 = (uint64_t*)x64_read_cr3();

	call	x64_read_cr3
	mov	QWORD PTR old_pml4$[rsp], rax

; 65   : 
; 66   : 	//! just copy the paging structure setuped by XNLDR 
; 67   : 	//! for the kernel! also known as kernel address space
; 68   : 	for (int i = 0; i < 512; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN4@vmmngr_x86
$LN3@vmmngr_x86:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN4@vmmngr_x86:
	cmp	DWORD PTR i$1[rsp], 512			; 00000200H
	jge	SHORT $LN2@vmmngr_x86

; 69   : 		if ((old_pml4[i] & 1) == 1)

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR old_pml4$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8]
	and	rax, 1
	cmp	rax, 1
	jne	SHORT $LN1@vmmngr_x86

; 70   : 			pml4[i] = old_pml4[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR pml4$[rsp]
	mov	r8, QWORD PTR old_pml4$[rsp]
	mov	rax, QWORD PTR [r8+rax*8]
	mov	QWORD PTR [rdx+rcx*8], rax
$LN1@vmmngr_x86:

; 71   : 	}

	jmp	SHORT $LN3@vmmngr_x86
$LN2@vmmngr_x86:

; 72   : 
; 73   : 	x64_write_cr3((size_t)pml4);

	mov	rcx, QWORD PTR pml4$[rsp]
	call	x64_write_cr3

; 74   : }

	add	rsp, 72					; 00000048H
	ret	0
?vmmngr_x86_64_init@@YAXXZ ENDP				; vmmngr_x86_64_init
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\vmmngr.cpp
_TEXT	SEGMENT
addr$ = 8
?p_index@@YA_K_K@Z PROC					; p_index

; 46   : size_t p_index (uint64_t addr){

	mov	QWORD PTR [rsp+8], rcx

; 47   : 	return (addr & 0x7ff);

	mov	rax, QWORD PTR addr$[rsp]
	and	rax, 2047				; 000007ffH

; 48   : }

	ret	0
?p_index@@YA_K_K@Z ENDP					; p_index
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\vmmngr.cpp
_TEXT	SEGMENT
addr$ = 8
?pt_index@@YA_K_K@Z PROC				; pt_index

; 42   : size_t pt_index (uint64_t addr){

	mov	QWORD PTR [rsp+8], rcx

; 43   : 	return (addr >> 12) & 0x1ff;

	mov	rax, QWORD PTR addr$[rsp]
	shr	rax, 12
	and	rax, 511				; 000001ffH

; 44   : }

	ret	0
?pt_index@@YA_K_K@Z ENDP				; pt_index
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\vmmngr.cpp
_TEXT	SEGMENT
addr$ = 8
?pd_index@@YA_K_K@Z PROC				; pd_index

; 38   : size_t pd_index (uint64_t addr){

	mov	QWORD PTR [rsp+8], rcx

; 39   : 	return (addr >> 21) & 0x1ff;

	mov	rax, QWORD PTR addr$[rsp]
	shr	rax, 21
	and	rax, 511				; 000001ffH

; 40   : }

	ret	0
?pd_index@@YA_K_K@Z ENDP				; pd_index
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\vmmngr.cpp
_TEXT	SEGMENT
addr$ = 8
?pdp_index@@YA_K_K@Z PROC				; pdp_index

; 34   : size_t pdp_index (uint64_t addr){

	mov	QWORD PTR [rsp+8], rcx

; 35   : 	return (addr >> 30) & 0x1ff;

	mov	rax, QWORD PTR addr$[rsp]
	shr	rax, 30
	and	rax, 511				; 000001ffH

; 36   : }

	ret	0
?pdp_index@@YA_K_K@Z ENDP				; pdp_index
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\vmmngr.cpp
_TEXT	SEGMENT
addr$ = 8
?pml4_index@@YA_K_K@Z PROC				; pml4_index

; 30   : size_t  pml4_index (uint64_t addr){

	mov	QWORD PTR [rsp+8], rcx

; 31   : 	return (addr >> 39) & 0x1ff;

	mov	rax, QWORD PTR addr$[rsp]
	shr	rax, 39					; 00000027H
	and	rax, 511				; 000001ffH

; 32   : }

	ret	0
?pml4_index@@YA_K_K@Z ENDP				; pml4_index
_TEXT	ENDS
END
