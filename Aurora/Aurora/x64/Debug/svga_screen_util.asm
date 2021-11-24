; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?g_screen@@3U_screen_console_@@A		; g_screen
_BSS	SEGMENT
?g_screen@@3U_screen_console_@@A DB 048H DUP (?)	; g_screen
_BSS	ENDS
CONST	SEGMENT
$SG5589	DB	'GMR Pages -> %x', 0aH, 00H
	ORG $+7
$SG5592	DB	'Tile buffer -> %x', 0aH, 00H
	ORG $+5
$SG5625	DB	'Drawing rect', 0aH, 00H
CONST	ENDS
PUBLIC	?svga_screen_console_init@@YAXI@Z		; svga_screen_console_init
PUBLIC	?svga_screen_console_set@@YAXIHH@Z		; svga_screen_console_set
PUBLIC	?svga_screen_console_rect@@YAXHHHHI@Z		; svga_screen_console_rect
PUBLIC	?svga_draw_tile_rect@@YAXHHHH@Z			; svga_draw_tile_rect
EXTRN	?svga_sync_to_fence@@YAXI@Z:PROC		; svga_sync_to_fence
EXTRN	?svga_insert_fence@@YAIXZ:PROC			; svga_insert_fence
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?gmr_define_contiguous@@YAIII@Z:PROC		; gmr_define_contiguous
EXTRN	?svga_screen_define_gmrfb@@YAXUSVGAGuestPtr@@IUSVGAGMRImageFormat@@@Z:PROC ; svga_screen_define_gmrfb
EXTRN	?svga_screen_blit_from_gmrfb@@YAXPEBUSVGASignedPoint@@PEBUSVGASignedRect@@I@Z:PROC ; svga_screen_blit_from_gmrfb
EXTRN	?svga_screen_annotate_fill@@YAXUSVGAColorBGRX@@@Z:PROC ; svga_screen_annotate_fill
pdata	SEGMENT
$pdata$?svga_screen_console_init@@YAXI@Z DD imagerel $LN3
	DD	imagerel $LN3+113
	DD	imagerel $unwind$?svga_screen_console_init@@YAXI@Z
$pdata$?svga_screen_console_rect@@YAXHHHHI@Z DD imagerel $LN5
	DD	imagerel $LN5+137
	DD	imagerel $unwind$?svga_screen_console_rect@@YAXHHHHI@Z
$pdata$?svga_draw_tile_rect@@YAXHHHH@Z DD imagerel $LN14
	DD	imagerel $LN14+271
	DD	imagerel $unwind$?svga_draw_tile_rect@@YAXHHHH@Z
pdata	ENDS
;	COMDAT ?src_origin@?1??svga_draw_tile_rect@@YAXHHHH@Z@4USVGASignedPoint@@B
CONST	SEGMENT
?src_origin@?1??svga_draw_tile_rect@@YAXHHHH@Z@4USVGASignedPoint@@B DD 00H ; `svga_draw_tile_rect'::`2'::src_origin
	DD	00H
CONST	ENDS
;	COMDAT ?format@?1??svga_draw_tile_rect@@YAXHHHH@Z@4USVGAGMRImageFormat@@B
CONST	SEGMENT
?format@?1??svga_draw_tile_rect@@YAXHHHH@Z@4USVGAGMRImageFormat@@B DD 01820H ; `svga_draw_tile_rect'::`2'::format
CONST	ENDS
xdata	SEGMENT
$unwind$?svga_screen_console_init@@YAXI@Z DD 010801H
	DD	06208H
$unwind$?svga_screen_console_rect@@YAXHHHHI@Z DD 011601H
	DD	04216H
$unwind$?svga_draw_tile_rect@@YAXHHHH@Z DD 011601H
	DD	08216H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\svga\svga_screen_util.cpp
_TEXT	SEGMENT
tv72 = 32
tv78 = 36
color$1 = 40
dest_rect$ = 48
left$ = 80
top$ = 88
right$ = 96
bottom$ = 104
?svga_draw_tile_rect@@YAXHHHH@Z PROC			; svga_draw_tile_rect

