; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?rtl_net_dev@@3PEAUrtl8139_dev@@EA		; rtl_net_dev
PUBLIC	?TSAD_Array@@3PAEA				; TSAD_Array
PUBLIC	?TSD_Array@@3PAEA				; TSD_Array
PUBLIC	?current_packet_ptr@@3IA			; current_packet_ptr
_BSS	SEGMENT
?rtl_net_dev@@3PEAUrtl8139_dev@@EA DQ 01H DUP (?)	; rtl_net_dev
?current_packet_ptr@@3IA DD 01H DUP (?)			; current_packet_ptr
_BSS	ENDS
CONST	SEGMENT
$SG3329	DB	'***RTL8139: Interrupt fired ***', 0aH, 00H
	ORG $+7
$SG3332	DB	'Receive packet', 0aH, 00H
$SG3337	DB	'RTL8192 MAC:', 00H
	ORG $+3
$SG3342	DB	':%x', 00H
$SG3343	DB	0aH, 00H
	ORG $+2
$SG3359	DB	'Realtek RTL8139 Device not found', 0aH, 00H
	ORG $+6
$SG3361	DB	'Realtek RTL8139 Device found, io_addr -> %x, mem_base ->'
	DB	' %x', 0aH, 00H
	ORG $+3
$SG3366	DB	'PCI Command reg -> %x', 0aH, 00H
	ORG $+1
$SG3367	DB	'RTL8139 Bus Mastering enabled', 0aH, 00H
	ORG $+1
$SG3374	DB	'RTL8139 Irq -> %d', 0aH, 00H
CONST	ENDS
_DATA	SEGMENT
?TSAD_Array@@3PAEA DB 020H				; TSAD_Array
	DB	024H
	DB	028H
	DB	02cH
?TSD_Array@@3PAEA DB 010H				; TSD_Array
	DB	014H
	DB	018H
	DB	01cH
_DATA	ENDS
PUBLIC	?rtl8139_initialize@@YAXXZ			; rtl8139_initialize
PUBLIC	?rtl8139_handler@@YAX_KPEAX@Z			; rtl8139_handler
PUBLIC	?rtl_read_mac_address@@YAXXZ			; rtl_read_mac_address
PUBLIC	?rtl_send_packet@@YAXPEAXI@Z			; rtl_send_packet
EXTRN	x64_inportb:PROC
EXTRN	x64_inportw:PROC
EXTRN	x64_inportd:PROC
EXTRN	x64_outportb:PROC
EXTRN	x64_outportw:PROC
EXTRN	x64_outportd:PROC
EXTRN	?interrupt_end@@YAXI@Z:PROC			; interrupt_end
EXTRN	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z:PROC	; interrupt_set
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?get_physical_address@@YAPEA_K_K@Z:PROC		; get_physical_address
EXTRN	?malloc@@YAPEAX_K@Z:PROC			; malloc
EXTRN	?pci_config_read8@@YAEPEBU_pci_address_@@G@Z:PROC ; pci_config_read8
EXTRN	?pci_config_write8@@YAXPEBU_pci_address_@@GE@Z:PROC ; pci_config_write8
EXTRN	?pci_find_device@@YA_NGGPEAU_pci_address_@@@Z:PROC ; pci_find_device
EXTRN	?pci_get_bar_addr@@YAIPEBU_pci_address_@@H@Z:PROC ; pci_get_bar_addr
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
pdata	SEGMENT
$pdata$?rtl8139_initialize@@YAXXZ DD imagerel $LN6
	DD	imagerel $LN6+604
	DD	imagerel $unwind$?rtl8139_initialize@@YAXXZ
$pdata$?rtl8139_handler@@YAX_KPEAX@Z DD imagerel $LN4
	DD	imagerel $LN4+126
	DD	imagerel $unwind$?rtl8139_handler@@YAX_KPEAX@Z
$pdata$?rtl_read_mac_address@@YAXXZ DD imagerel $LN6
	DD	imagerel $LN6+299
	DD	imagerel $unwind$?rtl_read_mac_address@@YAXXZ
$pdata$?rtl_send_packet@@YAXPEAXI@Z DD imagerel $LN4
	DD	imagerel $LN4+198
	DD	imagerel $unwind$?rtl_send_packet@@YAXPEAXI@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?rtl8139_initialize@@YAXXZ DD 010401H
	DD	08204H
$unwind$?rtl8139_handler@@YAX_KPEAX@Z DD 010e01H
	DD	0620eH
$unwind$?rtl_read_mac_address@@YAXXZ DD 010401H
	DD	06204H
