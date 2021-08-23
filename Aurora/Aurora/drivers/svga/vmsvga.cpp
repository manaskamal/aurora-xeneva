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

#include <drivers\svga\vmsvga.h>
#include <stdio.h>
#include <drivers\svga\gmr.h>
#include <drivers\svga\svga_screen.h>
#include <drivers\vga.h>
#include <drivers\svga\svga_screen_util.h>
#include <drivers\vmmouse.h>
#include <screen.h>

svga_device svga_dev;


uint32_t svga_read_reg (uint32_t index) {
	outportd (svga_dev.io_base + SVGA_INDEX_PORT, index);
	return inportd (svga_dev.io_base + SVGA_VALUE_PORT);
}

void svga_write_reg (uint32_t index, uint32_t value) {
	outportd (svga_dev.io_base + SVGA_INDEX_PORT, index);
	outportd (svga_dev.io_base + SVGA_VALUE_PORT, value);
}

bool svga_is_fifo_reg_valid (int reg) {
	return svga_dev.fifo_mem[SVGA_FIFO_MIN] > (reg << 2);
}

bool svga_has_fifo_cap (int cap) {
	return (svga_dev.fifo_mem[SVGA_FIFO_CAPABILITIES] & cap) != 0;
}


void svga_init () {
	
	if (!pci_find_device (PCI_VENDOR_ID_VMWARE, PCI_DEVICE_ID_VMWARE_SVGA2, &svga_dev.pci_addr)) {
		printf ("No VMware SVGA device found\n");
		return;
	}
	/*pci_device_info *dev = (pci_device_info*)pmmngr_alloc();
	if (!pci_find_device_class (0x03,0x00,dev)) {
		printf ("SVGA Controller not found\n");
		return;
	}*/

	pci_set_mem_enable (&svga_dev.pci_addr, true);
	svga_dev.io_base =  pci_get_bar_addr (&svga_dev.pci_addr,0);
	svga_dev.fb_mem = (uint8_t*)pci_get_bar_addr (&svga_dev.pci_addr, 1);
	svga_dev.fifo_mem = (uint32_t*)pci_get_bar_addr (&svga_dev.pci_addr, 2);


	svga_dev.device_version_id = SVGA_ID_2;
	do {
		svga_write_reg (SVGA_REG_ID, svga_dev.device_version_id);
		if (svga_read_reg (SVGA_REG_ID) == svga_dev.device_version_id) {
			break;
		}else {
			svga_dev.device_version_id--;
		}
	}while (svga_dev.device_version_id >= SVGA_ID_0);

	if (svga_dev.device_version_id < SVGA_ID_0) {
		printf ("[VMware SVGA]: negotiating SVGA device version!\n");
	}

	svga_dev.vram_size = svga_read_reg (SVGA_REG_VRAM_SIZE);
	svga_dev.fb_size = svga_read_reg (SVGA_REG_FB_SIZE);
	svga_dev.fifo_size = svga_read_reg (SVGA_REG_MEM_SIZE);
	//! sanity check the fifo and framebuffer sizes
	if (svga_dev.fb_size < 0x100000) {
		printf ("[VMware SVGA]: FrameBuffer size is very small, probably incorrect\n");
	}

	if (svga_dev.fifo_size < 0x20000) {
		printf ("[VMware SVGA]: FIFO size is very small, probably incorrect\n");
	}

	if (svga_dev.device_version_id >= SVGA_ID_1) {
		svga_dev.capabilities = svga_read_reg (SVGA_REG_CAPABILITIES);
	}

	//!interrupts
	if (svga_dev.capabilities & SVGA_CAP_IRQMASK) {
		uint8_t irq = pci_config_read8 (&svga_dev.pci_addr, offsetof (pci_config_space,intr_line));	
		svga_dev.irq_line = irq;
		svga_write_reg (SVGA_REG_IRQMASK, 0);
		printf ("Irq of svga -> %d\n", irq);
		outportd (svga_dev.io_base + SVGA_IRQSTATUS_PORT, 0xff);

		svga_dev.irq.pending = 0;
		if (irq <= 244)
			interrupt_set (irq, svga_interrupt_handler, irq);
		//irq_mask (irq, true);

	}

	svga_enable();
	svga_set_mode (1280,1024,32);
	gmr_init();
	memset(svga_dev.fb_mem,0x40,svga_dev.width*svga_dev.height*32);
	svga_update(0,0,svga_dev.width,svga_dev.height);
	screen_set_configuration(svga_dev.width,svga_dev.height);
	vm_backdoor_mouse_init (true);
}


