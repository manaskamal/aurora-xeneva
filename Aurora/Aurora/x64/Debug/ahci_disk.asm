; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?sata_drive_port@@3PEAU_hba_port_@@EA		; sata_drive_port
_BSS	SEGMENT
?sata_drive_port@@3PEAU_hba_port_@@EA DQ 01H DUP (?)	; sata_drive_port
_BSS	ENDS
CONST	SEGMENT
$SG3839	DB	'[AHCI]:Port Hung', 0aH, 00H
	ORG $+6
$SG3845	DB	'[AHCI]: Port error ', 0dH, 0aH, 00H
	ORG $+2
$SG3872	DB	'[AHCI]:Port Hung', 0aH, 00H
	ORG $+6
$SG3878	DB	'[AHCI]: Port error ', 0dH, 0aH, 00H
	ORG $+2
$SG3907	DB	'[AHCI]:Port Hung', 0aH, 00H
	ORG $+6
$SG3926	DB	'[AHCI]: Port Supports cold presence %d', 0aH, 00H
$SG3943	DB	'[AHCI]: Model -> %s', 0aH, 00H
CONST	ENDS
PUBLIC	?ahci_disk_initialize@@YAXPEAU_hba_port_@@@Z	; ahci_disk_initialize
PUBLIC	?ahci_disk_write@@YAXPEAU_hba_port_@@_KIPEA_K@Z	; ahci_disk_write
PUBLIC	?ahci_disk_read@@YAXPEAU_hba_port_@@_KIPEA_K@Z	; ahci_disk_read
PUBLIC	?ahci_disk_stop_cmd@@YAXPEAU_hba_port_@@@Z	; ahci_disk_stop_cmd
PUBLIC	?ahci_disk_start_cmd@@YAXPEAU_hba_port_@@@Z	; ahci_disk_start_cmd
PUBLIC	?ahci_disk_get_port@@YAPEAU_hba_port_@@XZ	; ahci_disk_get_port
PUBLIC	?ahci_disk_find_slot@@YAIPEAU_hba_port_@@@Z	; ahci_disk_find_slot
PUBLIC	?ahci_disk_identify@@YAXPEAU_hba_port_@@_KIPEA_K@Z ; ahci_disk_identify
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?_debug_print_@@YAXPEADZZ:PROC			; _debug_print_
pdata	SEGMENT
$pdata$?ahci_disk_initialize@@YAXPEAU_hba_port_@@@Z DD imagerel $LN10
	DD	imagerel $LN10+776
	DD	imagerel $unwind$?ahci_disk_initialize@@YAXPEAU_hba_port_@@@Z
$pdata$?ahci_disk_write@@YAXPEAU_hba_port_@@_KIPEA_K@Z DD imagerel $LN10
	DD	imagerel $LN10+744
	DD	imagerel $unwind$?ahci_disk_write@@YAXPEAU_hba_port_@@_KIPEA_K@Z
$pdata$?ahci_disk_read@@YAXPEAU_hba_port_@@_KIPEA_K@Z DD imagerel $LN12
	DD	imagerel $LN12+763
	DD	imagerel $unwind$?ahci_disk_read@@YAXPEAU_hba_port_@@_KIPEA_K@Z
$pdata$?ahci_disk_find_slot@@YAIPEAU_hba_port_@@@Z DD imagerel $LN7
	DD	imagerel $LN7+87
	DD	imagerel $unwind$?ahci_disk_find_slot@@YAIPEAU_hba_port_@@@Z
$pdata$?ahci_disk_identify@@YAXPEAU_hba_port_@@_KIPEA_K@Z DD imagerel $LN12
	DD	imagerel $LN12+1001
	DD	imagerel $unwind$?ahci_disk_identify@@YAXPEAU_hba_port_@@_KIPEA_K@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?ahci_disk_initialize@@YAXPEAU_hba_port_@@@Z DD 020c01H
	DD	013010cH
$unwind$?ahci_disk_write@@YAXPEAU_hba_port_@@_KIPEA_K@Z DD 011801H
	DD	0c218H
$unwind$?ahci_disk_read@@YAXPEAU_hba_port_@@_KIPEA_K@Z DD 011801H
	DD	0c218H
$unwind$?ahci_disk_find_slot@@YAIPEAU_hba_port_@@@Z DD 010901H
	DD	02209H
$unwind$?ahci_disk_identify@@YAXPEAU_hba_port_@@_KIPEA_K@Z DD 011801H
	DD	0c218H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\ahci_disk.cpp
_TEXT	SEGMENT
i$ = 32
fis$ = 40
tbl$ = 48
spin$ = 56
command_slot$ = 60
cmd_list$ = 64
buffer_whole$ = 72
tv365 = 80
tv360 = 84
port$ = 112
lba$ = 120
count$ = 128
buffer$ = 136
?ahci_disk_identify@@YAXPEAU_hba_port_@@_KIPEA_K@Z PROC	; ahci_disk_identify

; 215  : void ahci_disk_identify (HBA_PORT *port, uint64_t lba, uint32_t count, uint64_t *buffer) {

$LN12:
	mov	QWORD PTR [rsp+32], r9
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 104				; 00000068H

; 216  : 	int spin = 0;

	mov	DWORD PTR spin$[rsp], 0

; 217  : 	HBA_CMD_HEADER *cmd_list = (HBA_CMD_HEADER*)port->clb;

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax]
	mov	QWORD PTR cmd_list$[rsp], rax

; 218  : 	uint64_t buffer_whole = (uint64_t)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR buffer_whole$[rsp], rax

; 219  : 
; 220  : 	cmd_list->cfl = sizeof(FIS_REG_H2D)/sizeof(uint32_t);

	mov	rax, QWORD PTR cmd_list$[rsp]
	movzx	eax, BYTE PTR [rax]
	and	al, 224					; 000000e0H
	or	al, 5
	mov	rcx, QWORD PTR cmd_list$[rsp]
	mov	BYTE PTR [rcx], al

; 221  : 	cmd_list->w = 0;

	mov	rax, QWORD PTR cmd_list$[rsp]
	movzx	eax, BYTE PTR [rax]
	and	al, 191					; 000000bfH
	mov	rcx, QWORD PTR cmd_list$[rsp]
	mov	BYTE PTR [rcx], al

; 222  : 	cmd_list->prdtl = (uint16_t)((count-1)>>4)+1;

	mov	eax, DWORD PTR count$[rsp]
	dec	eax
	shr	eax, 4
	movzx	eax, ax
	inc	eax
	mov	rcx, QWORD PTR cmd_list$[rsp]
	mov	WORD PTR [rcx+2], ax

