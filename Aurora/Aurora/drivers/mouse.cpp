/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  mouse.cpp -- Runtime PS2 Mouse Driver
 *
 *  /PROJECT - Aurora {Xeneva v1.0}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===============================================
 */

#include <drivers\mouse.h>
#include <arch\x86_64\thread.h>
#include <screen.h>
#include <ipc\message.h>
#include <ipc\evntsh.h>
#include <ipc\dwm_ipc.h>
#include <drivers\vmmouse.h>
#include <atomic\mutex.h>
#include <vfs.h>

static uint8_t mouse_cycle = 0;
static uint8_t mouse_byte[4];
int32_t  mouse_x = 0;
int32_t  mouse_y = 0;
int32_t  mouse_x_difference = 0;
int32_t  mouse_y_difference = 0;
uint8_t prev_button[3];
uint8_t curr_button[3];
uint32_t mouse_button_state;
volatile int32_t mouse_button = 0;
static mutex_t  *mouse = create_mutex();


void  mouse_wait (uint8_t a_type){
	uint32_t _timer_out_ = 100000;
	if (a_type == 0) {
		while (_timer_out_--){
			if ((x64_inportb(0x64) & 1) == 1){
				return;
			}
		}
		return;
	}else {
		while (_timer_out_--){
			if ((x64_inportb(0x64) & 2) == 0){
				return;
			}
		}
		return;
	}
}

void mouse_write (uint8_t write) {
	mouse_wait (1);
	outportb (0x64, 0xD4);
	mouse_wait (1);
	outportb (0x60, write);
}

uint8_t mouse_read () {
	mouse_wait (0);
	return inportb (0x60);
}

//!Buttons Check up
int left_button_up() {
	return prev_button[0] && !curr_button[0];
}

void mouse_handler (size_t p, void* param) {
	x64_cli();
	set_multi_task_enable (false);
	uint8_t status = inportb (MOUSE_STATUS);
	while ((status & MOUSE_BBIT) && (status & MOUSE_F_BIT)) {
		int8_t mouse_in = inportb (MOUSE_PORT);
		switch (mouse_cycle) {
		case 0:
			mouse_byte[0] = mouse_in;
			if (!(mouse_in & MOUSE_V_BIT)) break;
			++mouse_cycle;
			break;
		case 1:
			mouse_byte[1] = mouse_in;
			++mouse_cycle;
			break;
		case 2:
			mouse_byte[2] = mouse_in;
			goto finish_packet;
		case 3:
			mouse_byte[3] = mouse_in;
			goto finish_packet;
		}

		goto read_next;

finish_packet:
		mouse_cycle = 0;

		int x = mouse_byte[1];
		int y = mouse_byte[2];
		if (x && mouse_byte[0] & ( 1 <<  4)) {
			x = x - 0x100;
		}

		if (y && mouse_byte[0] & (1 << 5)) {
			y = y - 0x100;
		}

		mouse_x_difference = x;
		mouse_y_difference = y;
		mouse_x += mouse_x_difference;
		mouse_y -= mouse_y_difference;

		if (mouse_x < 0)
			mouse_x = 0;

		if (mouse_y < 0)
			mouse_y = 0;

		if (mouse_x > get_screen_width())
			mouse_x = get_screen_width() - 7;

		if (mouse_y > get_screen_height())
			mouse_y = get_screen_height() - 7;

		mouse_button_state = 0;

		if (mouse_byte[0] & 0x01) {    //0x01 for PS/2
			curr_button[0] = 1;
			mouse_button_state |= 1;
		}else
			curr_button[0] = 0;

		if (mouse_byte[0] & 0x02) {
			curr_button[2] = 1;
		}else 
			curr_button[2] = 0;

		if (mouse_byte[0] & 0x04)
			mouse_button |= MOUSE_MIDDLE_CLICK;
		
		//!Pass here the message stream to all waiting processes
	


		//mutex_lock (mouse);
		dwm_message_t msg; // = (dwm_message_t*)pmmngr_alloc();
		msg.type = 1;
		msg.dword = mouse_x;
		msg.dword2 = mouse_y;
		msg.dword4 = mouse_button_state;
		msg.dword5 = mouse_byte[1];
		msg.dword6 = -mouse_byte[2];
		dwm_put_message (&msg);
		//pmmngr_free (msg);
		//mutex_unlock (mouse);

		/*if (left_button_up()) {
			mouse_button_state |= 5;
		}*/


		memcpy (prev_button, curr_button, 3);
		memset (curr_button, 0x00, 3);
read_next:
		break;
	}

	set_multi_task_enable(true);
	interrupt_end(12);
	x64_sti();
}


/**  Mouse IOQuery function **/
int mouse_ioquery (int code, void* arg) {
	switch (code) {
		case MOUSE_IOCODE_DISABLE:
			irq_mask(12,true);
			break;
		case MOUSE_IOCODE_ENABLE:
			irq_mask(12, false);
			break;
		default:
			break;
	}

	return 1;
}


/**
 * Register it to the VFS Subsystem
 */
void mouse_register_device () {
	file_system_t *mouse_file = (file_system_t*)pmmngr_alloc();
	strcpy (mouse_file->name, "IOMOUSE");
	mouse_file->sys_open = NULL;
	mouse_file->sys_read = NULL;
	mouse_file->sys_read_blk = NULL;
	mouse_file->ioquery = mouse_ioquery;
	vfs_register (3,mouse_file);
}

void initialize_mouse () {
	mouse_cycle = 0;
	mouse_x = 0;
	mouse_y = 0;

	uint8_t status;

	mouse_wait (1);
    outportb (0x64, 0xA8);

	mouse_wait(1);
	outportb (0x64, 0x20);

	mouse_wait (0);
	status = (inportb (0x60) | 2);

	mouse_wait (1);
	outportb (0x64, 0x60);

	mouse_wait (1);
	outportb (0x60, status);

	mouse_write (0xF6);
	mouse_read ();

	mouse_write (0xF4);
	mouse_read ();

	interrupt_set (34, mouse_handler, 12);  //34

	mouse_register_device ();
	irq_mask(12, true);
}