void svga_enable () {

	svga_dev.fifo_mem[SVGA_FIFO_MIN] = SVGA_FIFO_NUM_REGS * sizeof(uint32_t);
	svga_dev.fifo_mem[SVGA_FIFO_MAX] = svga_dev.fifo_size;
	svga_dev.fifo_mem[SVGA_FIFO_NEXT_CMD] = svga_dev.fifo_mem[SVGA_FIFO_MIN];
	svga_dev.fifo_mem[SVGA_FIFO_STOP] = svga_dev.fifo_mem[SVGA_FIFO_MIN];

	if (svga_has_fifo_cap (SVGA_CAP_EXTENDED_FIFO) &&
		svga_is_fifo_reg_valid (SVGA_FIFO_GUEST_3D_HWVERSION)) {
			svga_dev.fifo_mem[SVGA_FIFO_GUEST_3D_HWVERSION] = SVGA3D_HWVERSION_CURRENT;
			printf ("HW3D supported\n");
	}

	//!Enable SVGA device and FIFO
	svga_write_reg (SVGA_REG_ENABLE, true);
	svga_write_reg (SVGA_REG_CONFIG_DONE, true);

	if (svga_dev.capabilities & SVGA_CAP_IRQMASK) {
		svga_write_reg (SVGA_REG_IRQMASK, SVGA_IRQFLAG_ANY_FENCE);
		printf ("SVGA IRQMask\n");
		svga_dev.irq.pending = 0;
		svga_insert_fence ();

		svga_write_reg (SVGA_REG_SYNC, 1);
		while (svga_read_reg (SVGA_REG_BUSY) != false);

		svga_write_reg (SVGA_REG_IRQMASK, 0);

		if ((svga_dev.irq.pending & SVGA_IRQFLAG_ANY_FENCE) == 0) {
			printf ("SVGA IRQ appears to be present but broken %d\n", svga_dev.irq.pending);
		}
	}

}


void svga_disable () {
	svga_write_reg (SVGA_REG_ENABLE, false);
}


void svga_panic (const char* text) {
	svga_disable ();
	printf (text);
}
void svga_set_mode (uint32_t width, uint32_t height, uint32_t bpp) {
	svga_dev.width = width;
	svga_dev.height = height;
	svga_dev.bpp = bpp;

	svga_write_reg (SVGA_REG_WIDTH, width);
	svga_write_reg (SVGA_REG_HEIGHT, height);
	svga_write_reg (SVGA_REG_BITS_PER_PIXEL, bpp);
	svga_write_reg (SVGA_REG_ENABLE, true);
	svga_dev.pitch = svga_read_reg (SVGA_REG_BYTES_PER_LINE);
}