; 223  : 
; 224  : 	uint32_t command_slot = ahci_disk_find_slot(port);

	mov	rcx, QWORD PTR port$[rsp]
	call	?ahci_disk_find_slot@@YAIPEAU_hba_port_@@@Z ; ahci_disk_find_slot
	mov	DWORD PTR command_slot$[rsp], eax

; 225  : 
; 226  : 	HBA_CMD_TABLE *tbl = (HBA_CMD_TABLE*)cmd_list[command_slot].ctba;

	mov	eax, DWORD PTR command_slot$[rsp]
	imul	rax, 32					; 00000020H
	mov	rcx, QWORD PTR cmd_list$[rsp]
	mov	eax, DWORD PTR [rcx+rax+8]
	mov	QWORD PTR tbl$[rsp], rax

; 227  : 	int i=0;

	mov	DWORD PTR i$[rsp], 0

; 228  : 	for (i = 0; i < cmd_list->prdtl; i++){

	mov	DWORD PTR i$[rsp], 0
	jmp	SHORT $LN9@ahci_disk_
$LN8@ahci_disk_:
	mov	eax, DWORD PTR i$[rsp]
	inc	eax
	mov	DWORD PTR i$[rsp], eax
$LN9@ahci_disk_:
	mov	rax, QWORD PTR cmd_list$[rsp]
	movzx	eax, WORD PTR [rax+2]
	cmp	DWORD PTR i$[rsp], eax
	jge	$LN7@ahci_disk_

; 229  : 		tbl->prdt[i].data_base_address = buffer_whole & 0xffffffff;

	mov	eax, -1					; ffffffffH
	mov	rcx, QWORD PTR buffer_whole$[rsp]
	and	rcx, rax
	mov	rax, rcx
	movsxd	rcx, DWORD PTR i$[rsp]
	imul	rcx, 16
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+128], eax

; 230  : 		tbl->prdt[i].dbau = buffer_whole >> 32;

	mov	rax, QWORD PTR buffer_whole$[rsp]
	shr	rax, 32					; 00000020H
	movsxd	rcx, DWORD PTR i$[rsp]
	imul	rcx, 16
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+132], eax

; 231  : 		tbl->prdt[i].data_byte_count = (512 * count) - 1;

	mov	eax, DWORD PTR count$[rsp]
	imul	eax, 512				; 00000200H
	dec	eax
	movsxd	rcx, DWORD PTR i$[rsp]
	imul	rcx, 16
	and	eax, 4194303				; 003fffffH
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	ecx, DWORD PTR [rdx+rcx+140]
	and	ecx, -4194304				; ffc00000H
	or	ecx, eax
	mov	eax, ecx
	movsxd	rcx, DWORD PTR i$[rsp]
	imul	rcx, 16
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+140], eax

; 232  : 		tbl->prdt[i].i = 1;

	movsxd	rax, DWORD PTR i$[rsp]
	imul	rax, 16
	mov	rcx, QWORD PTR tbl$[rsp]
	mov	eax, DWORD PTR [rcx+rax+140]
	bts	eax, 31
	movsxd	rcx, DWORD PTR i$[rsp]
	imul	rcx, 16
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+140], eax

; 233  : 		buffer += 512*count;

	mov	eax, DWORD PTR count$[rsp]
	imul	eax, 512				; 00000200H
	mov	eax, eax
	mov	rcx, QWORD PTR buffer$[rsp]
	lea	rax, QWORD PTR [rcx+rax*8]
	mov	QWORD PTR buffer$[rsp], rax

; 234  : 		buffer_whole = (uint32_t)buffer;

	mov	eax, DWORD PTR buffer$[rsp]
	mov	QWORD PTR buffer_whole$[rsp], rax

; 235  : 	}

	jmp	$LN8@ahci_disk_
$LN7@ahci_disk_:

; 236  : 	tbl->prdt[i].data_base_address = buffer_whole & 0xffffffff;

	mov	eax, -1					; ffffffffH
	mov	rcx, QWORD PTR buffer_whole$[rsp]
	and	rcx, rax
	mov	rax, rcx
	movsxd	rcx, DWORD PTR i$[rsp]
	imul	rcx, 16
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+128], eax

; 237  : 	tbl->prdt[i].dbau = buffer_whole >> 32;

	mov	rax, QWORD PTR buffer_whole$[rsp]
	shr	rax, 32					; 00000020H
	movsxd	rcx, DWORD PTR i$[rsp]
	imul	rcx, 16
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+132], eax

; 238  : 	tbl->prdt[i].data_byte_count = (512 * count) - 1;

	mov	eax, DWORD PTR count$[rsp]
	imul	eax, 512				; 00000200H
	dec	eax
	movsxd	rcx, DWORD PTR i$[rsp]
	imul	rcx, 16
	and	eax, 4194303				; 003fffffH
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	ecx, DWORD PTR [rdx+rcx+140]
	and	ecx, -4194304				; ffc00000H
	or	ecx, eax
	mov	eax, ecx
	movsxd	rcx, DWORD PTR i$[rsp]
	imul	rcx, 16
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+140], eax

; 239  : 	tbl->prdt[i].i = 1;

	movsxd	rax, DWORD PTR i$[rsp]
	imul	rax, 16
	mov	rcx, QWORD PTR tbl$[rsp]
	mov	eax, DWORD PTR [rcx+rax+140]
	bts	eax, 31
	movsxd	rcx, DWORD PTR i$[rsp]
	imul	rcx, 16
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+140], eax

; 240  : 
; 241  : 	FIS_REG_H2D *fis = (FIS_REG_H2D*)tbl->cmd_fis;

	mov	rax, QWORD PTR tbl$[rsp]
	mov	QWORD PTR fis$[rsp], rax

; 242  : 	fis->fis_type = FIS_TYPE_REG_H2D;

	mov	rax, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rax], 39			; 00000027H

; 243  : 	fis->c = 1;

	mov	rax, QWORD PTR fis$[rsp]
	movzx	eax, BYTE PTR [rax+1]
	or	al, 128					; 00000080H
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+1], al

; 244  : 	fis->command = ATA_CMD_IDENTIFY;

	mov	rax, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rax+2], 236			; 000000ecH

; 245  : 	fis->lba0 = lba & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+4], al

; 246  : 	fis->lba1 = (lba>>8) & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	shr	rax, 8
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+5], al

; 247  : 	fis->lba2 = (lba>>16) & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	shr	rax, 16
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+6], al

; 248  : 	fis->device = 1<<6;

	mov	rax, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rax+7], 64			; 00000040H