$unwind$?rtl_send_packet@@YAXPEAXI@Z DD 010d01H
	DD	0820dH
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\net\rtl8139.cpp
_TEXT	SEGMENT
tv93 = 32
transfar_data$ = 40
phys_addr$ = 48
data$ = 80
len$ = 88
?rtl_send_packet@@YAXPEAXI@Z PROC			; rtl_send_packet

; 52   : void rtl_send_packet (void* data, uint32_t len) {

$LN4:
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 53   : 	void *transfar_data = malloc(len);

	mov	eax, DWORD PTR len$[rsp]
	mov	ecx, eax
	call	?malloc@@YAPEAX_K@Z			; malloc
	mov	QWORD PTR transfar_data$[rsp], rax

; 54   : 	void *phys_addr = get_physical_address((uint64_t)transfar_data);

	mov	rcx, QWORD PTR transfar_data$[rsp]
	call	?get_physical_address@@YAPEA_K_K@Z	; get_physical_address
	mov	QWORD PTR phys_addr$[rsp], rax

; 55   : 
; 56   : 	x64_outportd (rtl_net_dev->io_base + TSAD_Array[rtl_net_dev->tx_cur], (uint32_t)phys_addr);

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	eax, WORD PTR [rax+2]
	mov	rcx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movsxd	rcx, DWORD PTR [rcx+32]
	lea	rdx, OFFSET FLAT:?TSAD_Array@@3PAEA	; TSAD_Array
	movzx	ecx, BYTE PTR [rdx+rcx]
	add	eax, ecx
	mov	edx, DWORD PTR phys_addr$[rsp]
	movzx	ecx, ax
	call	x64_outportd

; 57   : 	x64_outportd (rtl_net_dev->io_base + TSD_Array[rtl_net_dev->tx_cur++], len);

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	eax, WORD PTR [rax+2]
	mov	rcx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movsxd	rcx, DWORD PTR [rcx+32]
	lea	rdx, OFFSET FLAT:?TSD_Array@@3PAEA	; TSD_Array
	movzx	ecx, BYTE PTR [rdx+rcx]
	add	eax, ecx
	mov	DWORD PTR tv93[rsp], eax
	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	mov	eax, DWORD PTR [rax+32]
	inc	eax
	mov	rcx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	mov	DWORD PTR [rcx+32], eax
	mov	edx, DWORD PTR len$[rsp]
	movzx	ecx, WORD PTR tv93[rsp]
	call	x64_outportd

; 58   : 	if (rtl_net_dev->tx_cur > 3)

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	cmp	DWORD PTR [rax+32], 3
	jle	SHORT $LN1@rtl_send_p

; 59   : 		rtl_net_dev->tx_cur = 0;

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	mov	DWORD PTR [rax+32], 0
$LN1@rtl_send_p:

; 60   : }

	add	rsp, 72					; 00000048H
	ret	0
?rtl_send_packet@@YAXPEAXI@Z ENDP			; rtl_send_packet
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\net\rtl8139.cpp
_TEXT	SEGMENT
mac_part2$ = 32
mac_part1$ = 36
i$1 = 40
?rtl_read_mac_address@@YAXXZ PROC			; rtl_read_mac_address