; 38   : void svga_draw_tile_rect (int left, int top, int right, int bottom) {

$LN14:
	mov	DWORD PTR [rsp+32], r9d
	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 72					; 00000048H

; 39   : 
; 40   : 	static const SVGAGMRImageFormat format = {{{32, 24}}};
; 41   : 	svga_screen_define_gmrfb(g_screen.tile_ptr, TILE_SIZE * sizeof(uint32_t), format);

	mov	r8d, DWORD PTR ?format@?1??svga_draw_tile_rect@@YAXHHHH@Z@4USVGAGMRImageFormat@@B
	mov	edx, 256				; 00000100H
	mov	rcx, QWORD PTR ?g_screen@@3U_screen_console_@@A+20
	call	?svga_screen_define_gmrfb@@YAXUSVGAGuestPtr@@IUSVGAGMRImageFormat@@@Z ; svga_screen_define_gmrfb

; 42   : 
; 43   : 	static const SVGASignedPoint src_origin = {0, 0};
; 44   : 	SVGASignedRect dest_rect;
; 45   : 
; 46   : 	for (dest_rect.top = top; dest_rect.top < bottom; dest_rect.top += TILE_SIZE) {

	mov	eax, DWORD PTR top$[rsp]
	mov	DWORD PTR dest_rect$[rsp+4], eax
	jmp	SHORT $LN7@svga_draw_
$LN6@svga_draw_:
	mov	eax, DWORD PTR dest_rect$[rsp+4]
	add	eax, 64					; 00000040H
	mov	DWORD PTR dest_rect$[rsp+4], eax
$LN7@svga_draw_:
	mov	eax, DWORD PTR bottom$[rsp]
	cmp	DWORD PTR dest_rect$[rsp+4], eax
	jge	$LN5@svga_draw_

; 47   : 		dest_rect.bottom = MIN (bottom, dest_rect.top + TILE_SIZE);

	mov	eax, DWORD PTR dest_rect$[rsp+4]
	add	eax, 64					; 00000040H
	cmp	DWORD PTR bottom$[rsp], eax
	jge	SHORT $LN10@svga_draw_
	mov	eax, DWORD PTR bottom$[rsp]
	mov	DWORD PTR tv72[rsp], eax
	jmp	SHORT $LN11@svga_draw_
$LN10@svga_draw_:
	mov	eax, DWORD PTR dest_rect$[rsp+4]
	add	eax, 64					; 00000040H
	mov	DWORD PTR tv72[rsp], eax
$LN11@svga_draw_:
	mov	eax, DWORD PTR tv72[rsp]
	mov	DWORD PTR dest_rect$[rsp+12], eax

; 48   : 
; 49   : 		for (dest_rect.left = left; dest_rect.left < right; dest_rect.left += TILE_SIZE) {

	mov	eax, DWORD PTR left$[rsp]
	mov	DWORD PTR dest_rect$[rsp], eax
	jmp	SHORT $LN4@svga_draw_
$LN3@svga_draw_:
	mov	eax, DWORD PTR dest_rect$[rsp]
	add	eax, 64					; 00000040H
	mov	DWORD PTR dest_rect$[rsp], eax
$LN4@svga_draw_:
	mov	eax, DWORD PTR right$[rsp]
	cmp	DWORD PTR dest_rect$[rsp], eax
	jge	SHORT $LN2@svga_draw_

; 50   : 			dest_rect.right = MIN (right, dest_rect.left + TILE_SIZE);

	mov	eax, DWORD PTR dest_rect$[rsp]
	add	eax, 64					; 00000040H
	cmp	DWORD PTR right$[rsp], eax
	jge	SHORT $LN12@svga_draw_
	mov	eax, DWORD PTR right$[rsp]
	mov	DWORD PTR tv78[rsp], eax
	jmp	SHORT $LN13@svga_draw_
$LN12@svga_draw_:
	mov	eax, DWORD PTR dest_rect$[rsp]
	add	eax, 64					; 00000040H
	mov	DWORD PTR tv78[rsp], eax
$LN13@svga_draw_:
	mov	eax, DWORD PTR tv78[rsp]
	mov	DWORD PTR dest_rect$[rsp+8], eax

; 51   : 
; 52   : 			if (g_screen.tile_usage.type == TILE_FILL) {

	cmp	DWORD PTR ?g_screen@@3U_screen_console_@@A+60, 1
	jne	SHORT $LN1@svga_draw_

; 53   : 				SVGAColorBGRX color;
; 54   : 				color.value = g_screen.tile_usage.color;

	mov	eax, DWORD PTR ?g_screen@@3U_screen_console_@@A+64
	mov	DWORD PTR color$1[rsp], eax

; 55   : 				svga_screen_annotate_fill (color);

	mov	ecx, DWORD PTR color$1[rsp]
	call	?svga_screen_annotate_fill@@YAXUSVGAColorBGRX@@@Z ; svga_screen_annotate_fill
$LN1@svga_draw_:

; 56   : 			}
; 57   : 
; 58   : 			svga_screen_blit_from_gmrfb (&src_origin, &dest_rect, g_screen.screen_id);

	mov	r8d, DWORD PTR ?g_screen@@3U_screen_console_@@A+8
	lea	rdx, QWORD PTR dest_rect$[rsp]
	lea	rcx, OFFSET FLAT:?src_origin@?1??svga_draw_tile_rect@@YAXHHHH@Z@4USVGASignedPoint@@B
	call	?svga_screen_blit_from_gmrfb@@YAXPEBUSVGASignedPoint@@PEBUSVGASignedRect@@I@Z ; svga_screen_blit_from_gmrfb

; 59   : 		}

	jmp	SHORT $LN3@svga_draw_
$LN2@svga_draw_:

; 60   : 	}

	jmp	$LN6@svga_draw_
$LN5@svga_draw_:

; 61   : 
; 62   : 	g_screen.tile_fence = svga_insert_fence();

	call	?svga_insert_fence@@YAIXZ		; svga_insert_fence
	mov	DWORD PTR ?g_screen@@3U_screen_console_@@A+56, eax

; 63   : }

	add	rsp, 72					; 00000048H
	ret	0