; 249  : 	fis->lba3 = (lba>>24) & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	shr	rax, 24
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+8], al

; 250  : 	fis->lba4 = (lba>>32) & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	shr	rax, 32					; 00000020H
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+9], al

; 251  : 	fis->lba5 = (lba>>40) & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	shr	rax, 40					; 00000028H
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+10], al

; 252  : 	fis->countl = count & 0xff;

	mov	eax, DWORD PTR count$[rsp]
	and	eax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+12], al

; 253  : 	fis->counth = (count >> 8) & 0xff;

	mov	eax, DWORD PTR count$[rsp]
	shr	eax, 8
	and	eax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+13], al
$LN6@ahci_disk_:

; 254  : 
; 255  : 	while((port->tfd & (ATA_SR_BSY  | ATA_SR_DRQ)) && spin < 1000000) {

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+32]
	and	eax, 136				; 00000088H
	test	eax, eax
	je	SHORT $LN5@ahci_disk_
	cmp	DWORD PTR spin$[rsp], 1000000		; 000f4240H
	jge	SHORT $LN5@ahci_disk_

; 256  : 		spin++;

	mov	eax, DWORD PTR spin$[rsp]
	inc	eax
	mov	DWORD PTR spin$[rsp], eax

; 257  : 	}

	jmp	SHORT $LN6@ahci_disk_
$LN5@ahci_disk_:

; 258  : 	if (spin==1000000)

	cmp	DWORD PTR spin$[rsp], 1000000		; 000f4240H
	jne	SHORT $LN4@ahci_disk_

; 259  : 		printf ("[AHCI]:Port Hung\n");

	lea	rcx, OFFSET FLAT:$SG3907
	call	?printf@@YAXPEBDZZ			; printf
$LN4@ahci_disk_:

; 260  : 
; 261  : 	port->ci = 1<<command_slot;

	mov	eax, DWORD PTR command_slot$[rsp]
	mov	ecx, 1
	mov	DWORD PTR tv360[rsp], ecx
	movzx	ecx, al
	mov	eax, DWORD PTR tv360[rsp]
	shl	eax, cl
	mov	rcx, QWORD PTR port$[rsp]
	mov	DWORD PTR [rcx+56], eax
$LN3@ahci_disk_:

; 262  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN2@ahci_disk_

; 263  : 		if ((port->ci & (1<<command_slot)) == 0) 

	mov	eax, DWORD PTR command_slot$[rsp]
	mov	ecx, 1
	mov	DWORD PTR tv365[rsp], ecx
	movzx	ecx, al
	mov	eax, DWORD PTR tv365[rsp]
	shl	eax, cl
	mov	rcx, QWORD PTR port$[rsp]
	mov	ecx, DWORD PTR [rcx+56]
	and	ecx, eax
	mov	eax, ecx
	test	eax, eax
	jne	SHORT $LN1@ahci_disk_

; 264  : 			break;

	jmp	SHORT $LN2@ahci_disk_
$LN1@ahci_disk_:

; 265  : 		/*if (port->is & (1<<30)) 
; 266  : 			break;*/
; 267  : 	}

	jmp	SHORT $LN3@ahci_disk_
$LN2@ahci_disk_:

; 268  : }

	add	rsp, 104				; 00000068H
	ret	0
?ahci_disk_identify@@YAXPEAU_hba_port_@@_KIPEA_K@Z ENDP	; ahci_disk_identify
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\ahci_disk.cpp
_TEXT	SEGMENT
i$1 = 0
slots$ = 4
port$ = 32
?ahci_disk_find_slot@@YAIPEAU_hba_port_@@@Z PROC	; ahci_disk_find_slot

; 77   : uint32_t ahci_disk_find_slot (HBA_PORT *port) {

$LN7:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 78   : 	uint32_t slots = (port->sact | port->ci);

	mov	rax, QWORD PTR port$[rsp]
	mov	rcx, QWORD PTR port$[rsp]
	mov	ecx, DWORD PTR [rcx+56]
	mov	eax, DWORD PTR [rax+52]
	or	eax, ecx
	mov	DWORD PTR slots$[rsp], eax

; 79   : 	for (int i = 0; i < 32; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN4@ahci_disk_
$LN3@ahci_disk_:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN4@ahci_disk_:
	cmp	DWORD PTR i$1[rsp], 32			; 00000020H
	jge	SHORT $LN2@ahci_disk_

; 80   : 		if ((slots & 1) == 0)

	mov	eax, DWORD PTR slots$[rsp]
	and	eax, 1
	test	eax, eax
	jne	SHORT $LN1@ahci_disk_

; 81   : 			return i;

	mov	eax, DWORD PTR i$1[rsp]
	jmp	SHORT $LN5@ahci_disk_
$LN1@ahci_disk_:

; 82   : 		slots >>= 1;

	mov	eax, DWORD PTR slots$[rsp]
	shr	eax, 1
	mov	DWORD PTR slots$[rsp], eax

; 83   : 	}

	jmp	SHORT $LN3@ahci_disk_
$LN2@ahci_disk_:
$LN5@ahci_disk_:

; 84   : }

	add	rsp, 24
	ret	0
?ahci_disk_find_slot@@YAIPEAU_hba_port_@@@Z ENDP	; ahci_disk_find_slot
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\ahci_disk.cpp
_TEXT	SEGMENT
?ahci_disk_get_port@@YAPEAU_hba_port_@@XZ PROC		; ahci_disk_get_port

; 350  : 	return sata_drive_port;

	mov	rax, QWORD PTR ?sata_drive_port@@3PEAU_hba_port_@@EA ; sata_drive_port

; 351  : }

	ret	0
?ahci_disk_get_port@@YAPEAU_hba_port_@@XZ ENDP		; ahci_disk_get_port
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\ahci_disk.cpp
_TEXT	SEGMENT
port$ = 8
?ahci_disk_start_cmd@@YAXPEAU_hba_port_@@@Z PROC	; ahci_disk_start_cmd

; 64   : void ahci_disk_start_cmd (HBA_PORT *port) {

	mov	QWORD PTR [rsp+8], rcx
$LN2@ahci_disk_:

; 65   : 	while (port->cmd & PX_CMD_CR)

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+24]
	and	eax, 32768				; 00008000H
	test	eax, eax
	je	SHORT $LN1@ahci_disk_

; 66   : 		;

	jmp	SHORT $LN2@ahci_disk_
$LN1@ahci_disk_:

; 67   : 	port->cmd |= PX_CMD_FRE;

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+24]
	or	eax, 16
	mov	rcx, QWORD PTR port$[rsp]
	mov	DWORD PTR [rcx+24], eax

