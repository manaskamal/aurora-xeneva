/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  vmsvga.h -- VMWare SVGA Graphics Driver
 *
 *  /PROJECT - Aurora { Xeneva }
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *================================================
 */

#ifndef __VMSVGA_H__
#define __VMSVGA_H__

#include <stdint.h>
#include <hal.h>
#include <drivers\pci.h>
#include <drivers\svga\svga_reg.h>
#include <drivers\svga\svga3d_reg.h>
#include <drivers\svga\svga_overlay.h>
#include <drivers\svga\svga_escape.h>

#define MIN(a, b)  ((a) < (b) ? (a) : (b))
#define MAX(a, b)  ((a) > (b) ? (a) : (b))


typedef struct _svga_drive_ {
	pci_address pci_addr;
	uint32_t io_base;
	uint32_t *fifo_mem;
	uint8_t  *fb_mem;
	uint32_t  fifo_size;
	uint32_t  fb_size;
	uint32_t  vram_size;

	uint32_t  device_version_id;
	uint32_t  capabilities;

	uint32_t  width;
	uint32_t  height;
	uint32_t  bpp;
	uint32_t  pitch;

	struct {
		uint32_t reserved_size;
		bool using_bounce_buffer;
		uint8_t bounce_buffer[1024 * 1024];
		uint32_t next_fence;
	}fifo;

	volatile struct {
		uint32_t pending;
		uint32_t switch_context;
		uint32_t count;
	} irq;
}svga_device;

extern uint32_t svga_read_reg (uint32_t index);
extern void svga_write_reg (uint32_t index, uint32_t value);
extern bool svga_is_fifo_reg_valid (int reg);
extern bool svga_has_fifo_cap (int cap);

extern void svga_init ();
extern void svga_enable ();
extern void svga_disable ();
extern void svga_set_mode (uint32_t width, uint32_t height, uint32_t bpp);
extern void svga_fifo_full ();
extern void* svga_fifo_reserve (uint32_t bytes);
extern void svga_fifo_commit (uint32_t bytes);
extern void svga_fifo_commit_all ();
extern void* svga_fifo_reserved_cmd (uint32_t type, uint32_t bytes) ;
extern void* svga_fifo_reserve_escape (uint32_t nsid, uint32_t bytes);
extern void svga_ring_doorbell ();
extern void* svga_alloc_gmr (uint32 size, SVGAGuestPtr *ptr);
extern void svga_update (uint32_t x, uint32_t y, uint32_t width, uint32_t height);
extern void svga_begin_define_cursor (const SVGAFifoCmdDefineCursor *cursor_info, 
							   void **and_mask, void **xor_mask );
extern void svga_begin_define_alpha_cursor (const SVGAFifoCmdDefineAlphaCursor *cursor_info,
									 void **data);
extern void svga_move_cursor (uint32_t visible, 
					   uint32_t x,
					   uint32_t y,
					   uint32_t screen_id);
extern void svga_begin_video_set_regs (uint32_t stream_id, uint32_t num_items, SVGAEscapeVideoSetRegs **set_regs);
extern void svga_video_set_all_regs (uint32_t stream_id, SVGAOverlayUnit *regs, uint32_t max_reg);
extern void svga_video_set_reg (uint32_t stream_id, uint32_t register_id, uint32_t value);
extern void svga_video_flush (uint32_t stream_id);
extern void svga_interrupt_handler (size_t s, void* p);
extern void svga_panic (const char* text);
extern void svga_sync_to_fence (uint32_t fence);
extern uint32_t svga_insert_fence ();
extern void svga_wait_for_irq () ;
extern uint32_t* svga_get_fb_mem ();
#endif