void* svga_fifo_reserve (uint32_t bytes) {
	debug_serial ("[Aurora]: Actual Fifo Reserve function called\n");
	volatile uint32_t *fifo = svga_dev.fifo_mem;
	uint32_t max = fifo[SVGA_FIFO_MAX];
	uint32_t min = fifo[SVGA_FIFO_MIN];
	uint32_t next_cmd = fifo[SVGA_FIFO_NEXT_CMD];
	debug_serial ("[Aurora]: Fifo memory acquired\n");
	bool reserveable = svga_has_fifo_cap (SVGA_FIFO_CAP_RESERVE);

	if (bytes  > sizeof (svga_dev.fifo.bounce_buffer)/* || bytes > (max - min)*/) {
		debug_serial ("[VMware SVGA]: FIFO command too large bytes\n");
		//for(;;);
	}

	if (bytes % sizeof (uint32_t)) {
		debug_serial ("[VMware SVGA]: FIFO command length not 32-bit aligned\n");
		//for(;;);
	}

	if (svga_dev.fifo.reserved_size != 0) {
		debug_serial ("[VMware SVGA]: FIFO reserve before FIFO commit\n");
		//for(;;);
	}

	svga_dev.fifo.reserved_size = bytes;

	while (1) {
		uint32_t stop = fifo[SVGA_FIFO_STOP];
		bool reserve_in_place = false;
		bool need_bounce = false;
		debug_serial("[Aurora]: Stop -> %d\n");
		if (next_cmd >= stop) {
			debug_serial ("[Aurora]: Debug Step[1]\n");
			if (next_cmd + bytes < max ||
				(next_cmd + bytes == max && stop > min)) {
					reserve_in_place = true;
			} else if ((max - next_cmd) + (stop - min) <= bytes) {
				svga_fifo_full ();
			} else {
				need_bounce = true;
			}
		}else {
			if (next_cmd + bytes < stop) {
				reserve_in_place = true;
			}else {
				svga_fifo_full ();
			}
		}
		if (reserve_in_place) {

			if (reserveable || bytes <= sizeof (uint32_t)) {
				svga_dev.fifo.using_bounce_buffer = false;
				if (reserveable) {
					fifo[SVGA_FIFO_RESERVED] = bytes;
				}
				return next_cmd + (uint8_t*)fifo;
			}else {
				need_bounce = true;
			}
		}
		if (need_bounce) {
			svga_dev.fifo.using_bounce_buffer = true;
			return svga_dev.fifo.bounce_buffer;
		}
	}
}


void svga_fifo_commit (uint32_t bytes) {
	
	volatile uint32_t *fifo = svga_dev.fifo_mem;
	//printf ("FIFO Commit address -> %x\n", fifo);
	uint32_t next_cmd = fifo[SVGA_FIFO_NEXT_CMD];
	uint32_t max = fifo[SVGA_FIFO_MAX];
	uint32_t min = fifo[SVGA_FIFO_MIN];

	bool reserveable = svga_has_fifo_cap (SVGA_FIFO_CAP_RESERVE);

	if (svga_dev.fifo.reserved_size == 0) {
		printf ("[VMware SVGA]: FIFO commit before FIFO reserve\n");
	}
	svga_dev.fifo.reserved_size = 0;

	if (svga_dev.fifo.using_bounce_buffer) {
		//printf ("Commit using bounce buffer\n");
		uint8_t* buffer = svga_dev.fifo.bounce_buffer;
		//printf ("Bounce buffer -> %x\n", buffer);
		if (reserveable) {
			//printf ("Reserved\n");
			uint32_t chunk_size = MIN (bytes, max - next_cmd);
			fifo[SVGA_FIFO_RESERVED] = bytes;
			memcpy (next_cmd + (uint8_t*) fifo, buffer, chunk_size);
			memcpy (min + (uint8_t*)fifo, buffer + chunk_size, bytes - chunk_size);
		} else {
			uint32_t *dword = (uint32_t*) buffer;
			while (bytes > 0) {
				fifo[next_cmd / sizeof *dword] = *dword++;
				next_cmd += sizeof *dword;
				if (next_cmd == max) {
					next_cmd = min;
				}
				fifo[SVGA_FIFO_NEXT_CMD] = next_cmd;
				bytes -= sizeof *dword;
			}
		}
	}

	if (!svga_dev.fifo.using_bounce_buffer || reserveable) {
		next_cmd += bytes;
		if (next_cmd >= max) {
			next_cmd -= max - min;
		}
		fifo[SVGA_FIFO_NEXT_CMD] = next_cmd;
	}

	if (reserveable) {
		fifo[SVGA_FIFO_RESERVED] = 0;
	}
	//printf ("Fifo commited\n");
}