; 68   : 	port->cmd |= PX_CMD_START;

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+24]
	or	eax, 1
	mov	rcx, QWORD PTR port$[rsp]
	mov	DWORD PTR [rcx+24], eax

; 69   : }

	ret	0
?ahci_disk_start_cmd@@YAXPEAU_hba_port_@@@Z ENDP	; ahci_disk_start_cmd
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\ahci_disk.cpp
_TEXT	SEGMENT
port$ = 8
?ahci_disk_stop_cmd@@YAXPEAU_hba_port_@@@Z PROC		; ahci_disk_stop_cmd

; 48   : void ahci_disk_stop_cmd (HBA_PORT *port) {

	mov	QWORD PTR [rsp+8], rcx

; 49   : 	port->cmd &= ~PX_CMD_START;

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+24]
	and	eax, -2					; fffffffeH
	mov	rcx, QWORD PTR port$[rsp]
	mov	DWORD PTR [rcx+24], eax

; 50   : 	port->cmd &= ~PX_CMD_FRE;

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+24]
	and	eax, -17				; ffffffefH
	mov	rcx, QWORD PTR port$[rsp]
	mov	DWORD PTR [rcx+24], eax
$LN7@ahci_disk_:
$LN4@ahci_disk_:

; 51   : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN3@ahci_disk_

; 52   : 		if (port->cmd & PX_CMD_FR)

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+24]
	and	eax, 16384				; 00004000H
	test	eax, eax
	je	SHORT $LN2@ahci_disk_

; 53   : 			continue;

	jmp	SHORT $LN4@ahci_disk_
$LN2@ahci_disk_:

; 54   : 		if (port->cmd & PX_CMD_CR)

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+24]
	and	eax, 32768				; 00008000H
	test	eax, eax
	je	SHORT $LN1@ahci_disk_

; 55   : 			continue;

	jmp	SHORT $LN7@ahci_disk_
$LN1@ahci_disk_:

; 56   : 		break;

	jmp	SHORT $LN3@ahci_disk_

; 57   : 	}

	jmp	SHORT $LN4@ahci_disk_
$LN3@ahci_disk_:

; 58   : }

	fatret	0
?ahci_disk_stop_cmd@@YAXPEAU_hba_port_@@@Z ENDP		; ahci_disk_stop_cmd
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\ahci_disk.cpp
_TEXT	SEGMENT
fis$ = 32
spin$ = 40
command_slot$ = 44
tbl$ = 48
cmd_list$ = 56
tv289 = 64
tv284 = 68
buffer_whole$ = 72
i$ = 80
port$ = 112
lba$ = 120
count$ = 128
buffer$ = 136
?ahci_disk_read@@YAXPEAU_hba_port_@@_KIPEA_K@Z PROC	; ahci_disk_read

; 94   : void ahci_disk_read (HBA_PORT *port, uint64_t lba, uint32_t count, uint64_t *buffer) {

$LN12:
	mov	QWORD PTR [rsp+32], r9
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 104				; 00000068H

; 95   : 	//port->is = (uint32_t)-1;
; 96   : 	int spin = 0;

	mov	DWORD PTR spin$[rsp], 0

; 97   : 	HBA_CMD_HEADER *cmd_list = (HBA_CMD_HEADER*)port->clb;

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax]
	mov	QWORD PTR cmd_list$[rsp], rax

; 98   : 	uint64_t buffer_whole = (uint64_t)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR buffer_whole$[rsp], rax

; 99   : 
; 100  : 	cmd_list->cfl = sizeof(FIS_REG_H2D)/sizeof(uint32_t);

	mov	rax, QWORD PTR cmd_list$[rsp]
	movzx	eax, BYTE PTR [rax]
	and	al, 224					; 000000e0H
	or	al, 5
	mov	rcx, QWORD PTR cmd_list$[rsp]
	mov	BYTE PTR [rcx], al

; 101  : 	cmd_list->w = 0;

	mov	rax, QWORD PTR cmd_list$[rsp]
	movzx	eax, BYTE PTR [rax]
	and	al, 191					; 000000bfH
	mov	rcx, QWORD PTR cmd_list$[rsp]
	mov	BYTE PTR [rcx], al

; 102  : 	cmd_list->prdtl = 1;

	mov	eax, 1
	mov	rcx, QWORD PTR cmd_list$[rsp]
	mov	WORD PTR [rcx+2], ax

; 103  : 	
; 104  : 	uint32_t command_slot = ahci_disk_find_slot(port);

	mov	rcx, QWORD PTR port$[rsp]
	call	?ahci_disk_find_slot@@YAIPEAU_hba_port_@@@Z ; ahci_disk_find_slot
	mov	DWORD PTR command_slot$[rsp], eax

; 105  : 
; 106  : 	HBA_CMD_TABLE *tbl = (HBA_CMD_TABLE*)cmd_list[command_slot].ctba;

	mov	eax, DWORD PTR command_slot$[rsp]
	imul	rax, 32					; 00000020H
	mov	rcx, QWORD PTR cmd_list$[rsp]
	mov	eax, DWORD PTR [rcx+rax+8]
	mov	QWORD PTR tbl$[rsp], rax

; 107  : 	int i=0;

	mov	DWORD PTR i$[rsp], 0

; 108  : 	//for (i = 0; i < cmd_list->prdtl; i++){
; 109  : 	tbl->prdt[0].data_base_address = buffer_whole & 0xffffffff;

	mov	eax, -1					; ffffffffH
	mov	rcx, QWORD PTR buffer_whole$[rsp]
	and	rcx, rax
	mov	rax, rcx
	mov	ecx, 16
	imul	rcx, 0
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+128], eax

; 110  : 	tbl->prdt[0].dbau = buffer_whole >> 32;

	mov	rax, QWORD PTR buffer_whole$[rsp]
	shr	rax, 32					; 00000020H
	mov	ecx, 16
	imul	rcx, 0
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+132], eax

; 111  : 	tbl->prdt[0].data_byte_count = 512 * count -1;

	mov	eax, DWORD PTR count$[rsp]
	imul	eax, 512				; 00000200H
	dec	eax
	mov	ecx, 16
	imul	rcx, 0
	and	eax, 4194303				; 003fffffH
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	ecx, DWORD PTR [rdx+rcx+140]
	and	ecx, -4194304				; ffc00000H
	or	ecx, eax
	mov	eax, ecx
	mov	ecx, 16
	imul	rcx, 0
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+140], eax