; 33   : void rtl_read_mac_address () {

$LN6:
	sub	rsp, 56					; 00000038H

; 34   : 	uint32_t mac_part1 = x64_inportd (rtl_net_dev->io_base + 0x00);

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	ecx, WORD PTR [rax+2]
	call	x64_inportd
	mov	DWORD PTR mac_part1$[rsp], eax

; 35   : 	uint16_t mac_part2 = x64_inportw (rtl_net_dev->io_base + 0x04);

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	eax, WORD PTR [rax+2]
	add	eax, 4
	movzx	ecx, ax
	call	x64_inportw
	mov	WORD PTR mac_part2$[rsp], ax

; 36   : 	rtl_net_dev->mac_addr[0] = mac_part1 >> 0;

	mov	eax, 1
	imul	rax, 0
	mov	rcx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	edx, BYTE PTR mac_part1$[rsp]
	mov	BYTE PTR [rcx+rax+12], dl

; 37   : 	rtl_net_dev->mac_addr[1] = mac_part1 >> 8;

	mov	eax, DWORD PTR mac_part1$[rsp]
	shr	eax, 8
	mov	ecx, 1
	imul	rcx, 1
	mov	rdx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	mov	BYTE PTR [rdx+rcx+12], al

; 38   : 	rtl_net_dev->mac_addr[2] = mac_part1 >> 16;

	mov	eax, DWORD PTR mac_part1$[rsp]
	shr	eax, 16
	mov	ecx, 1
	imul	rcx, 2
	mov	rdx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	mov	BYTE PTR [rdx+rcx+12], al

; 39   : 	rtl_net_dev->mac_addr[3] = mac_part1 >> 24;

	mov	eax, DWORD PTR mac_part1$[rsp]
	shr	eax, 24
	mov	ecx, 1
	imul	rcx, 3
	mov	rdx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	mov	BYTE PTR [rdx+rcx+12], al

; 40   : 
; 41   : 	rtl_net_dev->mac_addr[4] = mac_part2 >> 0;

	mov	eax, 1
	imul	rax, 4
	mov	rcx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	edx, BYTE PTR mac_part2$[rsp]
	mov	BYTE PTR [rcx+rax+12], dl

; 42   : 	rtl_net_dev->mac_addr[5] = mac_part2 >> 8;

	movzx	eax, WORD PTR mac_part2$[rsp]
	sar	eax, 8
	mov	ecx, 1
	imul	rcx, 5
	mov	rdx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	mov	BYTE PTR [rdx+rcx+12], al

; 43   : 
; 44   : 	printf ("RTL8192 MAC:");

	lea	rcx, OFFSET FLAT:$SG3337
	call	?printf@@YAXPEBDZZ			; printf

; 45   : 	for (int i = 0; i < 6; i++){

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@rtl_read_m
$LN2@rtl_read_m:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@rtl_read_m:
	cmp	DWORD PTR i$1[rsp], 6
	jge	SHORT $LN1@rtl_read_m

; 46   : 	 printf (":%x", rtl_net_dev->mac_addr[i]);

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	eax, BYTE PTR [rcx+rax+12]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG3342
	call	?printf@@YAXPEBDZZ			; printf

; 47   : 	}

	jmp	SHORT $LN2@rtl_read_m
$LN1@rtl_read_m:

; 48   : 	printf ("\n");

	lea	rcx, OFFSET FLAT:$SG3343
	call	?printf@@YAXPEBDZZ			; printf

; 49   : }

	add	rsp, 56					; 00000038H
	ret	0
?rtl_read_mac_address@@YAXXZ ENDP			; rtl_read_mac_address
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\net\rtl8139.cpp
_TEXT	SEGMENT
status$ = 32
v$ = 64
p$ = 72
?rtl8139_handler@@YAX_KPEAX@Z PROC			; rtl8139_handler

; 22   : void rtl8139_handler (size_t v, void* p) {

$LN4:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 23   : 	printf ("***RTL8139: Interrupt fired ***\n");

	lea	rcx, OFFSET FLAT:$SG3329
	call	?printf@@YAXPEBDZZ			; printf

; 24   : 	uint16_t status = x64_inportw(rtl_net_dev->io_base + 0x3e);

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	eax, WORD PTR [rax+2]
	add	eax, 62					; 0000003eH
	movzx	ecx, ax
	call	x64_inportw
	mov	WORD PTR status$[rsp], ax

; 25   : 
; 26   : 	if (status & ROK) {

	movzx	eax, WORD PTR status$[rsp]
	and	eax, 1
	test	eax, eax
	je	SHORT $LN1@rtl8139_ha

; 27   : 		printf ("Receive packet\n");

	lea	rcx, OFFSET FLAT:$SG3332
	call	?printf@@YAXPEBDZZ			; printf
$LN1@rtl8139_ha:

; 28   : 	}
; 29   : 	x64_outportw (rtl_net_dev->io_base + 0x3E, 0x5);

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	eax, WORD PTR [rax+2]
	add	eax, 62					; 0000003eH
	mov	dx, 5
	movzx	ecx, ax
	call	x64_outportw

; 30   : 	interrupt_end(rtl_net_dev->irq);

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	eax, BYTE PTR [rax+36]
	mov	ecx, eax
	call	?interrupt_end@@YAXI@Z			; interrupt_end

; 31   : }

	add	rsp, 56					; 00000038H
	ret	0
?rtl8139_handler@@YAX_KPEAX@Z ENDP			; rtl8139_handler
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\net\rtl8139.cpp
_TEXT	SEGMENT
pci_command_reg$ = 32
irq_num$ = 36
ret$ = 40
dev_addr$ = 48
?rtl8139_initialize@@YAXXZ PROC				; rtl8139_initialize

