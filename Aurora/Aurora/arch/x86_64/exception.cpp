/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 * exception -- Exception service of Aurora
 *
 * /PROJECT - Aurora {Xeneva}
 * /AUTHOR  - Manas Kamal Choudhury 2021
 *
 */

#include <arch\x86_64\exception.h>
#include <arch\x86_64\mmngr\vmmngr.h>
#include <arch\x86_64\thread.h>
#include <drivers\svga\vmsvga.h>
#include <screen.h>

void panic(const char* msg,...) {
	printf ("***ARCH x86_64 : Exception Occured ***\n");
	printf ("[Aurora Kernel]: We are sorry to say that, a processor invalid exception has occured\n");
	printf ("[Aurora Kernel]: please inform it to the master of the kernel\n");
	printf ("[Aurora Kernel]: Below is the code of exception\n");
	printf (msg);
}

void divide_by_zero_fault(size_t vector, void* param) {
	x64_cli();
	panic ("\nDivide by 0");
	for(;;);
}

void single_step_trap(size_t vector, void* param) {
	x64_cli();
	interrupt_stack_frame *frame = (interrupt_stack_frame*)param;
	panic ("\nSingle Step Trap");
	for(;;);
}

void nmi_trap (size_t vector, void* param){
	x64_cli();
	panic("\nNMI [Non-Muskable-Interrupt] Trap");
	for(;;);

}

//! exception function breakpoint_trap
void breakpoint_trap (size_t vector, void* param){
	x64_cli();
	panic("\nBreakpoint Trap");
	for(;;);
}

//! exception function -- overflow_trap
void overflow_trap (size_t v, void* p){
	x64_cli();
	panic("\nOverflow Trap");
	for(;;);
}

//! exception function -- bounds_check_fault
void bounds_check_fault (size_t v, void* p){
	x64_cli();
	panic("\nBound Check Fault");
	for(;;);
}

//! exception function -- invalid_opcode_fault
void invalid_opcode_fault (size_t v, void* p){
	x64_cli();
	interrupt_stack_frame *frame = (interrupt_stack_frame*)p;
	panic("Invalid Opcode Fault\n");
	printf ("__PROCESSOR TRACE__\n");
	printf ("RIP -> %x\n",frame->rip);
	printf ("Stack -> %x\n", frame->rsp);
	printf ("RFLAGS -> %x\n", frame->rflags);
	printf ("CS -> %x\n", frame->cs);
	printf ("SS -> %x\n", frame->ss);
	printf ("Current task -> %s\n", get_current_thread()->name);
	for(;;);
}

//! exception function -- no device fault
void no_device_fault (size_t v, void* p){
	x64_cli();
	panic("\nNo Device Fault");
	for(;;);
}

//! exception function -- double fault abort
void double_fault_abort (size_t v, void* p){
	x64_cli();
	panic("\nDouble Fault Abort");
	for(;;);
}

//! exception function -- invalid tss fault
void invalid_tss_fault (size_t v, void* p){
	x64_cli();
	panic("\nInvalid TSS Fault ");
	for(;;);
}

//! exception function -- no_segment_fault
void no_segment_fault (size_t v, void* p){
	x64_cli();
	panic("\nNo Segment Fault");
	for(;;);
}

//! exception function -- stack_fault
void stack_fault (size_t v, void* p){
	x64_cli();
	panic("\nStack Fault at ");
	for(;;);
}

//! exception function --- general protection fault
//   general protection fault is responsible for displaying processor security based error
void general_protection_fault (size_t v, void* p){
	x64_cli();
	interrupt_stack_frame *frame = (interrupt_stack_frame*)p;
	panic ("Genral Protection Fault\n");
	printf ("__PROCESSOR TRACE__\n");
	printf ("RIP -> %x\n",frame->rip);
	printf ("Stack -> %x\n", frame->rsp);
	printf ("RFLAGS -> %x\n", frame->rflags);
	printf ("Current task ->%s\n", get_current_thread()->name);
	printf ("CS -> %x, SS -> %x\n", frame->cs, frame->ss);
    for(;;);
}

//! Most important for good performance is page fault! whenever any memory related errors occurs
//! it get fired and new page swapping process should be allocated