void svga_fifo_commit_all () {
	svga_fifo_commit (svga_dev.fifo.reserved_size);
}

void* svga_fifo_reserved_cmd (uint32_t type, uint32_t bytes) {
	debug_serial ("[Aurora]: Fifo Reserved function called\n");
	uint32_t*cmd = (uint32_t*)svga_fifo_reserve (bytes + sizeof type);
	cmd[0] = type;
	return cmd + 1;
}


void* svga_fifo_reserve_escape (uint32_t nsid, uint32_t bytes) {

	uint32_t padded_bytes = (bytes + 3) & ~3UL;
#pragma pack (push)
	struct header{
		uint32_t cmd;
		uint32_t nsid;
		uint32_t size;
	};
#pragma pack (pop)

	header *h = (header*)svga_fifo_reserve (padded_bytes + sizeof (header));
	h->cmd = SVGA_CMD_ESCAPE;
	h->nsid = nsid;
	h->size = bytes;

	return h + 1;
}

void svga_fifo_full () {
	if (svga_is_fifo_reg_valid (SVGA_FIFO_FENCE_GOAL) &&
		(svga_dev.capabilities & SVGA_CAP_IRQMASK)) {

			svga_write_reg (SVGA_REG_IRQMASK, SVGA_IRQFLAG_FIFO_PROGRESS);
			x64_cli();
			svga_ring_doorbell ();
			svga_wait_for_irq();
			svga_write_reg (SVGA_REG_IRQMASK, 0);
			x64_sti();
	} else {
		svga_write_reg (SVGA_REG_SYNC, 1);
		svga_read_reg (SVGA_REG_BUSY);
	}
}


void svga_ring_doorbell () {
	if (svga_is_fifo_reg_valid (SVGA_FIFO_BUSY) && svga_dev.fifo_mem[SVGA_FIFO_BUSY] == false) {
		svga_dev.fifo_mem[SVGA_FIFO_BUSY] = true;
		svga_write_reg (SVGA_REG_SYNC, 1);
	}
}

void* svga_alloc_gmr (uint32 size, SVGAGuestPtr *ptr) {
	static SVGAGuestPtr next_ptr = {SVGA_GMR_FRAMEBUFFER, 0 };
	*ptr = next_ptr;
	next_ptr.offset += size;
	return svga_dev.fb_mem + ptr->offset;
}

void svga_update (uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
	debug_serial ("[Aurora]: SVGA Screen Update called\n");
	SVGAFifoCmdUpdate *cmd = (SVGAFifoCmdUpdate*)svga_fifo_reserved_cmd (SVGA_CMD_UPDATE, sizeof (SVGAFifoCmdUpdate));
	cmd->x = x;
	cmd->y = y;
	cmd->width = width;
	cmd->height = height;
	svga_fifo_commit_all ();
	debug_serial ("[Aurora]: Update fifo completed\n");
}


void svga_begin_define_cursor (const SVGAFifoCmdDefineCursor *cursor_info, 
							   void **and_mask, void **xor_mask ) 
{
    uint32_t and_pitch = ((cursor_info->andMaskDepth * cursor_info->width + 31) >> 5) << 2;
	uint32_t and_size = and_pitch * cursor_info->height;
	uint32_t xor_pitch = ((cursor_info->xorMaskDepth * cursor_info->width + 31) >> 5) << 2;
	uint32_t xor_size = xor_pitch * cursor_info->height;

	SVGAFifoCmdDefineCursor *cmd = (SVGAFifoCmdDefineCursor*)svga_fifo_reserved_cmd (SVGA_CMD_DEFINE_CURSOR, sizeof *cmd + and_size + xor_size);

	*cmd = *cursor_info;
	*and_mask = (void*)(cmd + 1);
	*xor_mask  = (void*)(and_size + (uint8_t*)*and_mask);
}

