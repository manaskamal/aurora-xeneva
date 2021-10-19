; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?gmr@@3U_gmr_state_@@A				; gmr
_BSS	SEGMENT
?gmr@@3U_gmr_state_@@A DB 0cH DUP (?)			; gmr
_BSS	ENDS
CONST	SEGMENT
$SG5509	DB	'Virtual device does not have GMR support', 0aH, 00H
	ORG $+6
$SG5515	DB	'Virtual device does not have GMR v2 support', 0aH, 00H
	ORG $+3
$SG5526	DB	'Desc Array -> %x', 0aH, 00H
	ORG $+6
$SG5532	DB	'First page -> %x', 0aH, 00H
	ORG $+6
$SG5543	DB	'REGISTER WRITTEN', 0aH, 00H
	ORG $+6
$SG5550	DB	'PPN iiiii -> %x', 0aH, 00H
	ORG $+7
$SG5551	DB	'returning', 0aH, 00H
	ORG $+5
$SG5561	DB	'Desc allocated %x', 0aH, 00H
CONST	ENDS
PUBLIC	?gmr_init@@YAXXZ				; gmr_init
PUBLIC	?gmr2_init@@YAXXZ				; gmr2_init
PUBLIC	?gmr_alloc_descriptor@@YAIPEAUSVGAGuestMemDescriptor@@I@Z ; gmr_alloc_descriptor
PUBLIC	?gmr_define@@YAXIPEAUSVGAGuestMemDescriptor@@I@Z ; gmr_define
PUBLIC	?gmr_define_contiguous@@YAIII@Z			; gmr_define_contiguous
PUBLIC	?gmr_define_even_pages@@YAIII@Z			; gmr_define_even_pages
PUBLIC	?gmr_free_all@@YAXXZ				; gmr_free_all
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?svga_read_reg@@YAII@Z:PROC			; svga_read_reg
EXTRN	?svga_write_reg@@YAXII@Z:PROC			; svga_write_reg
EXTRN	?svga_dev@@3U_svga_drive_@@A:BYTE		; svga_dev
pdata	SEGMENT
$pdata$?gmr_init@@YAXXZ DD imagerel $LN5
	DD	imagerel $LN5+70
	DD	imagerel $unwind$?gmr_init@@YAXXZ
$pdata$?gmr2_init@@YAXXZ DD imagerel $LN5
	DD	imagerel $LN5+70
	DD	imagerel $unwind$?gmr2_init@@YAXXZ
$pdata$?gmr_alloc_descriptor@@YAIPEAUSVGAGuestMemDescriptor@@I@Z DD imagerel $LN9
	DD	imagerel $LN9+300
	DD	imagerel $unwind$?gmr_alloc_descriptor@@YAIPEAUSVGAGuestMemDescriptor@@I@Z
$pdata$?gmr_define@@YAXIPEAUSVGAGuestMemDescriptor@@I@Z DD imagerel $LN3
	DD	imagerel $LN3+81
	DD	imagerel $unwind$?gmr_define@@YAXIPEAUSVGAGuestMemDescriptor@@I@Z
$pdata$?gmr_define_contiguous@@YAIII@Z DD imagerel $LN3
	DD	imagerel $LN3+86
	DD	imagerel $unwind$?gmr_define_contiguous@@YAIII@Z
$pdata$?gmr_define_even_pages@@YAIII@Z DD imagerel $LN6
	DD	imagerel $LN6+157
	DD	imagerel $unwind$?gmr_define_even_pages@@YAIII@Z
$pdata$?gmr_free_all@@YAXXZ DD imagerel $LN6
	DD	imagerel $LN6+57
	DD	imagerel $unwind$?gmr_free_all@@YAXXZ
pdata	ENDS
xdata	SEGMENT
$unwind$?gmr_init@@YAXXZ DD 010401H
	DD	04204H
$unwind$?gmr2_init@@YAXXZ DD 010401H
	DD	04204H
$unwind$?gmr_alloc_descriptor@@YAIPEAUSVGAGuestMemDescriptor@@I@Z DD 010d01H
	DD	0820dH
$unwind$?gmr_define@@YAXIPEAUSVGAGuestMemDescriptor@@I@Z DD 011201H
	DD	06212H
$unwind$?gmr_define_contiguous@@YAIII@Z DD 010c01H
	DD	0620cH