; 112  : 	tbl->prdt[0].i = 1;

	mov	eax, 16
	imul	rax, 0
	mov	rcx, QWORD PTR tbl$[rsp]
	mov	eax, DWORD PTR [rcx+rax+140]
	bts	eax, 31
	mov	ecx, 16
	imul	rcx, 0
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+140], eax

; 113  : 
; 114  : 
; 115  : 	FIS_REG_H2D *fis = (FIS_REG_H2D*)tbl->cmd_fis;

	mov	rax, QWORD PTR tbl$[rsp]
	mov	QWORD PTR fis$[rsp], rax

; 116  : 	fis->fis_type = FIS_TYPE_REG_H2D;

	mov	rax, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rax], 39			; 00000027H

; 117  : 	fis->c = 1;

	mov	rax, QWORD PTR fis$[rsp]
	movzx	eax, BYTE PTR [rax+1]
	or	al, 128					; 00000080H
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+1], al

; 118  : 	fis->command = ATA_CMD_READ_DMA_EXT;

	mov	rax, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rax+2], 37			; 00000025H

; 119  : 	fis->lba0 = lba & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+4], al

; 120  : 	fis->lba1 = (lba>>8) & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	shr	rax, 8
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+5], al

; 121  : 	fis->lba2 = (lba>>16) & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	shr	rax, 16
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+6], al

; 122  : 	fis->device = 1<<6;

	mov	rax, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rax+7], 64			; 00000040H

; 123  : 	fis->lba3 = (lba>>24) & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	shr	rax, 24
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+8], al

; 124  : 	fis->lba4 = (lba>>32) & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	shr	rax, 32					; 00000020H
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+9], al

; 125  : 	fis->lba5 = (lba>>40) & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	shr	rax, 40					; 00000028H
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+10], al

; 126  : 	fis->countl = count & 0xff;

	mov	eax, DWORD PTR count$[rsp]
	and	eax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+12], al

; 127  : 	fis->counth = (count >> 8) & 0xff;

	mov	eax, DWORD PTR count$[rsp]
	shr	eax, 8
	and	eax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+13], al
$LN9@ahci_disk_:

; 128  : 
; 129  : 	while((port->tfd & (ATA_SR_BSY  | ATA_SR_DRQ)) && spin < 1000000) {

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+32]
	and	eax, 136				; 00000088H
	test	eax, eax
	je	SHORT $LN8@ahci_disk_
	cmp	DWORD PTR spin$[rsp], 1000000		; 000f4240H
	jge	SHORT $LN8@ahci_disk_

; 130  : 		spin++;

	mov	eax, DWORD PTR spin$[rsp]
	inc	eax
	mov	DWORD PTR spin$[rsp], eax

; 131  : 	}

	jmp	SHORT $LN9@ahci_disk_
$LN8@ahci_disk_:

; 132  : 	if (spin==1000000)

	cmp	DWORD PTR spin$[rsp], 1000000		; 000f4240H
	jne	SHORT $LN7@ahci_disk_

; 133  : 		_debug_print_ ("[AHCI]:Port Hung\n");

	lea	rcx, OFFSET FLAT:$SG3839
	call	?_debug_print_@@YAXPEADZZ		; _debug_print_
$LN7@ahci_disk_:

; 134  : 
; 135  : 
; 136  : 	port->ci = 1<<command_slot;

	mov	eax, DWORD PTR command_slot$[rsp]
	mov	ecx, 1
	mov	DWORD PTR tv284[rsp], ecx
	movzx	ecx, al
	mov	eax, DWORD PTR tv284[rsp]
	shl	eax, cl
	mov	rcx, QWORD PTR port$[rsp]
	mov	DWORD PTR [rcx+56], eax
$LN6@ahci_disk_:

; 137  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN5@ahci_disk_

; 138  : 		if ((port->ci & (1<<command_slot)) == 0) 

	mov	eax, DWORD PTR command_slot$[rsp]
	mov	ecx, 1
	mov	DWORD PTR tv289[rsp], ecx
	movzx	ecx, al
	mov	eax, DWORD PTR tv289[rsp]
	shl	eax, cl
	mov	rcx, QWORD PTR port$[rsp]
	mov	ecx, DWORD PTR [rcx+56]
	and	ecx, eax
	mov	eax, ecx
	test	eax, eax
	jne	SHORT $LN4@ahci_disk_

; 139  : 			break;

	jmp	SHORT $LN5@ahci_disk_
$LN4@ahci_disk_:

; 140  : 		if (port->is & (1<<30))  {

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+16]
	and	eax, 1073741824				; 40000000H
	test	eax, eax
	je	SHORT $LN3@ahci_disk_

; 141  : 			_debug_print_ ("[AHCI]: Port error \r\n");

	lea	rcx, OFFSET FLAT:$SG3845
	call	?_debug_print_@@YAXPEADZZ		; _debug_print_

; 142  : 			break;

	jmp	SHORT $LN5@ahci_disk_
$LN3@ahci_disk_:

; 143  : 		}
; 144  : 	}

	jmp	SHORT $LN6@ahci_disk_
$LN5@ahci_disk_:
$LN2@ahci_disk_:

; 145  : 
; 146  : 	while (port->tfd & (ATA_SR_BSY | ATA_SR_DRQ))

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+32]
	and	eax, 136				; 00000088H
	test	eax, eax
	je	SHORT $LN1@ahci_disk_

; 147  : 		;

	jmp	SHORT $LN2@ahci_disk_
$LN1@ahci_disk_:

; 148  : 
; 149  : }

	add	rsp, 104				; 00000068H
	ret	0
?ahci_disk_read@@YAXPEAU_hba_port_@@_KIPEA_K@Z ENDP	; ahci_disk_read
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\ahci_disk.cpp
_TEXT	SEGMENT
fis$ = 32
spin$ = 40
command_slot$ = 44
tbl$ = 48
cmd_list$ = 56
tv286 = 64
tv281 = 68
buffer_whole$ = 72
i$ = 80
port$ = 112
lba$ = 120
count$ = 128
buffer$ = 136
?ahci_disk_write@@YAXPEAU_hba_port_@@_KIPEA_K@Z PROC	; ahci_disk_write

; 159  : void ahci_disk_write (HBA_PORT *port, uint64_t lba, uint32_t count, uint64_t *buffer) {

$LN10:
	mov	QWORD PTR [rsp+32], r9
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 104				; 00000068H

; 160  : 	int spin = 0;

	mov	DWORD PTR spin$[rsp], 0

; 161  : 	HBA_CMD_HEADER *cmd_list = (HBA_CMD_HEADER*)port->clb;

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax]
	mov	QWORD PTR cmd_list$[rsp], rax

