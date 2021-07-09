/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  user64.h -- User Level code for arch x86_64 
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *====================================================
 */

#include <arch\x86_64\user64.h>

extern "C" void syscall_entry();
extern "C" void x64_syscall_entry_compat();
extern "C" void* x64_get_stack ();
TSS *tss;
//! Initialize the syscall service
void initialize_syscall ()  {
	
	uint64_t syscall_sel = SEGVAL (GDT_ENTRY_KERNEL_CODE, 0);
	uint64_t sysret_sel = SEGVAL (GDT_ENTRY_USER_CODE32, 3);

	x64_write_msr (IA32_STAR, (sysret_sel << 48) | (syscall_sel << 32));
	x64_write_msr (IA32_LSTAR, (size_t)&syscall_entry);
	x64_write_msr (IA32_SFMASK, IA32_EFLAGS_INTR | IA32_EFLAGS_DIRF);
	x64_write_msr (IA32_CSTAR, (size_t)&x64_syscall_entry_compat);
}


//! Set up the user space environment
void initialize_user_land (size_t bit) {

	uint16_t data_sel = SEGVAL (GDT_ENTRY_USER_DATA, 3);
	uint16_t code_sel = 0;
	switch (bit) {
	case 64:
		code_sel = SEGVAL (GDT_ENTRY_USER_CODE, 3);
		break;
	case 32:
		code_sel = SEGVAL (GDT_ENTRY_USER_CODE32, 3);
		break;
	default:
		return;
	}

	gdtr peek_gdt;
	x64_sgdt (&peek_gdt);
	gdt_entry& tss_entry = peek_gdt.gdtaddr[GDT_ENTRY_TSS];

	tss = (TSS*) (tss_entry.base_low + (tss_entry.base_mid << 16) + (tss_entry.base_high << 24) + ((uint64_t)*(uint32_t*)&peek_gdt.gdtaddr[GDT_ENTRY_TSS + 1] << 32));
	
	/*void* esp_stack = x64_get_stack();
	x64_write_msr (IA32_SYSENTER_ESP, (size_t)esp_stack); */
}

TSS* get_kernel_tss () {
	return tss;
}


extern "C" void syscall_debug  (uint64_t rcx) {
	printf ("Syscalled occured\n");
	printf ("Loaded kernel stack is %x\n", rcx);
	for(;;);
}