$unwind$?gmr_define_even_pages@@YAIII@Z DD 010c01H
	DD	0620cH
$unwind$?gmr_free_all@@YAXXZ DD 010401H
	DD	06204H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\svga\gmr.cpp
_TEXT	SEGMENT
id$ = 32
?gmr_free_all@@YAXXZ PROC				; gmr_free_all

; 137  : {

$LN6:
	sub	rsp, 56					; 00000038H

; 138  :    uint32 id;
; 139  : 
; 140  :    for (id = 0; id < gmr.max_ids; id++) {

	mov	DWORD PTR id$[rsp], 0
	jmp	SHORT $LN3@gmr_free_a
$LN2@gmr_free_a:
	mov	eax, DWORD PTR id$[rsp]
	inc	eax
	mov	DWORD PTR id$[rsp], eax
$LN3@gmr_free_a:
	mov	eax, DWORD PTR ?gmr@@3U_gmr_state_@@A
	cmp	DWORD PTR id$[rsp], eax
	jae	SHORT $LN1@gmr_free_a

; 141  :       gmr_define(id, NULL, 0);

	xor	r8d, r8d
	xor	edx, edx
	mov	ecx, DWORD PTR id$[rsp]
	call	?gmr_define@@YAXIPEAUSVGAGuestMemDescriptor@@I@Z ; gmr_define

; 142  :    }

	jmp	SHORT $LN2@gmr_free_a
$LN1@gmr_free_a:

; 143  : }

	add	rsp, 56					; 00000038H
	ret	0
?gmr_free_all@@YAXXZ ENDP				; gmr_free_all
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\svga\gmr.cpp
_TEXT	SEGMENT
i$ = 32
region$ = 36
desc$ = 40
gmrId$ = 64
numPages$ = 72
?gmr_define_even_pages@@YAIII@Z PROC			; gmr_define_even_pages

; 117  : {

$LN6:
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 118  :    SVGAGuestMemDescriptor *desc;
; 119  :    ppn region = (ppn)pmmngr_alloc();   //malloc(numPages * 2);

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	DWORD PTR region$[rsp], eax

; 120  :  
; 121  :    int i;
; 122  : 
; 123  :    desc = (SVGAGuestMemDescriptor *)pmmngr_alloc();//malloc(sizeof(desc) * numPages);

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR desc$[rsp], rax

; 124  :    printf ("Desc allocated %x\n", desc);

	mov	rdx, QWORD PTR desc$[rsp]
	lea	rcx, OFFSET FLAT:$SG5561
	call	?printf@@YAXPEBDZZ			; printf

; 125  :    for (i = 0; i < numPages; i++) {

	mov	DWORD PTR i$[rsp], 0
	jmp	SHORT $LN3@gmr_define
$LN2@gmr_define:
	mov	eax, DWORD PTR i$[rsp]
	inc	eax
	mov	DWORD PTR i$[rsp], eax
$LN3@gmr_define:
	mov	eax, DWORD PTR numPages$[rsp]
	cmp	DWORD PTR i$[rsp], eax
	jae	SHORT $LN1@gmr_define

; 126  :       desc[i].ppn = region + i * 4096;

	mov	eax, DWORD PTR i$[rsp]
	imul	eax, 4096				; 00001000H
	mov	ecx, DWORD PTR region$[rsp]
	add	ecx, eax
	mov	eax, ecx
	movsxd	rcx, DWORD PTR i$[rsp]
	mov	rdx, QWORD PTR desc$[rsp]
	mov	DWORD PTR [rdx+rcx*8], eax

; 127  :       desc[i].numPages = 1;

	movsxd	rax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR desc$[rsp]
	mov	DWORD PTR [rcx+rax*8+4], 1

; 128  :    }

	jmp	SHORT $LN2@gmr_define
$LN1@gmr_define:

; 129  : 
; 130  :    gmr_define(gmrId, desc, numPages);

	mov	r8d, DWORD PTR numPages$[rsp]
	mov	rdx, QWORD PTR desc$[rsp]
	mov	ecx, DWORD PTR gmrId$[rsp]
	call	?gmr_define@@YAXIPEAUSVGAGuestMemDescriptor@@I@Z ; gmr_define

; 131  : 
; 132  :    return region;

	mov	eax, DWORD PTR region$[rsp]

; 133  : }

	add	rsp, 56					; 00000038H
	ret	0