?svga_draw_tile_rect@@YAXHHHH@Z ENDP			; svga_draw_tile_rect
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\svga\svga_screen_util.cpp
_TEXT	SEGMENT
left$ = 48
top$ = 56
right$ = 64
bottom$ = 72
color$ = 80
?svga_screen_console_rect@@YAXHHHHI@Z PROC		; svga_screen_console_rect

; 67   : 							   int right, int bottom, uint32_t color) {

$LN5:
	mov	DWORD PTR [rsp+32], r9d
	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 40					; 00000028H

; 68   : 
; 69   : 								   printf ("Drawing rect\n");

	lea	rcx, OFFSET FLAT:$SG5625
	call	?printf@@YAXPEBDZZ			; printf

; 70   : 	if (g_screen.tile_usage.type != TILE_FILL || g_screen.tile_usage.color != color) {

	cmp	DWORD PTR ?g_screen@@3U_screen_console_@@A+60, 1
	jne	SHORT $LN1@svga_scree
	mov	eax, DWORD PTR color$[rsp]
	cmp	DWORD PTR ?g_screen@@3U_screen_console_@@A+64, eax
	je	SHORT $LN2@svga_scree
$LN1@svga_scree:

; 71   : 		svga_sync_to_fence (g_screen.tile_fence);

	mov	ecx, DWORD PTR ?g_screen@@3U_screen_console_@@A+56
	call	?svga_sync_to_fence@@YAXI@Z		; svga_sync_to_fence

; 72   : 		g_screen.tile_usage.type = TILE_FILL;

	mov	DWORD PTR ?g_screen@@3U_screen_console_@@A+60, 1

; 73   : 		g_screen.tile_usage.color = color;

	mov	eax, DWORD PTR color$[rsp]
	mov	DWORD PTR ?g_screen@@3U_screen_console_@@A+64, eax

; 74   : 		memset (g_screen.tile_buffer, color, TILE_BUFFER_PIXELS);

	mov	r8d, 4096				; 00001000H
	movzx	edx, BYTE PTR color$[rsp]
	mov	rcx, QWORD PTR ?g_screen@@3U_screen_console_@@A+32
	call	?memset@@YAXPEAXEI@Z			; memset
$LN2@svga_scree:

; 75   : 	}
; 76   : 
; 77   : 	svga_draw_tile_rect (left, top, right, bottom);

	mov	r9d, DWORD PTR bottom$[rsp]
	mov	r8d, DWORD PTR right$[rsp]
	mov	edx, DWORD PTR top$[rsp]
	mov	ecx, DWORD PTR left$[rsp]
	call	?svga_draw_tile_rect@@YAXHHHH@Z		; svga_draw_tile_rect

; 78   : }

	add	rsp, 40					; 00000028H
	ret	0