; 162  : 	uint64_t buffer_whole = (uint64_t)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR buffer_whole$[rsp], rax

; 163  : 
; 164  : 	cmd_list->cfl = sizeof(FIS_REG_H2D)/sizeof(uint32_t);

	mov	rax, QWORD PTR cmd_list$[rsp]
	movzx	eax, BYTE PTR [rax]
	and	al, 224					; 000000e0H
	or	al, 5
	mov	rcx, QWORD PTR cmd_list$[rsp]
	mov	BYTE PTR [rcx], al

; 165  : 	cmd_list->w = 1;

	mov	rax, QWORD PTR cmd_list$[rsp]
	movzx	eax, BYTE PTR [rax]
	or	al, 64					; 00000040H
	mov	rcx, QWORD PTR cmd_list$[rsp]
	mov	BYTE PTR [rcx], al

; 166  : 	cmd_list->prdtl = 1;

	mov	eax, 1
	mov	rcx, QWORD PTR cmd_list$[rsp]
	mov	WORD PTR [rcx+2], ax

; 167  : 	
; 168  : 	uint32_t command_slot = ahci_disk_find_slot(port);

	mov	rcx, QWORD PTR port$[rsp]
	call	?ahci_disk_find_slot@@YAIPEAU_hba_port_@@@Z ; ahci_disk_find_slot
	mov	DWORD PTR command_slot$[rsp], eax

; 169  : 
; 170  : 	HBA_CMD_TABLE *tbl = (HBA_CMD_TABLE*)cmd_list[command_slot].ctba;

	mov	eax, DWORD PTR command_slot$[rsp]
	imul	rax, 32					; 00000020H
	mov	rcx, QWORD PTR cmd_list$[rsp]
	mov	eax, DWORD PTR [rcx+rax+8]
	mov	QWORD PTR tbl$[rsp], rax

; 171  : 	int i=0;

	mov	DWORD PTR i$[rsp], 0

; 172  : 	tbl->prdt[0].data_base_address = buffer_whole & 0xffffffff;

	mov	eax, -1					; ffffffffH
	mov	rcx, QWORD PTR buffer_whole$[rsp]
	and	rcx, rax
	mov	rax, rcx
	mov	ecx, 16
	imul	rcx, 0
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+128], eax

; 173  : 	tbl->prdt[0].dbau = buffer_whole >> 32;

	mov	rax, QWORD PTR buffer_whole$[rsp]
	shr	rax, 32					; 00000020H
	mov	ecx, 16
	imul	rcx, 0
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+132], eax

; 174  : 	tbl->prdt[0].data_byte_count = 512 * count -1;

	mov	eax, DWORD PTR count$[rsp]
	imul	eax, 512				; 00000200H
	dec	eax
	mov	ecx, 16
	imul	rcx, 0
	and	eax, 4194303				; 003fffffH
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	ecx, DWORD PTR [rdx+rcx+140]
	and	ecx, -4194304				; ffc00000H
	or	ecx, eax
	mov	eax, ecx
	mov	ecx, 16
	imul	rcx, 0
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+140], eax

; 175  : 	tbl->prdt[0].i = 1;

	mov	eax, 16
	imul	rax, 0
	mov	rcx, QWORD PTR tbl$[rsp]
	mov	eax, DWORD PTR [rcx+rax+140]
	bts	eax, 31
	mov	ecx, 16
	imul	rcx, 0
	mov	rdx, QWORD PTR tbl$[rsp]
	mov	DWORD PTR [rdx+rcx+140], eax

; 176  : 
; 177  : 	FIS_REG_H2D *fis = (FIS_REG_H2D*)tbl->cmd_fis;

	mov	rax, QWORD PTR tbl$[rsp]
	mov	QWORD PTR fis$[rsp], rax

; 178  : 	fis->fis_type = FIS_TYPE_REG_H2D;

	mov	rax, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rax], 39			; 00000027H

; 179  : 	fis->c = 1;

	mov	rax, QWORD PTR fis$[rsp]
	movzx	eax, BYTE PTR [rax+1]
	or	al, 128					; 00000080H
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+1], al

; 180  : 	fis->command = ATA_CMD_WRITE_DMA_EXT;

	mov	rax, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rax+2], 53			; 00000035H

; 181  : 	fis->lba0 = lba & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+4], al

; 182  : 	fis->lba1 = (lba>>8) & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	shr	rax, 8
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+5], al

; 183  : 	fis->lba2 = (lba>>16) & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	shr	rax, 16
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+6], al

; 184  : 	fis->device = 1<<6;

	mov	rax, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rax+7], 64			; 00000040H

; 185  : 	fis->lba3 = (lba>>24) & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	shr	rax, 24
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+8], al

; 186  : 	fis->lba4 = (lba>>32) & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	shr	rax, 32					; 00000020H
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+9], al

; 187  : 	fis->lba5 = (lba>>40) & 0xff;

	mov	rax, QWORD PTR lba$[rsp]
	shr	rax, 40					; 00000028H
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+10], al

; 188  : 	fis->countl = count & 0xff;

	mov	eax, DWORD PTR count$[rsp]
	and	eax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+12], al

; 189  : 	fis->counth = (count >> 8) & 0xff;

	mov	eax, DWORD PTR count$[rsp]
	shr	eax, 8
	and	eax, 255				; 000000ffH
	mov	rcx, QWORD PTR fis$[rsp]
	mov	BYTE PTR [rcx+13], al
$LN7@ahci_disk_:

; 190  : 
; 191  : 	while((port->tfd & (ATA_SR_BSY  | ATA_SR_DRQ)) && spin < 1000000) {

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+32]
	and	eax, 136				; 00000088H
	test	eax, eax
	je	SHORT $LN6@ahci_disk_
	cmp	DWORD PTR spin$[rsp], 1000000		; 000f4240H
	jge	SHORT $LN6@ahci_disk_

; 192  : 		spin++;

	mov	eax, DWORD PTR spin$[rsp]
	inc	eax
	mov	DWORD PTR spin$[rsp], eax

; 193  : 	}

	jmp	SHORT $LN7@ahci_disk_
$LN6@ahci_disk_:

; 194  : 	if (spin==1000000)

	cmp	DWORD PTR spin$[rsp], 1000000		; 000f4240H
	jne	SHORT $LN5@ahci_disk_

; 195  : 		printf ("[AHCI]:Port Hung\n");

	lea	rcx, OFFSET FLAT:$SG3872
	call	?printf@@YAXPEBDZZ			; printf
$LN5@ahci_disk_:

; 196  : 
; 197  : 	port->ci = 1<<command_slot;

	mov	eax, DWORD PTR command_slot$[rsp]
	mov	ecx, 1
	mov	DWORD PTR tv281[rsp], ecx
	movzx	ecx, al
	mov	eax, DWORD PTR tv281[rsp]
	shl	eax, cl
	mov	rcx, QWORD PTR port$[rsp]
	mov	DWORD PTR [rcx+56], eax
$LN4@ahci_disk_:

; 198  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN3@ahci_disk_

; 199  : 		if ((port->ci & (1<<command_slot)) == 0) 

	mov	eax, DWORD PTR command_slot$[rsp]
	mov	ecx, 1
	mov	DWORD PTR tv286[rsp], ecx
	movzx	ecx, al
	mov	eax, DWORD PTR tv286[rsp]
	shl	eax, cl
	mov	rcx, QWORD PTR port$[rsp]
	mov	ecx, DWORD PTR [rcx+56]
	and	ecx, eax
	mov	eax, ecx
	test	eax, eax
	jne	SHORT $LN2@ahci_disk_

; 200  : 			break;

	jmp	SHORT $LN3@ahci_disk_
$LN2@ahci_disk_:

; 201  : 		if (port->is & (1<<30))  {

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+16]
	and	eax, 1073741824				; 40000000H
	test	eax, eax
	je	SHORT $LN1@ahci_disk_

; 202  : 			_debug_print_ ("[AHCI]: Port error \r\n");

	lea	rcx, OFFSET FLAT:$SG3878
	call	?_debug_print_@@YAXPEADZZ		; _debug_print_

; 203  : 			break;

	jmp	SHORT $LN3@ahci_disk_
$LN1@ahci_disk_:

; 204  : 		}
; 205  : 	}

	jmp	SHORT $LN4@ahci_disk_
$LN3@ahci_disk_:

; 206  : }

	add	rsp, 104				; 00000068H
	ret	0
?ahci_disk_write@@YAXPEAU_hba_port_@@_KIPEA_K@Z ENDP	; ahci_disk_write
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\ahci_disk.cpp
_TEXT	SEGMENT
cold_presence$ = 32
i$1 = 36
i$2 = 40
phys$ = 48
current_slot$ = 56
cmd_list$ = 64
addr$ = 72
ide_buf$ = 80
fis_dev$ = 88
ata_device_name$ = 96
port$ = 160
?ahci_disk_initialize@@YAXPEAU_hba_port_@@@Z PROC	; ahci_disk_initialize

; 275  : void ahci_disk_initialize (HBA_PORT *port) {

$LN10:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 152				; 00000098H

; 276  : 
; 277  : 	/* stop the DMA engine */
; 278  : 	ahci_disk_stop_cmd(port);

	mov	rcx, QWORD PTR port$[rsp]
	call	?ahci_disk_stop_cmd@@YAXPEAU_hba_port_@@@Z ; ahci_disk_stop_cmd

; 279  : 
; 280  : 	sata_drive_port = port;

	mov	rax, QWORD PTR port$[rsp]
	mov	QWORD PTR ?sata_drive_port@@3PEAU_hba_port_@@EA, rax ; sata_drive_port

; 281  : 
; 282  : 
; 283  : 
; 284  : 	uint64_t phys;
; 285  : 
; 286  : 	/* Allocate command list */
; 287  : 	phys = (uint64_t)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR phys$[rsp], rax

; 288  : 	port->clb = phys & 0xffffffff;

	mov	eax, -1					; ffffffffH
	mov	rcx, QWORD PTR phys$[rsp]
	and	rcx, rax
	mov	rax, rcx
	mov	rcx, QWORD PTR port$[rsp]
	mov	DWORD PTR [rcx], eax

; 289  : 	port->clbu = phys >> 32;

	mov	rax, QWORD PTR phys$[rsp]
	shr	rax, 32					; 00000020H
	mov	rcx, QWORD PTR port$[rsp]
	mov	DWORD PTR [rcx+4], eax

; 290  : 
; 291  : 	HBA_CMD_HEADER *cmd_list = (HBA_CMD_HEADER*)phys;

	mov	rax, QWORD PTR phys$[rsp]
	mov	QWORD PTR cmd_list$[rsp], rax

; 292  : 	memset((void*)phys, 0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR phys$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 293  : 
; 294  : 	/* Allocate FIS */
; 295  : 	phys = (uint64_t)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR phys$[rsp], rax

; 296  : 	port->fb = phys & 0xffffffff;

	mov	eax, -1					; ffffffffH
	mov	rcx, QWORD PTR phys$[rsp]
	and	rcx, rax
	mov	rax, rcx
	mov	rcx, QWORD PTR port$[rsp]
	mov	DWORD PTR [rcx+8], eax

; 297  : 	port->fbu = (phys >> 32);

	mov	rax, QWORD PTR phys$[rsp]
	shr	rax, 32					; 00000020H
	mov	rcx, QWORD PTR port$[rsp]
	mov	DWORD PTR [rcx+12], eax

; 298  : 
; 299  : 	HBA_FIS *fis_dev = (HBA_FIS*)phys;

	mov	rax, QWORD PTR phys$[rsp]
	mov	QWORD PTR fis_dev$[rsp], rax

; 300  : 	memset((void*)phys, 0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR phys$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 301  : 
; 302  : 	uint8_t cold_presence = port->cmd & (1<<20);

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+24]
	and	eax, 1048576				; 00100000H
	mov	BYTE PTR cold_presence$[rsp], al

; 303  : 	if (cold_presence) {

	movzx	eax, BYTE PTR cold_presence$[rsp]
	test	eax, eax
	je	SHORT $LN7@ahci_disk_

; 304  : 		printf ("[AHCI]: Port Supports cold presence %d\n",cold_presence);

	movzx	eax, BYTE PTR cold_presence$[rsp]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG3926
	call	?printf@@YAXPEBDZZ			; printf
$LN7@ahci_disk_:

; 305  : 	}
; 306  : 
; 307  : 	for (int i = 0; i < 31; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN6@ahci_disk_
$LN5@ahci_disk_:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN6@ahci_disk_:
	cmp	DWORD PTR i$1[rsp], 31
	jge	$LN4@ahci_disk_

; 308  : 		cmd_list[i].prdtl = 1;

	movsxd	rax, DWORD PTR i$1[rsp]
	imul	rax, 32					; 00000020H
	mov	ecx, 1
	mov	rdx, QWORD PTR cmd_list$[rsp]
	mov	WORD PTR [rdx+rax+2], cx

; 309  : 		phys = (uint64_t)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR phys$[rsp], rax

; 310  : 		cmd_list[i].ctba = phys & 0xffffffff;

	mov	eax, -1					; ffffffffH
	mov	rcx, QWORD PTR phys$[rsp]
	and	rcx, rax
	mov	rax, rcx
	movsxd	rcx, DWORD PTR i$1[rsp]
	imul	rcx, 32					; 00000020H
	mov	rdx, QWORD PTR cmd_list$[rsp]
	mov	DWORD PTR [rdx+rcx+8], eax

; 311  : 		cmd_list[i].ctbau = phys >> 32;

	mov	rax, QWORD PTR phys$[rsp]
	shr	rax, 32					; 00000020H
	movsxd	rcx, DWORD PTR i$1[rsp]
	imul	rcx, 32					; 00000020H
	mov	rdx, QWORD PTR cmd_list$[rsp]
	mov	DWORD PTR [rdx+rcx+12], eax

; 312  : 		cmd_list[i].p = 1;

	movsxd	rax, DWORD PTR i$1[rsp]
	imul	rax, 32					; 00000020H
	mov	rcx, QWORD PTR cmd_list$[rsp]
	movzx	eax, BYTE PTR [rcx+rax]
	or	al, 128					; 00000080H
	movsxd	rcx, DWORD PTR i$1[rsp]
	imul	rcx, 32					; 00000020H
	mov	rdx, QWORD PTR cmd_list$[rsp]
	mov	BYTE PTR [rdx+rcx], al

; 313  : 		cmd_list[i].cfl = 0x10;

	movsxd	rax, DWORD PTR i$1[rsp]
	imul	rax, 32					; 00000020H
	mov	rcx, QWORD PTR cmd_list$[rsp]
	movzx	eax, BYTE PTR [rcx+rax]
	and	al, 224					; 000000e0H
	or	al, 16
	movsxd	rcx, DWORD PTR i$1[rsp]
	imul	rcx, 32					; 00000020H
	mov	rdx, QWORD PTR cmd_list$[rsp]
	mov	BYTE PTR [rdx+rcx], al

; 314  : 		memset((void*)phys, 0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR phys$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 315  : 	}

	jmp	$LN5@ahci_disk_
$LN4@ahci_disk_:

; 316  : 
; 317  : 	port->serr = 0xffffffff;

	mov	rax, QWORD PTR port$[rsp]
	mov	DWORD PTR [rax+48], -1			; ffffffffH

; 318  : 
; 319  : 	port->cmd &= ~HBA_PX_CMD_ICC;

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+24]
	and	eax, 268435455				; 0fffffffH
	mov	rcx, QWORD PTR port$[rsp]
	mov	DWORD PTR [rcx+24], eax

; 320  : 	port->cmd |= PX_CMD_POD | PX_CMD_SUD | HBA_PX_CMD_ICC_ACTIVE;

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+24]
	or	eax, 268435462				; 10000006H
	mov	rcx, QWORD PTR port$[rsp]
	mov	DWORD PTR [rcx+24], eax

; 321  : 
; 322  : 
; 323  : 	port->ie = (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) |
; 324  : 		(1<<7) | (1<<22) | (1<<23) | (1<<24) | (1<<26) | (1<<27) | (1<<28) | 
; 325  : 		(1<<29) | (1<<30) | (1<<31);

	mov	rax, QWORD PTR port$[rsp]
	mov	DWORD PTR [rax+20], -37748481		; fdc000ffH

; 326  : 
; 327  : 	/* start the command DMA engine */
; 328  : 	ahci_disk_start_cmd(port);

	mov	rcx, QWORD PTR port$[rsp]
	call	?ahci_disk_start_cmd@@YAXPEAU_hba_port_@@@Z ; ahci_disk_start_cmd

; 329  : 
; 330  : 	uint8_t current_slot = port->cmd & (1<<8);

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+24]
	and	eax, 256				; 00000100H
	mov	BYTE PTR current_slot$[rsp], al