?gmr_define_even_pages@@YAIII@Z ENDP			; gmr_define_even_pages
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\svga\gmr.cpp
_TEXT	SEGMENT
desc$ = 32
gmrId$ = 64
numPages$ = 72
?gmr_define_contiguous@@YAIII@Z PROC			; gmr_define_contiguous

; 104  : ppn gmr_define_contiguous(uint32 gmrId, uint32 numPages){

$LN3:
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 105  :    SVGAGuestMemDescriptor desc;
; 106  :     desc.ppn = (ppn)pmmngr_alloc(); //malloc(numPages),

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	DWORD PTR desc$[rsp], eax

; 107  :     desc.numPages = numPages,
; 108  : 	printf ("PPN iiiii -> %x\n", desc.ppn);

	mov	eax, DWORD PTR numPages$[rsp]
	mov	DWORD PTR desc$[rsp+4], eax
	mov	edx, DWORD PTR desc$[rsp]
	lea	rcx, OFFSET FLAT:$SG5550
	call	?printf@@YAXPEBDZZ			; printf

; 109  : 
; 110  :     gmr_define(gmrId, &desc, 1);

	mov	r8d, 1
	lea	rdx, QWORD PTR desc$[rsp]
	mov	ecx, DWORD PTR gmrId$[rsp]
	call	?gmr_define@@YAXIPEAUSVGAGuestMemDescriptor@@I@Z ; gmr_define

; 111  : 	printf ("returning\n");

	lea	rcx, OFFSET FLAT:$SG5551
	call	?printf@@YAXPEBDZZ			; printf

; 112  :    return desc.ppn;

	mov	eax, DWORD PTR desc$[rsp]

; 113  : }

	add	rsp, 56					; 00000038H
	ret	0
?gmr_define_contiguous@@YAIII@Z ENDP			; gmr_define_contiguous
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\svga\gmr.cpp
_TEXT	SEGMENT
desc$ = 32
gmrId$ = 64
descArray$ = 72
numDescriptors$ = 80
?gmr_define@@YAXIPEAUSVGAGuestMemDescriptor@@I@Z PROC	; gmr_define

; 82   : {

$LN3:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 83   :    ppn desc = gmr_alloc_descriptor(descArray, numDescriptors);

	mov	edx, DWORD PTR numDescriptors$[rsp]
	mov	rcx, QWORD PTR descArray$[rsp]
	call	?gmr_alloc_descriptor@@YAIPEAUSVGAGuestMemDescriptor@@I@Z ; gmr_alloc_descriptor
	mov	DWORD PTR desc$[rsp], eax

; 84   : 
; 85   :    /*
; 86   :     * Define/undefine the GMR. Defining an empty GMR is equivalent to
; 87   :     * undefining a GMR.
; 88   :     */
; 89   : 
; 90   :    svga_write_reg(SVGA_REG_GMR_ID, gmrId);

	mov	edx, DWORD PTR gmrId$[rsp]
	mov	ecx, 41					; 00000029H
	call	?svga_write_reg@@YAXII@Z		; svga_write_reg

; 91   :    svga_write_reg(SVGA_REG_GMR_DESCRIPTOR, desc);

	mov	edx, DWORD PTR desc$[rsp]
	mov	ecx, 42					; 0000002aH
	call	?svga_write_reg@@YAXII@Z		; svga_write_reg

; 92   :    printf ("REGISTER WRITTEN\n");

	lea	rcx, OFFSET FLAT:$SG5543
	call	?printf@@YAXPEBDZZ			; printf

; 93   :    //if (desc) {
; 94   :       /*
; 95   :        * Clobber the first page, to verify that the device reads our
; 96   :        * descriptors synchronously when we write the GMR registers.
; 97   :        */
; 98   :       //Heap_DiscardPages(desc, 1);
; 99   :   // }
; 100  : }

	add	rsp, 56					; 00000038H
	ret	0
?gmr_define@@YAXIPEAUSVGAGuestMemDescriptor@@I@Z ENDP	; gmr_define
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\svga\gmr.cpp
_TEXT	SEGMENT
i$ = 32
page$ = 36
first_page$ = 40
desc_per_page$ = 44
desc$ = 48
desc_array$ = 80
num_descriptor$ = 88
?gmr_alloc_descriptor@@YAIPEAUSVGAGuestMemDescriptor@@I@Z PROC ; gmr_alloc_descriptor