; 62   : void rtl8139_initialize () {

$LN6:
	sub	rsp, 72					; 00000048H

; 63   : 	rtl_net_dev = (rtl8139_dev*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA, rax ; rtl_net_dev

; 64   : 	pci_address *dev_addr = (pci_address*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR dev_addr$[rsp], rax

; 65   : 	if (!pci_find_device (RTL8139_VENDOR_ID,RTL8139_DEVICE_ID,dev_addr)) {

	mov	r8, QWORD PTR dev_addr$[rsp]
	mov	dx, 33081				; 00008139H
	mov	cx, 4332				; 000010ecH
	call	?pci_find_device@@YA_NGGPEAU_pci_address_@@@Z ; pci_find_device
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN3@rtl8139_in

; 66   : 		printf ("Realtek RTL8139 Device not found\n");

	lea	rcx, OFFSET FLAT:$SG3359
	call	?printf@@YAXPEBDZZ			; printf

; 67   : 		return;

	jmp	$LN4@rtl8139_in
$LN3@rtl8139_in:

; 68   : 	}
; 69   : 	uint32_t ret = pci_get_bar_addr(dev_addr, 0);

	xor	edx, edx
	mov	rcx, QWORD PTR dev_addr$[rsp]
	call	?pci_get_bar_addr@@YAIPEBU_pci_address_@@H@Z ; pci_get_bar_addr
	mov	DWORD PTR ret$[rsp], eax

; 70   : 	rtl_net_dev->bar_type = ret & 0x1;

	mov	eax, DWORD PTR ret$[rsp]
	and	eax, 1
	mov	rcx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	mov	BYTE PTR [rcx], al

; 71   : 	rtl_net_dev->io_base = ret & (~0x3);

	mov	eax, DWORD PTR ret$[rsp]
	and	eax, -4					; fffffffcH
	mov	rcx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	mov	WORD PTR [rcx+2], ax

; 72   : 	rtl_net_dev->mem_base = ret & (~0xf);

	mov	eax, DWORD PTR ret$[rsp]
	and	eax, -16				; fffffff0H
	mov	rcx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	mov	DWORD PTR [rcx+4], eax

; 73   : 
; 74   : 	printf ("Realtek RTL8139 Device found, io_addr -> %x, mem_base -> %x\n", rtl_net_dev->io_base, rtl_net_dev->mem_base);

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	eax, WORD PTR [rax+2]
	mov	rcx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	mov	r8d, DWORD PTR [rcx+4]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG3361
	call	?printf@@YAXPEBDZZ			; printf

; 75   : 	
; 76   : 	uint32_t irq_num = pci_config_read8 (dev_addr, offsetof (pci_config_space,intr_line));	

	mov	dx, 60					; 0000003cH
	mov	rcx, QWORD PTR dev_addr$[rsp]
	call	?pci_config_read8@@YAEPEBU_pci_address_@@G@Z ; pci_config_read8
	movzx	eax, al
	mov	DWORD PTR irq_num$[rsp], eax

; 77   : 	rtl_net_dev->irq = irq_num;

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	ecx, BYTE PTR irq_num$[rsp]
	mov	BYTE PTR [rax+36], cl

; 78   :     interrupt_set (irq_num,rtl8139_handler,irq_num);

	mov	eax, DWORD PTR irq_num$[rsp]
	movzx	r8d, BYTE PTR irq_num$[rsp]
	lea	rdx, OFFSET FLAT:?rtl8139_handler@@YAX_KPEAX@Z ; rtl8139_handler
	mov	ecx, eax
	call	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z	; interrupt_set

; 79   : 	rtl_net_dev->tx_cur = 0;

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	mov	DWORD PTR [rax+32], 0

; 80   : 
; 81   : 	//! enable bus mastering
; 82   : 	uint32_t pci_command_reg = pci_config_read8 (dev_addr,0x04);

	mov	dx, 4
	mov	rcx, QWORD PTR dev_addr$[rsp]
	call	?pci_config_read8@@YAEPEBU_pci_address_@@G@Z ; pci_config_read8
	movzx	eax, al
	mov	DWORD PTR pci_command_reg$[rsp], eax

; 83   : 	printf ("PCI Command reg -> %x\n", pci_command_reg);

	mov	edx, DWORD PTR pci_command_reg$[rsp]
	lea	rcx, OFFSET FLAT:$SG3366
	call	?printf@@YAXPEBDZZ			; printf

; 84   : 	pci_command_reg |= (1 << 2);

	mov	eax, DWORD PTR pci_command_reg$[rsp]
	or	eax, 4
	mov	DWORD PTR pci_command_reg$[rsp], eax

; 85   :     pci_config_write8(dev_addr, 0x04,pci_command_reg);

	movzx	r8d, BYTE PTR pci_command_reg$[rsp]
	mov	dx, 4
	mov	rcx, QWORD PTR dev_addr$[rsp]
	call	?pci_config_write8@@YAXPEBU_pci_address_@@GE@Z ; pci_config_write8

; 86   :     printf ("RTL8139 Bus Mastering enabled\n");

	lea	rcx, OFFSET FLAT:$SG3367
	call	?printf@@YAXPEBDZZ			; printf

; 87   : 	
; 88   : 	
; 89   : 	x64_outportb (rtl_net_dev->io_base + 0x52, 0x0);

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	eax, WORD PTR [rax+2]
	add	eax, 82					; 00000052H
	xor	edx, edx
	movzx	ecx, ax
	call	x64_outportb

; 90   : 
; 91   : 	//! Soft reset 
; 92   : 	x64_outportb(rtl_net_dev->io_base + 0x37, 0x10);

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	eax, WORD PTR [rax+2]
	add	eax, 55					; 00000037H
	mov	dl, 16
	movzx	ecx, ax
	call	x64_outportb
$LN2@rtl8139_in:

; 93   : 	while ((x64_inportb (rtl_net_dev->io_base + 0x37) & 0x10) != 0) {

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	eax, WORD PTR [rax+2]
	add	eax, 55					; 00000037H
	movzx	ecx, ax
	call	x64_inportb
	movzx	eax, al
	and	eax, 16
	test	eax, eax
	je	SHORT $LN1@rtl8139_in

; 94   : 	}

	jmp	SHORT $LN2@rtl8139_in
$LN1@rtl8139_in:

; 95   : 	
; 96   : 	//! allocate receive buffer
; 97   : 	rtl_net_dev->rx_buffer = (char*)malloc(8192 + 16 + 1500);

	mov	ecx, 9708				; 000025ecH
	call	?malloc@@YAPEAX_K@Z			; malloc
	mov	rcx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	mov	QWORD PTR [rcx+24], rax

; 98   : 	memset(rtl_net_dev->rx_buffer, 0x0, 8192 + 16 + 1500);

	mov	r8d, 9708				; 000025ecH
	xor	edx, edx
	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	mov	rcx, QWORD PTR [rax+24]
	call	?memset@@YAXPEAXEI@Z			; memset

; 99   : 	x64_outportd (rtl_net_dev->io_base + 0x30, (uint32_t)get_physical_address((uint64_t)rtl_net_dev->rx_buffer));

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	mov	rcx, QWORD PTR [rax+24]
	call	?get_physical_address@@YAPEA_K_K@Z	; get_physical_address
	mov	rcx, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	ecx, WORD PTR [rcx+2]
	add	ecx, 48					; 00000030H
	mov	edx, eax
	call	x64_outportd

; 100  : 
; 101  : 	x64_outportw (rtl_net_dev->io_base + 0x3C, 0x0005);

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	eax, WORD PTR [rax+2]
	add	eax, 60					; 0000003cH
	mov	dx, 5
	movzx	ecx, ax
	call	x64_outportw

; 102  : 
; 103  : 	x64_outportd (rtl_net_dev->io_base + 0x44, 0xf | (1 << 7));

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	eax, WORD PTR [rax+2]
	add	eax, 68					; 00000044H
	mov	edx, 143				; 0000008fH
	movzx	ecx, ax
	call	x64_outportd

; 104  : 
; 105  : 	x64_outportb (rtl_net_dev->io_base + 0x37, 0x0C);

	mov	rax, QWORD PTR ?rtl_net_dev@@3PEAUrtl8139_dev@@EA ; rtl_net_dev
	movzx	eax, WORD PTR [rax+2]
	add	eax, 55					; 00000037H
	mov	dl, 12
	movzx	ecx, ax
	call	x64_outportb

; 106  : 
; 107  : 	
; 108  : 	printf ("RTL8139 Irq -> %d\n", irq_num);

	mov	edx, DWORD PTR irq_num$[rsp]
	lea	rcx, OFFSET FLAT:$SG3374
	call	?printf@@YAXPEBDZZ			; printf

; 109  : 	
; 110  : 	rtl_read_mac_address();

	call	?rtl_read_mac_address@@YAXXZ		; rtl_read_mac_address

; 111  : 
; 112  : 	rtl_send_packet(NULL, 64);

	mov	edx, 64					; 00000040H
	xor	ecx, ecx
	call	?rtl_send_packet@@YAXPEAXI@Z		; rtl_send_packet
$LN4@rtl8139_in:

; 113  : }

	add	rsp, 72					; 00000048H
	ret	0
?rtl8139_initialize@@YAXXZ ENDP				; rtl8139_initialize
_TEXT	ENDS
END
