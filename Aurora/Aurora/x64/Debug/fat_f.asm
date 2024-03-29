; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3692	DB	'FAT32: Creating a file ', 0dH, 0aH, 00H
	ORG $+6
$SG3711	DB	'FAT32: file created at entry-> %d ', 0dH, 0aH, 00H
	ORG $+3
$SG3735	DB	'[FAT32]: cluster -> %d flushed to disk ', 0dH, 0aH, 00H
	ORG $+6
$SG3750	DB	'[FAT32]: Writing to file, required clusters -> %d ', 0dH
	DB	0aH, 00H
CONST	ENDS
PUBLIC	?fat32_make_file@@YAPEAU_vfs_node_@@IPEADI@Z	; fat32_make_file
PUBLIC	?fat32_write_file@@YAXPEAU_vfs_node_@@PEAEI@Z	; fat32_write_file
PUBLIC	?fat32_write_content@@YAXIPEAEI@Z		; fat32_write_content
EXTRN	strcpy:PROC
EXTRN	memset:PROC
EXTRN	memcpy:PROC
EXTRN	?fat32_to_dos_file_name@@YAXPEBDPEADI@Z:PROC	; fat32_to_dos_file_name
EXTRN	?fat32_find_free_cluster@@YAIXZ:PROC		; fat32_find_free_cluster
EXTRN	?fat32_alloc_cluster@@YAXHI@Z:PROC		; fat32_alloc_cluster
EXTRN	?fat32_get_root_cluster@@YAIXZ:PROC		; fat32_get_root_cluster
EXTRN	?fat32_get_sector_per_cluster@@YA_KXZ:PROC	; fat32_get_sector_per_cluster
EXTRN	AuPmmngrAlloc:PROC
EXTRN	AuPmmngrFree:PROC
EXTRN	malloc:PROC
EXTRN	free:PROC
EXTRN	?ahci_disk_write@@YAXPEAU_hba_port_@@_KIPEA_K@Z:PROC ; ahci_disk_write
EXTRN	?ahci_disk_read@@YAXPEAU_hba_port_@@_KIPEA_K@Z:PROC ; ahci_disk_read
EXTRN	?ahci_disk_get_port@@YAPEAU_hba_port_@@XZ:PROC	; ahci_disk_get_port
EXTRN	_debug_print_:PROC
EXTRN	?fat32_read_fat@@YAII@Z:PROC			; fat32_read_fat
EXTRN	?fat32_clear_cluster@@YAXI@Z:PROC		; fat32_clear_cluster
EXTRN	?cluster_to_sector32@@YA_K_K@Z:PROC		; cluster_to_sector32
EXTRN	?fat32_format_date@@YAGXZ:PROC			; fat32_format_date
EXTRN	?fat32_format_time@@YAGXZ:PROC			; fat32_format_time
pdata	SEGMENT
$pdata$?fat32_make_file@@YAPEAU_vfs_node_@@IPEADI@Z DD imagerel $LN14
	DD	imagerel $LN14+844
	DD	imagerel $unwind$?fat32_make_file@@YAPEAU_vfs_node_@@IPEADI@Z
$pdata$?fat32_write_file@@YAXPEAU_vfs_node_@@PEAEI@Z DD imagerel $LN10
	DD	imagerel $LN10+252
	DD	imagerel $unwind$?fat32_write_file@@YAXPEAU_vfs_node_@@PEAEI@Z
$pdata$?fat32_write_content@@YAXIPEAEI@Z DD imagerel $LN14
	DD	imagerel $LN14+344
	DD	imagerel $unwind$?fat32_write_content@@YAXIPEAEI@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?fat32_make_file@@YAPEAU_vfs_node_@@IPEADI@Z DD 021501H
	DD	0110115H
$unwind$?fat32_write_file@@YAXPEAU_vfs_node_@@PEAEI@Z DD 011301H
	DD	08213H
$unwind$?fat32_write_content@@YAXIPEAEI@Z DD 011201H
	DD	0a212H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\fat\fat_f.cpp