; 331  : 
; 332  : 	uint64_t *addr = (uint64_t*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR addr$[rsp], rax

; 333  : 	memset(addr,0,4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR addr$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 334  : 	ahci_disk_identify(port,0,1,addr);

	mov	r9, QWORD PTR addr$[rsp]
	mov	r8d, 1
	xor	edx, edx
	mov	rcx, QWORD PTR port$[rsp]
	call	?ahci_disk_identify@@YAXPEAU_hba_port_@@_KIPEA_K@Z ; ahci_disk_identify

; 335  : 	char ata_device_name[40];
; 336  : 	uint8_t *ide_buf = (uint8_t*)addr;

	mov	rax, QWORD PTR addr$[rsp]
	mov	QWORD PTR ide_buf$[rsp], rax

; 337  : 	for (int i= 0; i < 40; i += 2)

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN3@ahci_disk_
$LN2@ahci_disk_:
	mov	eax, DWORD PTR i$2[rsp]
	add	eax, 2
	mov	DWORD PTR i$2[rsp], eax
$LN3@ahci_disk_:
	cmp	DWORD PTR i$2[rsp], 40			; 00000028H
	jge	SHORT $LN1@ahci_disk_

; 338  : 	{
; 339  : 		ata_device_name[i] = ide_buf[54 + i + 1];

	mov	eax, DWORD PTR i$2[rsp]
	add	eax, 55					; 00000037H
	cdqe
	movsxd	rcx, DWORD PTR i$2[rsp]
	mov	rdx, QWORD PTR ide_buf$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR ata_device_name$[rsp+rcx], al

; 340  : 		ata_device_name[i + 1] = ide_buf[54 + i];

	mov	eax, DWORD PTR i$2[rsp]
	add	eax, 54					; 00000036H
	cdqe
	mov	ecx, DWORD PTR i$2[rsp]
	inc	ecx
	movsxd	rcx, ecx
	mov	rdx, QWORD PTR ide_buf$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR ata_device_name$[rsp+rcx], al

; 341  : 	}

	jmp	SHORT $LN2@ahci_disk_
$LN1@ahci_disk_:

; 342  : 	printf ("[AHCI]: Model -> %s\n", ata_device_name);

	lea	rdx, QWORD PTR ata_device_name$[rsp]
	lea	rcx, OFFSET FLAT:$SG3943
	call	?printf@@YAXPEBDZZ			; printf

; 343  : 
; 344  : }

	add	rsp, 152				; 00000098H
	ret	0
?ahci_disk_initialize@@YAXPEAU_hba_port_@@@Z ENDP	; ahci_disk_initialize
_TEXT	ENDS
END