?svga_screen_console_rect@@YAXHHHHI@Z ENDP		; svga_screen_console_rect
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\svga\svga_screen_util.cpp
_TEXT	SEGMENT
screen_id$ = 8
width$ = 16
height$ = 24
?svga_screen_console_set@@YAXIHH@Z PROC			; svga_screen_console_set

; 31   : void svga_screen_console_set (uint32_t screen_id, int width, int height) {

	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx

; 32   : 	g_screen.screen_id = screen_id;

	mov	eax, DWORD PTR screen_id$[rsp]
	mov	DWORD PTR ?g_screen@@3U_screen_console_@@A+8, eax

; 33   : 	g_screen.screen_width = width;

	mov	eax, DWORD PTR width$[rsp]
	mov	DWORD PTR ?g_screen@@3U_screen_console_@@A+12, eax

; 34   : 	g_screen.screen_height = height;

	mov	eax, DWORD PTR height$[rsp]
	mov	DWORD PTR ?g_screen@@3U_screen_console_@@A+16, eax

; 35   : }

	ret	0
?svga_screen_console_set@@YAXIHH@Z ENDP			; svga_screen_console_set
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\svga\svga_screen_util.cpp
_TEXT	SEGMENT
gmr_pages$ = 32
gmr_size$ = 36
gmr_id$ = 64
?svga_screen_console_init@@YAXI@Z PROC			; svga_screen_console_init

; 20   : void svga_screen_console_init (uint32_t gmr_id) {

$LN3:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 21   : 	
; 22   : 	const uint32_t gmr_size = TILE_BUFFER_BYTES + MAX_FONT_SIZE;

	mov	DWORD PTR gmr_size$[rsp], 216384	; 00034d40H

; 23   : 	ppn gmr_pages = gmr_define_contiguous (gmr_id, (gmr_size + PAGE_MASK) / PAGE_SIZE);

	mov	edx, 53					; 00000035H
	mov	ecx, DWORD PTR gmr_id$[rsp]
	call	?gmr_define_contiguous@@YAIII@Z		; gmr_define_contiguous
	mov	DWORD PTR gmr_pages$[rsp], eax

; 24   : 	printf ("GMR Pages -> %x\n", gmr_pages);

	mov	edx, DWORD PTR gmr_pages$[rsp]
	lea	rcx, OFFSET FLAT:$SG5589
	call	?printf@@YAXPEBDZZ			; printf

; 25   : 	g_screen.tile_ptr.gmrId = gmr_id;

	mov	eax, DWORD PTR gmr_id$[rsp]
	mov	DWORD PTR ?g_screen@@3U_screen_console_@@A+20, eax

; 26   : 	g_screen.tile_ptr.offset = 0;

	mov	DWORD PTR ?g_screen@@3U_screen_console_@@A+24, 0

; 27   : 	g_screen.tile_buffer = (uint32_t*)PPN_POINTER(gmr_pages);

	mov	eax, DWORD PTR gmr_pages$[rsp]
	imul	eax, 4096				; 00001000H
	mov	eax, eax
	mov	QWORD PTR ?g_screen@@3U_screen_console_@@A+32, rax

; 28   : 	printf ("Tile buffer -> %x\n", g_screen.tile_buffer);

	mov	rdx, QWORD PTR ?g_screen@@3U_screen_console_@@A+32
	lea	rcx, OFFSET FLAT:$SG5592
	call	?printf@@YAXPEBDZZ			; printf

; 29   : }

	add	rsp, 56					; 00000038H
	ret	0
?svga_screen_console_init@@YAXI@Z ENDP			; svga_screen_console_init
_TEXT	ENDS
END