_TEXT	SEGMENT
cluster$ = 32
i$1 = 36
required_cluster$ = 40
i$2 = 44
one_cluster_sz$ = 48
ahci_buff$ = 56
tv84 = 64
tv87 = 72
first_cluster$ = 96
buffer$ = 104
length$ = 112
?fat32_write_content@@YAXIPEAEI@Z PROC			; fat32_write_content

; 137  : void fat32_write_content (uint32_t first_cluster, uint8_t *buffer, uint32_t length) {

$LN14:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 88					; 00000058H

; 138  : 
; 139  : 	uint32_t one_cluster_sz = 512* fat32_get_sector_per_cluster();

	call	?fat32_get_sector_per_cluster@@YA_KXZ	; fat32_get_sector_per_cluster
	imul	rax, 512				; 00000200H
	mov	DWORD PTR one_cluster_sz$[rsp], eax

; 140  : 
; 141  : 	uint32_t required_cluster = 0;

	mov	DWORD PTR required_cluster$[rsp], 0

; 142  : 	if (length > one_cluster_sz) {

	mov	eax, DWORD PTR one_cluster_sz$[rsp]
	cmp	DWORD PTR length$[rsp], eax
	jbe	SHORT $LN11@fat32_writ

; 143  : 		for (int i = 0; i < length / one_cluster_sz; i++)

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN10@fat32_writ
$LN9@fat32_writ:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN10@fat32_writ:
	xor	edx, edx
	mov	eax, DWORD PTR length$[rsp]
	div	DWORD PTR one_cluster_sz$[rsp]
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN8@fat32_writ

; 144  : 			required_cluster++;

	mov	eax, DWORD PTR required_cluster$[rsp]
	inc	eax
	mov	DWORD PTR required_cluster$[rsp], eax
	jmp	SHORT $LN9@fat32_writ
$LN8@fat32_writ:
$LN11@fat32_writ:

; 145  : 	}
; 146  : 
; 147  : 	uint64_t* ahci_buff = (uint64_t*)AuPmmngrAlloc();

	call	AuPmmngrAlloc
	mov	QWORD PTR ahci_buff$[rsp], rax

; 148  : 	memset(ahci_buff, 0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR ahci_buff$[rsp]
	call	memset

; 149  : 	
; 150  : 
; 151  : 	uint32_t cluster = first_cluster;

	mov	eax, DWORD PTR first_cluster$[rsp]
	mov	DWORD PTR cluster$[rsp], eax

; 152  : 	
; 153  : 	for (int i = 0; i < required_cluster; i++) {

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN7@fat32_writ
$LN6@fat32_writ:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN7@fat32_writ:
	mov	eax, DWORD PTR required_cluster$[rsp]
	cmp	DWORD PTR i$2[rsp], eax
	jae	$LN5@fat32_writ

; 154  : 		if (cluster != FAT_EOC_MARK || cluster != FAT_BAD_CLUSTER) {

	cmp	DWORD PTR cluster$[rsp], -8		; fffffff8H
	jne	SHORT $LN3@fat32_writ
	cmp	DWORD PTR cluster$[rsp], -9		; fffffff7H
	je	SHORT $LN4@fat32_writ
$LN3@fat32_writ:

; 155  : 			memcpy (ahci_buff,buffer,4096);

	mov	r8d, 4096				; 00001000H
	mov	rdx, QWORD PTR buffer$[rsp]
	mov	rcx, QWORD PTR ahci_buff$[rsp]
	call	memcpy

; 156  : 			ahci_disk_write (ahci_disk_get_port(),cluster_to_sector32(cluster),fat32_get_sector_per_cluster(),ahci_buff);

	call	?fat32_get_sector_per_cluster@@YA_KXZ	; fat32_get_sector_per_cluster
	mov	QWORD PTR tv84[rsp], rax
	mov	ecx, DWORD PTR cluster$[rsp]
	call	?cluster_to_sector32@@YA_K_K@Z		; cluster_to_sector32
	mov	QWORD PTR tv87[rsp], rax
	call	?ahci_disk_get_port@@YAPEAU_hba_port_@@XZ ; ahci_disk_get_port
	mov	r9, QWORD PTR ahci_buff$[rsp]
	mov	rcx, QWORD PTR tv84[rsp]
	mov	r8d, ecx
	mov	rcx, QWORD PTR tv87[rsp]
	mov	rdx, rcx
	mov	rcx, rax
	call	?ahci_disk_write@@YAXPEAU_hba_port_@@_KIPEA_K@Z ; ahci_disk_write

; 157  : 			_debug_print_ ("[FAT32]: cluster -> %d flushed to disk \r\n", cluster);

	mov	edx, DWORD PTR cluster$[rsp]
	lea	rcx, OFFSET FLAT:$SG3735
	call	_debug_print_
$LN4@fat32_writ:

; 158  : 		}
; 159  : 		cluster = fat32_read_fat(cluster);

	mov	ecx, DWORD PTR cluster$[rsp]
	call	?fat32_read_fat@@YAII@Z			; fat32_read_fat
	mov	DWORD PTR cluster$[rsp], eax

; 160  : 		if (cluster == FAT_EOC_MARK || cluster == FAT_BAD_CLUSTER)

	cmp	DWORD PTR cluster$[rsp], -8		; fffffff8H
	je	SHORT $LN1@fat32_writ
	cmp	DWORD PTR cluster$[rsp], -9		; fffffff7H
	jne	SHORT $LN2@fat32_writ
$LN1@fat32_writ:

; 161  : 			break;

	jmp	SHORT $LN5@fat32_writ
$LN2@fat32_writ:

; 162  : 		buffer += 4096;

	mov	rax, QWORD PTR buffer$[rsp]
	add	rax, 4096				; 00001000H
	mov	QWORD PTR buffer$[rsp], rax

; 163  : 	}

	jmp	$LN6@fat32_writ
$LN5@fat32_writ:

; 164  : 
; 165  : 	AuPmmngrFree(ahci_buff);

	mov	rcx, QWORD PTR ahci_buff$[rsp]
	call	AuPmmngrFree

; 166  : }

	add	rsp, 88					; 00000058H
	ret	0
?fat32_write_content@@YAXIPEAEI@Z ENDP			; fat32_write_content
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\fat\fat_f.cpp
_TEXT	SEGMENT
required_cluster$ = 32
cluster$ = 36
i$1 = 40
i$2 = 44
cluster_next$ = 48
one_cluster_sz$ = 52
file$ = 80
buffer$ = 88
length$ = 96
?fat32_write_file@@YAXPEAU_vfs_node_@@PEAEI@Z PROC	; fat32_write_file

; 173  : void fat32_write_file (vfs_node_t *file, uint8_t* buffer, uint32_t length) {

$LN10:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 174  : 
; 175  : 	uint32_t one_cluster_sz = 512* fat32_get_sector_per_cluster();

	call	?fat32_get_sector_per_cluster@@YA_KXZ	; fat32_get_sector_per_cluster
	imul	rax, 512				; 00000200H
	mov	DWORD PTR one_cluster_sz$[rsp], eax

; 176  : 
; 177  : 	uint32_t required_cluster = 0;

	mov	DWORD PTR required_cluster$[rsp], 0

; 178  : 	if (length > one_cluster_sz) {

	mov	eax, DWORD PTR one_cluster_sz$[rsp]
	cmp	DWORD PTR length$[rsp], eax
	jbe	SHORT $LN7@fat32_writ

; 179  : 		for (int i = 0; i < length / one_cluster_sz; i++)

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN6@fat32_writ
$LN5@fat32_writ:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN6@fat32_writ:
	xor	edx, edx
	mov	eax, DWORD PTR length$[rsp]
	div	DWORD PTR one_cluster_sz$[rsp]
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN4@fat32_writ

; 180  : 			required_cluster++;

	mov	eax, DWORD PTR required_cluster$[rsp]
	inc	eax
	mov	DWORD PTR required_cluster$[rsp], eax
	jmp	SHORT $LN5@fat32_writ
$LN4@fat32_writ:
$LN7@fat32_writ:

; 181  : 	}
; 182  : 
; 183  : 	_debug_print_ ("[FAT32]: Writing to file, required clusters -> %d \r\n", required_cluster);

	mov	edx, DWORD PTR required_cluster$[rsp]
	lea	rcx, OFFSET FLAT:$SG3750
	call	_debug_print_

; 184  : 
; 185  : 	uint32_t cluster = file->current;

	mov	rax, QWORD PTR file$[rsp]
	mov	eax, DWORD PTR [rax+44]
	mov	DWORD PTR cluster$[rsp], eax

; 186  : 
; 187  : 	uint32_t cluster_next = 0;

	mov	DWORD PTR cluster_next$[rsp], 0

; 188  : 	for (int i = 0; i < required_cluster-1; i++) {

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN3@fat32_writ
$LN2@fat32_writ:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN3@fat32_writ:
	mov	eax, DWORD PTR required_cluster$[rsp]
	dec	eax
	cmp	DWORD PTR i$2[rsp], eax
	jae	SHORT $LN1@fat32_writ

; 189  : 		cluster_next = fat32_find_free_cluster();

	call	?fat32_find_free_cluster@@YAIXZ		; fat32_find_free_cluster
	mov	DWORD PTR cluster_next$[rsp], eax

; 190  : 		fat32_alloc_cluster(cluster,cluster_next);

	mov	edx, DWORD PTR cluster_next$[rsp]
	mov	ecx, DWORD PTR cluster$[rsp]
	call	?fat32_alloc_cluster@@YAXHI@Z		; fat32_alloc_cluster

; 191  : 		fat32_clear_cluster (cluster);

	mov	ecx, DWORD PTR cluster$[rsp]
	call	?fat32_clear_cluster@@YAXI@Z		; fat32_clear_cluster

; 192  : 		cluster = cluster_next;

	mov	eax, DWORD PTR cluster_next$[rsp]
	mov	DWORD PTR cluster$[rsp], eax

; 193  : 	}

	jmp	SHORT $LN2@fat32_writ
$LN1@fat32_writ:

; 194  : 	fat32_alloc_cluster (cluster,FAT_EOC_MARK);

	mov	edx, -8					; fffffff8H
	mov	ecx, DWORD PTR cluster$[rsp]
	call	?fat32_alloc_cluster@@YAXHI@Z		; fat32_alloc_cluster

; 195  : 
; 196  : 	fat32_write_content (file->current,buffer, length);

	mov	r8d, DWORD PTR length$[rsp]
	mov	rdx, QWORD PTR buffer$[rsp]
	mov	rax, QWORD PTR file$[rsp]
	mov	ecx, DWORD PTR [rax+44]
	call	?fat32_write_content@@YAXIPEAEI@Z	; fat32_write_content

; 197  : }

	add	rsp, 72					; 00000048H
	ret	0
?fat32_write_file@@YAXPEAU_vfs_node_@@PEAEI@Z ENDP	; fat32_write_file
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\fs\fat\fat_f.cpp
_TEXT	SEGMENT
dirent$1 = 32
is_parent_root$ = 40
j$2 = 44
file$ = 48
i$3 = 56
cluster$4 = 60
buff$ = 64
fname$ = 72
tv83 = 88
buffer$5 = 96
tv175 = 104
tv95 = 112
parent_clust$ = 144
filename$ = 152
size$ = 160
?fat32_make_file@@YAPEAU_vfs_node_@@IPEADI@Z PROC	; fat32_make_file

; 61   : vfs_node_t* fat32_make_file (uint32_t parent_clust, char* filename, uint32_t size) {

$LN14:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 136				; 00000088H

; 62   : 	vfs_node_t *file = (vfs_node_t*)malloc(sizeof(vfs_node_t));

	mov	ecx, 112				; 00000070H
	call	malloc
	mov	QWORD PTR file$[rsp], rax

; 63   : 	memset(file, 0, sizeof(vfs_node_t));

	mov	r8d, 112				; 00000070H
	xor	edx, edx
	mov	rcx, QWORD PTR file$[rsp]
	call	memset

; 64   : 
; 65   : 
; 66   : 	uint64_t* buff = (uint64_t*)AuPmmngrAlloc();

	call	AuPmmngrAlloc
	mov	QWORD PTR buff$[rsp], rax

; 67   : 	memset(buff, 0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR buff$[rsp]
	call	memset

; 68   : 
; 69   : 	bool is_parent_root = false;

	mov	BYTE PTR is_parent_root$[rsp], 0

; 70   : 
; 71   : 	_debug_print_ ("FAT32: Creating a file \r\n");

	lea	rcx, OFFSET FLAT:$SG3692
	call	_debug_print_

; 72   : 
; 73   : 	char fname[11];
; 74   : 	memset(fname,0,11);

	mov	r8d, 11
	xor	edx, edx
	lea	rcx, QWORD PTR fname$[rsp]
	call	memset

; 75   : 	fat32_to_dos_file_name (filename, fname, 11);

	mov	r8d, 11
	lea	rdx, QWORD PTR fname$[rsp]
	mov	rcx, QWORD PTR filename$[rsp]
	call	?fat32_to_dos_file_name@@YAXPEBDPEADI@Z	; fat32_to_dos_file_name

; 76   : 
; 77   : 	if (parent_clust == fat32_get_root_cluster ())

	call	?fat32_get_root_cluster@@YAIXZ		; fat32_get_root_cluster
	cmp	DWORD PTR parent_clust$[rsp], eax
	jne	SHORT $LN11@fat32_make

; 78   : 		is_parent_root = true;

	mov	BYTE PTR is_parent_root$[rsp], 1
$LN11@fat32_make:
$search$15:

; 79   : 
; 80   : search:
; 81   : 	for (int j = 0; j < fat32_get_sector_per_cluster(); j++) {

	mov	DWORD PTR j$2[rsp], 0
	jmp	SHORT $LN10@fat32_make
$LN9@fat32_make:
	mov	eax, DWORD PTR j$2[rsp]
	inc	eax
	mov	DWORD PTR j$2[rsp], eax
$LN10@fat32_make:
	movsxd	rax, DWORD PTR j$2[rsp]
	mov	QWORD PTR tv83[rsp], rax
	call	?fat32_get_sector_per_cluster@@YA_KXZ	; fat32_get_sector_per_cluster
	mov	rcx, QWORD PTR tv83[rsp]
	cmp	rcx, rax
	jae	$LN8@fat32_make

; 82   : 		memset(buff,0,4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR buff$[rsp]
	call	memset

; 83   : 		ahci_disk_read (ahci_disk_get_port(), cluster_to_sector32(parent_clust) + j, 1,buff);

	mov	eax, DWORD PTR parent_clust$[rsp]
	mov	ecx, eax
	call	?cluster_to_sector32@@YA_K_K@Z		; cluster_to_sector32
	movsxd	rcx, DWORD PTR j$2[rsp]
	add	rax, rcx
	mov	QWORD PTR tv95[rsp], rax
	call	?ahci_disk_get_port@@YAPEAU_hba_port_@@XZ ; ahci_disk_get_port
	mov	r9, QWORD PTR buff$[rsp]
	mov	r8d, 1
	mov	rcx, QWORD PTR tv95[rsp]
	mov	rdx, rcx
	mov	rcx, rax
	call	?ahci_disk_read@@YAXPEAU_hba_port_@@_KIPEA_K@Z ; ahci_disk_read

; 84   : 
; 85   : 		unsigned char* buffer = (unsigned char*)buff;

	mov	rax, QWORD PTR buff$[rsp]
	mov	QWORD PTR buffer$5[rsp], rax

; 86   : 		fat32_dir *dirent = (fat32_dir*)buff;

	mov	rax, QWORD PTR buff$[rsp]
	mov	QWORD PTR dirent$1[rsp], rax

; 87   : 		for (int i = 0; i < 16; i++) {

	mov	DWORD PTR i$3[rsp], 0
	jmp	SHORT $LN7@fat32_make
$LN6@fat32_make:
	mov	eax, DWORD PTR i$3[rsp]
	inc	eax
	mov	DWORD PTR i$3[rsp], eax
$LN7@fat32_make:
	cmp	DWORD PTR i$3[rsp], 16
	jge	$LN5@fat32_make

; 88   : 			if (dirent->filename[0] == 0x00 || dirent->filename[0] == 0xE5) {

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR dirent$1[rsp]
	movzx	eax, BYTE PTR [rcx+rax]
	test	eax, eax
	je	SHORT $LN3@fat32_make
	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR dirent$1[rsp]
	movzx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 229				; 000000e5H
	jne	$LN4@fat32_make
$LN3@fat32_make:

; 89   : 				memcpy (dirent->filename, fname,11);

	mov	rax, QWORD PTR dirent$1[rsp]
	mov	r8d, 11
	lea	rdx, QWORD PTR fname$[rsp]
	mov	rcx, rax
	call	memcpy

; 90   : 
; 91   : 				uint32_t cluster = fat32_find_free_cluster();

	call	?fat32_find_free_cluster@@YAIXZ		; fat32_find_free_cluster
	mov	DWORD PTR cluster$4[rsp], eax

; 92   : 				fat32_alloc_cluster (cluster,FAT_EOC_MARK);

	mov	edx, -8					; fffffff8H
	mov	ecx, DWORD PTR cluster$4[rsp]
	call	?fat32_alloc_cluster@@YAXHI@Z		; fat32_alloc_cluster

; 93   : 				fat32_clear_cluster(cluster);

	mov	ecx, DWORD PTR cluster$4[rsp]
	call	?fat32_clear_cluster@@YAXI@Z		; fat32_clear_cluster

; 94   : 
; 95   : 				dirent->attrib = ATTRIBUTE_ARCHIVE;

	mov	rax, QWORD PTR dirent$1[rsp]
	mov	BYTE PTR [rax+11], 32			; 00000020H

; 96   : 				dirent->first_cluster = cluster & 0x0000FFFF;

	mov	eax, DWORD PTR cluster$4[rsp]
	and	eax, 65535				; 0000ffffH
	mov	rcx, QWORD PTR dirent$1[rsp]
	mov	WORD PTR [rcx+26], ax

; 97   : 				dirent->first_cluster_hi_bytes = (cluster & 0x0FFF0000)>>16;

	mov	eax, DWORD PTR cluster$4[rsp]
	and	eax, 268369920				; 0fff0000H
	shr	eax, 16
	mov	rcx, QWORD PTR dirent$1[rsp]
	mov	WORD PTR [rcx+20], ax

; 98   : 				dirent->date_created = fat32_format_date();

	call	?fat32_format_date@@YAGXZ		; fat32_format_date
	mov	rcx, QWORD PTR dirent$1[rsp]
	mov	WORD PTR [rcx+16], ax

; 99   : 				dirent->time_created = fat32_format_time();

	call	?fat32_format_time@@YAGXZ		; fat32_format_time
	mov	rcx, QWORD PTR dirent$1[rsp]
	mov	WORD PTR [rcx+14], ax

; 100  : 				dirent->last_wrt_date = dirent->date_created;

	mov	rax, QWORD PTR dirent$1[rsp]
	mov	rcx, QWORD PTR dirent$1[rsp]
	movzx	ecx, WORD PTR [rcx+16]
	mov	WORD PTR [rax+24], cx

; 101  : 				dirent->last_wrt_time = dirent->time_created;

	mov	rax, QWORD PTR dirent$1[rsp]
	mov	rcx, QWORD PTR dirent$1[rsp]
	movzx	ecx, WORD PTR [rcx+14]
	mov	WORD PTR [rax+22], cx

; 102  : 				dirent->date_last_accessed = 0;

	xor	eax, eax
	mov	rcx, QWORD PTR dirent$1[rsp]
	mov	WORD PTR [rcx+18], ax

; 103  : 				dirent->file_size = size;

	mov	rax, QWORD PTR dirent$1[rsp]
	mov	ecx, DWORD PTR size$[rsp]
	mov	DWORD PTR [rax+28], ecx

; 104  : 
; 105  : 			    ahci_disk_write (ahci_disk_get_port(),cluster_to_sector32(parent_clust) + j,1,buff);

	mov	eax, DWORD PTR parent_clust$[rsp]
	mov	ecx, eax
	call	?cluster_to_sector32@@YA_K_K@Z		; cluster_to_sector32
	movsxd	rcx, DWORD PTR j$2[rsp]
	add	rax, rcx
	mov	QWORD PTR tv175[rsp], rax
	call	?ahci_disk_get_port@@YAPEAU_hba_port_@@XZ ; ahci_disk_get_port
	mov	r9, QWORD PTR buff$[rsp]
	mov	r8d, 1
	mov	rcx, QWORD PTR tv175[rsp]
	mov	rdx, rcx
	mov	rcx, rax
	call	?ahci_disk_write@@YAXPEAU_hba_port_@@_KIPEA_K@Z ; ahci_disk_write

; 106  : 				AuPmmngrFree(buffer);

	mov	rcx, QWORD PTR buffer$5[rsp]
	call	AuPmmngrFree

; 107  : 
; 108  : 				strcpy (file->filename,fname);

	mov	rax, QWORD PTR file$[rsp]
	lea	rdx, QWORD PTR fname$[rsp]
	mov	rcx, rax
	call	strcpy

; 109  : 				file->size = dirent->file_size;

	mov	rax, QWORD PTR file$[rsp]
	mov	rcx, QWORD PTR dirent$1[rsp]
	mov	ecx, DWORD PTR [rcx+28]
	mov	DWORD PTR [rax+32], ecx

; 110  : 				file->eof = 0;

	mov	rax, QWORD PTR file$[rsp]
	mov	BYTE PTR [rax+36], 0

; 111  : 				file->pos = 0;

	mov	rax, QWORD PTR file$[rsp]
	mov	DWORD PTR [rax+40], 0

; 112  : 				file->current = dirent->first_cluster;

	mov	rax, QWORD PTR dirent$1[rsp]
	movzx	eax, WORD PTR [rax+26]
	mov	rcx, QWORD PTR file$[rsp]
	mov	DWORD PTR [rcx+44], eax

; 113  : 				file->flags = FS_FLAG_GENERAL;

	mov	rax, QWORD PTR file$[rsp]
	mov	BYTE PTR [rax+48], 4

; 114  : 				file->status = FS_STATUS_FOUND;

	mov	rax, QWORD PTR file$[rsp]
	mov	BYTE PTR [rax+49], 4

; 115  : 				_debug_print_ ("FAT32: file created at entry-> %d \r\n",i);

	mov	edx, DWORD PTR i$3[rsp]
	lea	rcx, OFFSET FLAT:$SG3711
	call	_debug_print_

; 116  : 			    return file;

	mov	rax, QWORD PTR file$[rsp]
	jmp	SHORT $LN12@fat32_make
$LN4@fat32_make:

; 117  : 			}
; 118  : 			dirent++;

	mov	rax, QWORD PTR dirent$1[rsp]
	add	rax, 32					; 00000020H
	mov	QWORD PTR dirent$1[rsp], rax

; 119  : 		}

	jmp	$LN6@fat32_make
$LN5@fat32_make:

; 120  : 	}

	jmp	$LN9@fat32_make
$LN8@fat32_make:

; 121  : 	parent_clust = fat32_read_fat(parent_clust);

	mov	ecx, DWORD PTR parent_clust$[rsp]
	call	?fat32_read_fat@@YAII@Z			; fat32_read_fat
	mov	DWORD PTR parent_clust$[rsp], eax

; 122  : 	if (parent_clust != FAT_EOC_MARK)

	cmp	DWORD PTR parent_clust$[rsp], -8	; fffffff8H
	je	SHORT $LN2@fat32_make

; 123  : 		goto search;

	jmp	$search$15

; 124  : 	else {

	jmp	SHORT $LN1@fat32_make
$LN2@fat32_make:

; 125  : 		free (file);

	mov	rcx, QWORD PTR file$[rsp]
	call	free

; 126  : 		return NULL;

	xor	eax, eax
$LN1@fat32_make:
$LN12@fat32_make:

; 127  : 	}
; 128  : }

	add	rsp, 136				; 00000088H
	ret	0
?fat32_make_file@@YAPEAU_vfs_node_@@IPEADI@Z ENDP	; fat32_make_file
_TEXT	ENDS
END