void svga_begin_define_alpha_cursor (const SVGAFifoCmdDefineAlphaCursor *cursor_info,
									 void **data) 
{
	uint32_t image_size = cursor_info->width * cursor_info->height * sizeof(uint32_t);
	SVGAFifoCmdDefineAlphaCursor *cmd =  (SVGAFifoCmdDefineAlphaCursor*)svga_fifo_reserved_cmd (SVGA_CMD_DEFINE_ALPHA_CURSOR,
		sizeof(cmd) + image_size);  //sizeof *cmd;
	//printf ("Cmd address -> %x, %x\n", cmd, *cmd);
	*cmd = *cursor_info;
	*data = (void*) (cmd + 1);
}

void svga_move_cursor (uint32_t visible, 
					   uint32_t x,
					   uint32_t y,
					   uint32_t screen_id) 
{
	if (svga_has_fifo_cap (SVGA_FIFO_CAP_SCREEN_OBJECT)) {
		svga_dev.fifo_mem[SVGA_FIFO_CURSOR_SCREEN_ID] = screen_id;
	}

	if (svga_has_fifo_cap (SVGA_FIFO_CAP_CURSOR_BYPASS_3)) {
		//printf ("Cursor Bypass 3 supported\n");
		svga_dev.fifo_mem[SVGA_FIFO_CURSOR_ON] = visible;
		svga_dev.fifo_mem[SVGA_FIFO_CURSOR_X] = x;
		svga_dev.fifo_mem[SVGA_FIFO_CURSOR_Y] = y;
		svga_dev.fifo_mem[SVGA_FIFO_CURSOR_COUNT]++;
	}
}


void svga_begin_video_set_regs (uint32_t stream_id, uint32_t num_items, SVGAEscapeVideoSetRegs **set_regs) {
	SVGAEscapeVideoSetRegs *cmd;
	uint32_t cmd_size = (sizeof *cmd - sizeof cmd->items + num_items * sizeof cmd->items[0]);

	cmd = (SVGAEscapeVideoSetRegs*)svga_fifo_reserve_escape (SVGA_ESCAPE_NSID_VMWARE, cmd_size);
	cmd->header.cmdType = SVGA_ESCAPE_VMWARE_VIDEO_SET_REGS;
	cmd->header.streamId = stream_id;

	*set_regs = cmd;
}

void svga_video_set_all_regs (uint32_t stream_id, SVGAOverlayUnit *regs, uint32_t max_reg) {

	uint32_t *reg_array = (uint32_t*) regs;
	const uint32_t num_regs = max_reg + 1;
	SVGAEscapeVideoSetRegs *set_regs;
	uint32_t i;

	svga_begin_video_set_regs (stream_id, num_regs, &set_regs);

	for (i = 0; i < num_regs; i++) {
		set_regs->items[i].registerId = i;
		set_regs->items[i].value = reg_array[i];
	}

	svga_fifo_commit_all();
}



void svga_video_set_reg (uint32_t stream_id, uint32_t register_id, uint32_t value) {

	SVGAEscapeVideoSetRegs *set_regs;

	svga_begin_video_set_regs (stream_id, 1, &set_regs);
	set_regs->items[0].registerId = register_id;
	set_regs->items[0].value = value;
	svga_fifo_commit_all();
}


void svga_video_flush (uint32_t stream_id) {
	SVGAEscapeVideoFlush *cmd;

	cmd = (SVGAEscapeVideoFlush*)svga_fifo_reserve_escape (SVGA_ESCAPE_NSID_VMWARE, sizeof *cmd);
	cmd->cmdType = SVGA_ESCAPE_VMWARE_VIDEO_FLUSH;
	cmd->streamId = stream_id;
	svga_fifo_commit_all();
}