; 39   : ppn gmr_alloc_descriptor (SVGAGuestMemDescriptor *desc_array, uint32_t num_descriptor) {

$LN9:
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 40   : 
; 41   : 	const uint32_t desc_per_page = PAGE_SIZE / sizeof (SVGAGuestMemDescriptor) - 1;

	mov	DWORD PTR desc_per_page$[rsp], 511	; 000001ffH

; 42   : 	SVGAGuestMemDescriptor *desc = NULL;

	mov	QWORD PTR desc$[rsp], 0

; 43   : 	ppn first_page ; //= (ppn)pmmngr_alloc();
; 44   : 	ppn page = 0;

	mov	DWORD PTR page$[rsp], 0

; 45   : 
; 46   : 	int i = 0;

	mov	DWORD PTR i$[rsp], 0

; 47   : 	printf ("Desc Array -> %x\n", desc_array);

	mov	rdx, QWORD PTR desc_array$[rsp]
	lea	rcx, OFFSET FLAT:$SG5526
	call	?printf@@YAXPEBDZZ			; printf
$LN8@gmr_alloc_:
$LN5@gmr_alloc_:

; 48   : 
; 49   : 	while (num_descriptor) {

	cmp	DWORD PTR num_descriptor$[rsp], 0
	je	$LN4@gmr_alloc_

; 50   : 		if (!first_page) {

	cmp	DWORD PTR first_page$[rsp], 0
	jne	SHORT $LN3@gmr_alloc_

; 51   : 			first_page = page = (ppn)pmmngr_alloc();//malloc(4096); //pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	DWORD PTR page$[rsp], eax
	mov	eax, DWORD PTR page$[rsp]
	mov	DWORD PTR first_page$[rsp], eax

; 52   : 			printf ("First page -> %x\n", page);

	mov	edx, DWORD PTR page$[rsp]
	lea	rcx, OFFSET FLAT:$SG5532
	call	?printf@@YAXPEBDZZ			; printf
$LN3@gmr_alloc_:

; 53   : 		}
; 54   : 
; 55   : 		desc = (SVGAGuestMemDescriptor *)page; //PPN_POINTER(page);

	mov	eax, DWORD PTR page$[rsp]
	mov	QWORD PTR desc$[rsp], rax

; 56   : 
; 57   : 		if (i == desc_per_page) {

	cmp	DWORD PTR i$[rsp], 511			; 000001ffH
	jne	SHORT $LN2@gmr_alloc_

; 58   : 
; 59   : 			page = (ppn)pmmngr_alloc();   //malloc(4096)

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	DWORD PTR page$[rsp], eax

; 60   : 			desc[i].ppn = page;

	movsxd	rax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR desc$[rsp]
	mov	edx, DWORD PTR page$[rsp]
	mov	DWORD PTR [rcx+rax*8], edx

; 61   : 			desc[i].numPages = 0;

	movsxd	rax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR desc$[rsp]
	mov	DWORD PTR [rcx+rax*8+4], 0

; 62   : 			i = 0; 

	mov	DWORD PTR i$[rsp], 0

; 63   : 			continue;

	jmp	SHORT $LN5@gmr_alloc_
$LN2@gmr_alloc_:

; 64   : 		}
; 65   : 
; 66   : 		desc[i] = *desc_array;

	mov	rax, QWORD PTR desc_array$[rsp]
	mov	rax, QWORD PTR [rax]
	movsxd	rcx, DWORD PTR i$[rsp]
	mov	rdx, QWORD PTR desc$[rsp]
	mov	QWORD PTR [rdx+rcx*8], rax

; 67   : 		i++;

	mov	eax, DWORD PTR i$[rsp]
	inc	eax
	mov	DWORD PTR i$[rsp], eax

; 68   : 		desc_array++;

	mov	rax, QWORD PTR desc_array$[rsp]
	add	rax, 8
	mov	QWORD PTR desc_array$[rsp], rax

; 69   : 		num_descriptor--;

	mov	eax, DWORD PTR num_descriptor$[rsp]
	dec	eax
	mov	DWORD PTR num_descriptor$[rsp], eax

; 70   : 	}

	jmp	$LN8@gmr_alloc_
$LN4@gmr_alloc_:

; 71   : 
; 72   : 	if (desc) {

	cmp	QWORD PTR desc$[rsp], 0
	je	SHORT $LN1@gmr_alloc_

; 73   : 		desc[i].ppn = 0;

	movsxd	rax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR desc$[rsp]
	mov	DWORD PTR [rcx+rax*8], 0

; 74   : 		desc[i].numPages = 0;

	movsxd	rax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR desc$[rsp]
	mov	DWORD PTR [rcx+rax*8+4], 0
$LN1@gmr_alloc_:

; 75   : 	}
; 76   : 	return first_page;

	mov	eax, DWORD PTR first_page$[rsp]

; 77   : }

	add	rsp, 72					; 00000048H
	ret	0