void page_fault (size_t vector, void* param){
	x64_cli();
	interrupt_stack_frame *frame = (interrupt_stack_frame*)param;
	void* vaddr = (void*)x64_read_cr2();

	int present = !(frame->error & 0x1);
	int rw = frame->error & 0x2;
	int us = frame->error & 0x4;
	int resv = frame->error & 0x8;
	int id = frame->error & 0x10;
 //
	
	if (us){
		panic ("Page Fault \n");
		printf ("Faulting Address -> %x\n", vaddr);
		printf ("__PROCESSOR TRACE__\n");
		printf ("RIP -> %x\n", frame->rip);
		printf ("Stack -> %x\n", frame->rsp);
		printf ("RFLAGS -> %x\n", frame->rflags);
		printf ("Current thread -> %s\n", get_current_thread()->name);
		printf ("Current Thread id -> %d\n", get_current_thread()->id);
		printf ("CS -> %x, SS -> %x\n", frame->cs, frame->ss);
		printf ("******Cause********\n");
		printf ("***User Priviledge fault***\n");
		for(;;);
	}else if (present){
		map_page((uint64_t)pmmngr_alloc(), (uint64_t)vaddr);
	}else if (rw) {
		panic ("Page Fault \n");
		printf ("Faulting Address -> %x\n", vaddr);
		printf ("__PROCESSOR TRACE__\n");
		printf ("RIP -> %x\n", frame->rip);
		printf ("Stack -> %x\n", frame->rsp);
		printf ("RFLAGS -> %x\n", frame->rflags);
		printf ("Current thread -> %s\n", get_current_thread()->name);
		printf ("Current Thread id -> %d\n", get_current_thread()->id);
		printf ("CS -> %x, SS -> %x\n", frame->cs, frame->ss);
		printf ("******Cause********\n");
		printf ("*** R/W ***\n");
		for(;;);
	}else if (resv) {
		panic ("Page Fault \n");
		printf ("Faulting Address -> %x\n", vaddr);
		printf ("__PROCESSOR TRACE__\n");
		printf ("RIP -> %x\n", frame->rip);
		printf ("Stack -> %x\n", frame->rsp);
		printf ("RFLAGS -> %x\n", frame->rflags);
		printf ("Current thread -> %s\n", get_current_thread()->name);
		printf ("Current Thread id -> %d\n", get_current_thread()->id);
		printf ("CS -> %x, SS -> %x\n", frame->cs, frame->ss);
		printf ("******Cause********\n");
		printf ("*** Reserved Page ***\n");
		for(;;);
	}else if (id) {
		panic ("Page Fault \n");
		printf ("Faulting Address -> %x\n", vaddr);
		printf ("__PROCESSOR TRACE__\n");
		printf ("RIP -> %x\n", frame->rip);
		printf ("Stack -> %x\n", frame->rsp);
		printf ("RFLAGS -> %x\n", frame->rflags);
		printf ("Current thread -> %s\n", get_current_thread()->name);
		printf ("Current Thread id -> %d\n", get_current_thread()->id);
		printf ("CS -> %x, SS -> %x\n", frame->cs, frame->ss);
		printf ("******Cause********\n");
		printf ("*** Invalid Page ****\n");
		for(;;);
	}
	//map_page((uint64_t)pmmngr_alloc(), (uint64_t)vaddr);
}

//! exception function -- fpu_fault

void fpu_fault (size_t vector, void* p){
	x64_cli();
	panic("\nFPU Fault");
	for(;;);
}

//! exception function -- alignment_check_fault

void alignment_check_fault (size_t v, void* p){
	x64_cli();
	panic("\nAlignment Check Fault at address ");
	for(;;);
}

//! exception function -- machine_check_abort
void machine_check_abort (size_t v, void* p){
	x64_cli();
	panic("\nMachine Check Abort");
	for(;;);
}

//! exception function -- simd related fault handler
 void simd_fpu_fault (size_t v, void* p){
	 x64_cli();
	 panic("\nSIMD FPU Fault");
	 for(;;);
 }

 void exception_init () {
	 x64_cli ();
	 setvect(0,divide_by_zero_fault);
	 setvect(1,single_step_trap);
	 setvect(2,nmi_trap);
	 setvect(3,breakpoint_trap);
	 setvect(4,overflow_trap);
	 setvect(5,bounds_check_fault);
	 setvect(6,invalid_opcode_fault);
	 setvect(7, no_device_fault);
	 setvect(8, double_fault_abort);
	 setvect(10, invalid_tss_fault);
	 setvect(11, no_segment_fault);
	 setvect(12, stack_fault);
	 setvect(13, general_protection_fault);
	 setvect(14, page_fault);
	 setvect(16, fpu_fault);
	 setvect(17, alignment_check_fault);
	 setvect(18, machine_check_abort);
	 setvect(19, simd_fpu_fault);
	 x64_sti();
 }