bool svga_has_fence_passed (uint32_t fence) {

	if (!fence) {
		return true;
	}

	if (!svga_has_fifo_cap (SVGA_FIFO_CAP_FENCE)) {
		return false;
	}

	return ((int32_t)(svga_dev.fifo_mem[SVGA_FIFO_FENCE] - fence)) >= 0;
}

void svga_sync_to_fence (uint32_t fence) {

	if (!fence) 
		return;

	if (!svga_has_fifo_cap (SVGA_FIFO_CAP_FENCE)) {
		//printf ("Fence Polling\n");
		svga_write_reg (SVGA_REG_SYNC, 1);
		while (svga_read_reg (SVGA_REG_BUSY) != false) {}
		//return;
	}

	if (svga_has_fence_passed (fence)) {
		//return;
	}

	if (svga_is_fifo_reg_valid (SVGA_FIFO_FENCE_GOAL) &&
		(svga_dev.capabilities & SVGA_CAP_IRQMASK)) {
			svga_dev.fifo_mem[SVGA_FIFO_FENCE_GOAL] = fence;
			svga_write_reg (SVGA_REG_IRQMASK, SVGA_IRQFLAG_FENCE_GOAL);
			x64_cli ();

			if (!svga_has_fence_passed(fence)) {
				svga_ring_doorbell ();
				if (!svga_has_fence_passed(fence)) {
					svga_wait_for_irq();
				}
			}

			svga_write_reg (SVGA_REG_IRQMASK, 0);
	} else {
		bool busy = true;
		svga_write_reg (SVGA_REG_SYNC, 1);

		while (!svga_has_fence_passed (fence) && busy) {
			busy = (svga_read_reg (SVGA_REG_BUSY) != 0);
		}
	}

	if (!svga_has_fence_passed (fence)) {
		//printf ("[VMware SVGA]: SyncToFence failed\n");
	}

}

uint32_t svga_insert_fence () {
	uint32_t fence;

#pragma pack (push)
	struct cmmnd{
		uint32_t id;
		uint32_t fence;
	};
#pragma pack (pop)

	cmmnd *cmd;

	//printf ("Insert fence cmd size -> %d\n", sizeof *cmd);
	if (!svga_has_fifo_cap (SVGA_FIFO_CAP_FENCE)) {
		//printf ("Insert fence no cap\n");
		//return 1;
	}

	if (svga_dev.fifo.next_fence == 0) {
		svga_dev.fifo.next_fence = 1;
	}

	fence = svga_dev.fifo.next_fence++;
	//printf ("Fence -> %x\n", fence);
	cmd = (cmmnd*)svga_fifo_reserve (sizeof *cmd);
	cmd->id = SVGA_CMD_FENCE;
	cmd->fence = fence;

	svga_fifo_commit_all();

	return fence;
}


void svga_wait_for_irq () {
	uint32_t flags = 0;
	do {
		flags = svga_dev.irq.pending;
	}while (flags == 0);
}
/**===============================================================
 ** Interrupt handler
 ** ==============================================================
 */
void svga_interrupt_handler (size_t s, void* p) {
	x64_cli ();
	printf ("SVGA interrupted\n");

	uint16_t port = svga_dev.io_base + SVGA_IRQSTATUS_PORT;
	uint32_t irq_flags = inportd (port);
	outportd (port, irq_flags);
	printf ("Irq flags -> %d\n", irq_flags);
	svga_dev.irq.count++;
	svga_dev.irq.pending = irq_flags;
	
	if (!irq_flags)
		printf ("[VMware SVGA]: spurious SVGA IRQ\n");	
	//svga_update(0,0,get_screen_width(), get_screen_height());
	interrupt_end(svga_dev.irq_line);
}


uint32_t* svga_get_fb_mem () {
	return (uint32_t*)svga_dev.fb_mem;
}