?gmr_alloc_descriptor@@YAIPEAUSVGAGuestMemDescriptor@@I@Z ENDP ; gmr_alloc_descriptor
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\svga\gmr.cpp
_TEXT	SEGMENT
?gmr2_init@@YAXXZ PROC					; gmr2_init

; 29   : void gmr2_init (void) {

$LN5:
	sub	rsp, 40					; 00000028H

; 30   : 	
; 31   : 	if (svga_dev.capabilities & SVGA_CAP_GMR2) {

	mov	eax, DWORD PTR ?svga_dev@@3U_svga_drive_@@A+48
	and	eax, 4194304				; 00400000H
	test	eax, eax
	je	SHORT $LN2@gmr2_init

; 32   : 		gmr.max_ids = svga_read_reg (SVGA_REG_GMR_MAX_IDS);

	mov	ecx, 43					; 0000002bH
	call	?svga_read_reg@@YAII@Z			; svga_read_reg
	mov	DWORD PTR ?gmr@@3U_gmr_state_@@A, eax

; 33   : 		gmr.max_pages = svga_read_reg (SVGA_REG_GMRS_MAX_PAGES);

	mov	ecx, 46					; 0000002eH
	call	?svga_read_reg@@YAII@Z			; svga_read_reg
	mov	DWORD PTR ?gmr@@3U_gmr_state_@@A+8, eax

; 34   : 	} else {

	jmp	SHORT $LN1@gmr2_init
$LN2@gmr2_init:

; 35   : 		printf ("Virtual device does not have GMR v2 support\n");

	lea	rcx, OFFSET FLAT:$SG5515
	call	?printf@@YAXPEBDZZ			; printf
$LN1@gmr2_init:

; 36   : 	}
; 37   : }

	add	rsp, 40					; 00000028H
	ret	0
?gmr2_init@@YAXXZ ENDP					; gmr2_init
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\svga\gmr.cpp
_TEXT	SEGMENT
?gmr_init@@YAXXZ PROC					; gmr_init

; 19   : void gmr_init () {

$LN5:
	sub	rsp, 40					; 00000028H

; 20   : 
; 21   : 	if (svga_dev.capabilities & SVGA_CAP_GMR) {

	mov	eax, DWORD PTR ?svga_dev@@3U_svga_drive_@@A+48
	and	eax, 1048576				; 00100000H
	test	eax, eax
	je	SHORT $LN2@gmr_init

; 22   : 		gmr.max_ids = svga_read_reg (SVGA_REG_GMR_MAX_IDS);

	mov	ecx, 43					; 0000002bH
	call	?svga_read_reg@@YAII@Z			; svga_read_reg
	mov	DWORD PTR ?gmr@@3U_gmr_state_@@A, eax

; 23   : 		gmr.max_descriptor_len = svga_read_reg (SVGA_REG_GMR_MAX_DESCRIPTOR_LENGTH);

	mov	ecx, 44					; 0000002cH
	call	?svga_read_reg@@YAII@Z			; svga_read_reg
	mov	DWORD PTR ?gmr@@3U_gmr_state_@@A+4, eax

; 24   : 	} else {

	jmp	SHORT $LN1@gmr_init
$LN2@gmr_init:

; 25   : 		printf ("Virtual device does not have GMR support\n");

	lea	rcx, OFFSET FLAT:$SG5509
	call	?printf@@YAXPEBDZZ			; printf
$LN1@gmr_init:

; 26   : 	}
; 27   : }

	add	rsp, 40					; 00000028H
	ret	0
?gmr_init@@YAXXZ ENDP					; gmr_init
_TEXT	ENDS
END
