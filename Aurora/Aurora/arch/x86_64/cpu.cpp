/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  cpu.h -- x86_64 cpu initializer
 *
 *  /PROJECT - Aurora v1.0
 *  /AUTHOR  - Manas Kamal Choudhruy
 *
 *===================================================
 */

#include <arch\x86_64\cpu.h>
#include <arch\x86_64\exception.h>
#include <arch\x86_64\user64.h>
#include <arch\x86_64\pic.h>
#include <stdio.h>
#include <arch\x86_64\apic.h>
#include <arch\x86_64\apinit.h>
#include <arch\x86_64\ioapic.h>
#include <arch\x86_64\mmngr\paging.h>
#include <arch\x86_64\pcpu.h>


//! Global Descriptor Table functions
extern "C" uint16_t x64_get_segment_register(size_t reg);
extern "C" void x64_set_segment_register(size_t reg, uint16_t val);
extern "C" void load_default_sregs();
extern "C" void x64_ltr(uint16_t seg);

//! Interrupt Descriptor Table functions
extern "C" void x64_lidt(void* location);
extern "C" void x64_sidt(void* location);
extern "C" void x64_lgdt(void* location);
extern "C" void x64_sgdt(void* location);

extern void debug_print(const char *text, ...);

//! Global Variables GDT
static const size_t GDT_ENTRIES = GDT_ENTRY_MAX;
__declspec(align(4)) static gdt_entry gdt[GDT_ENTRIES];
__declspec(align(4)) static gdtr the_gdtr, old_gdtr;
static uint16_t oldsregs[8];

static bool _fxsave = false;
static bool _xsave = false;

//!==========================================================================================
//! G L O B A L     D E S C R I P T O R    T A B L E 
//!==========================================================================================

void set_gdt_entry(gdt_entry& entry, size_t base, size_t limit, uint8_t access, uint8_t flags)
{
	entry.base_low = base & 0xFFFF;
	entry.base_mid = (base >> 16) & 0xFF;
	entry.base_high = (base >> 24) & 0xFF;
	entry.limit_low = limit & 0xFFFF;
	entry.access = access;
	entry.flags_limit = (flags << 4) | ((limit >> 16) & 0xF);
}

static void set_gdt_entry(gdt_entry& entry, uint8_t access, uint8_t flags)
{
	access |= GDT_ACCESS_PRESENT | GDT_ACCESS_TYPE;
	flags |= GDT_FLAG_GRAN;
	set_gdt_entry(entry, 0, SIZE_MAX, access, flags);
}

static void fill_gdt(gdt_entry* thegdt)
{
	set_gdt_entry(thegdt[GDT_ENTRY_NULL], 0, 0, 0, 0);    //0x00
	//Kernel Code segment: STAR.SYSCALL_CS
	set_gdt_entry(thegdt[GDT_ENTRY_KERNEL_CODE], GDT_ACCESS_PRIVL(0) | GDT_ACCESS_RW | GDT_ACCESS_EX, GDT_FLAG_64BT);  //0x08
	//Kernel Data segment
	set_gdt_entry(thegdt[GDT_ENTRY_KERNEL_DATA], GDT_ACCESS_PRIVL(0) | GDT_ACCESS_RW, GDT_FLAG_32BT);    //0x10
	//User Code segment (32 bit): STAR.SYSRET_CS
	set_gdt_entry(thegdt[GDT_ENTRY_USER_CODE32], GDT_ACCESS_PRIVL(3) | GDT_ACCESS_RW | GDT_ACCESS_EX, GDT_FLAG_32BT);  //0x18
	//User Data segment
	set_gdt_entry(thegdt[GDT_ENTRY_USER_DATA], GDT_ACCESS_PRIVL(3) | GDT_ACCESS_RW, GDT_FLAG_32BT);    //0x20
	//User Code segment (64 bit)
	set_gdt_entry(thegdt[GDT_ENTRY_USER_CODE], GDT_ACCESS_PRIVL(3) | GDT_ACCESS_RW | GDT_ACCESS_EX, GDT_FLAG_64BT);   //0x28  | 3 -- 0x2B
	//Kernel Code segment (32 bit)
	set_gdt_entry(thegdt[GDT_ENTRY_KERNEL_CODE32], GDT_ACCESS_PRIVL(3) | GDT_ACCESS_RW | GDT_ACCESS_EX , GDT_FLAG_32BT);  //0x30
}

void save_sregs()
{
	for (uint_fast8_t reg = 0; reg < 8; ++reg)
		oldsregs[reg] = x64_get_segment_register(reg);
}

void load_default_sregs()
{
	x64_set_segment_register(SREG_CS, SEGVAL(GDT_ENTRY_KERNEL_CODE, 0));		
	x64_set_segment_register(SREG_DS, SEGVAL(GDT_ENTRY_KERNEL_DATA, 0));
	x64_set_segment_register(SREG_ES, SEGVAL(GDT_ENTRY_KERNEL_DATA, 0));
	x64_set_segment_register(SREG_SS, SEGVAL(GDT_ENTRY_KERNEL_DATA, 0));
	//Per CPU data
	x64_set_segment_register(SREG_FS, SEGVAL(GDT_ENTRY_KERNEL_DATA, 0));
	x64_set_segment_register(SREG_GS, SEGVAL(GDT_ENTRY_KERNEL_DATA, 0));
}

//! Initialize the Global Descriptor Table
extern "C" void gdt_initialize()
{
	x64_sgdt(&old_gdtr);
	save_sregs();
	fill_gdt(gdt);
	the_gdtr.gdtaddr = gdt;
	the_gdtr.size = GDT_ENTRIES * sizeof(gdt_entry) - 1;
	x64_lgdt(&the_gdtr);
	load_default_sregs();
}

/*
 * gdt_initialize_ap -- initialize gdt for Application
 * processors
 */
void gdt_initialize_ap() {
	gdtr* new_gdtr = new gdtr;
	gdt_entry* new_gdt = new gdt_entry[GDT_ENTRIES];
	fill_gdt(new_gdt);
	new_gdtr->gdtaddr = new_gdt;
	new_gdtr->size = GDT_ENTRIES * sizeof(gdt_entry) - 1;
	x64_lgdt(new_gdtr);
}


//=====================================================================
// I N T E R R U P T   D E S C R I P T O R   T A B L E
//=====================================================================
static void (*interrupts_handlers[256])(size_t, void*);

extern "C" extern void* default_irq_handlers[];

static void register_irq(IDT* entry, void* function)
{
	size_t faddr = (size_t)function;
	entry->offset_1 = faddr & UINT16_MAX;
	entry->offset_2 = (faddr >> 16) & UINT16_MAX;
	entry->offset_3 = (faddr >> 32) & UINT32_MAX;
}

void setvect(size_t vector, void (*function)(size_t vector, void* param))
{
	interrupts_handlers[vector] = function;
};

extern "C" void interrupt_dispatcher(uint64_t num, interrupt_stack_frame *frame)
{	
	interrupts_handlers[num](num, frame);
	return;
}

static IDT the_idt[256];
void default_irq(size_t vect, void* param){
	x64_cli();
	printf("*** [x64_idt] x64_default_handler: Unhandled Exception *** \n");
	for(;;);
}



void  interrupt_initialize() {
 
	TSS* tss = (TSS*)malloc(sizeof(TSS));
	tss->iomapbase = sizeof(TSS);
	size_t tss_addr = (size_t)tss;

	gdtr curr_gdt;
	x64_sgdt(&curr_gdt);
	gdt_entry* thegdt = the_gdtr.gdtaddr; //curr_gdt.gdtaddr;
	set_gdt_entry(thegdt[GDT_ENTRY_TSS], (tss_addr & UINT32_MAX), sizeof(TSS), GDT_ACCESS_PRESENT | 0x9, 0);
	*(uint64_t*)&thegdt[GDT_ENTRY_TSS + 1] = (tss_addr >> 32);
	x64_ltr(SEGVAL(GDT_ENTRY_TSS, 3));

	AuPCPUSetKernelTSS(tss);

	IDTR *idtr = (IDTR*)malloc(sizeof(IDTR));  //0xFFFFD80000000000;
	idtr->idtaddr = the_idt;
	idtr->length = 256 * sizeof(IDT) - 1;
	x64_lidt(idtr);
	for (int n = 0; n < 256; n++)
	{
		the_idt[n].ist = 0;
		the_idt[n].selector = SEGVAL(GDT_ENTRY_KERNEL_CODE, 0);
		the_idt[n].zero = 0;
		the_idt[n].type_attr = GDT_ACCESS_PRESENT | 0xE;
		register_irq(&the_idt[n], default_irq_handlers[n]);
	}
}

//! the main entry point for HAL of x86_64 arch
void x86_64_gdt_init () {
	//! clear interrupts first
    x64_cli ();

	////! initialize the global descriptor table
	gdt_initialize();

	x64_sti();
}

/*
 * interrupt_initialize_ap -- intialises interrupts for
 * for each APs
 */
void interrupt_initialize_ap() {
	TSS* tss = (TSS*)malloc(sizeof(TSS));
	tss->iomapbase = sizeof(TSS);
	size_t tss_addr = (size_t)tss;

	gdtr curr_gdt;
	x64_sgdt(&curr_gdt);
	gdt_entry* thegdt = curr_gdt.gdtaddr; //curr_gdt.gdtaddr;
	set_gdt_entry(thegdt[GDT_ENTRY_TSS], (tss_addr & UINT32_MAX), sizeof(TSS), GDT_ACCESS_PRESENT | 0x9, 0);
	*(uint64_t*)&thegdt[GDT_ENTRY_TSS + 1] = (tss_addr >> 32);
	x64_ltr(SEGVAL(GDT_ENTRY_TSS, 3));

	

	AuPCPUSetKernelTSS(tss);

	IDTR *idtr = (IDTR*)malloc(sizeof(IDTR));  //0xFFFFD80000000000;
	idtr->idtaddr = the_idt;
	idtr->length = 256 * sizeof(IDT) - 1;
	x64_lidt(idtr);
	for (int n = 0; n < 256; n++)
	{
		the_idt[n].ist = 0;
		the_idt[n].selector = SEGVAL(GDT_ENTRY_KERNEL_CODE, 0);
		the_idt[n].zero = 0;
		the_idt[n].type_attr = GDT_ACCESS_PRESENT | 0xE;
		register_irq(&the_idt[n], default_irq_handlers[n]);
	}
}


static int pit_tick = 0;
void pit_handler_callback (size_t p, void* param) {
	apic_local_eoi();
}


void x86_64_init_cpu () {
	x64_cli();

	AuCreatePCPU(NULL);
	////! initialize the interrupt descriptor table
	interrupt_initialize();

	
	debug_print ("IDT initialized\n");

	x64_sti();
	////! initialize all exception handlers
	exception_init ();

	debug_print ("Exception initialized\n");
	

	//!Initialize APIC   FIXME: Causes triple fault now
	initialize_apic (true);
	
	debug_print ("APIC initialized\n");

//	//!Enable EFER and SYSCALL Extension
	size_t efer = x64_read_msr(IA32_EFER);
	efer |= (1<<11);
	efer |= 1;
	efer |= (1<<0);
	efer |= 1;
	x64_write_msr(IA32_EFER, efer);
	//! now start the interrupts

	debug_print ("EFER.SYSCALL enabled\n");
	//! initialize the user land environment
	initialize_user_land (64);

	debug_print ("User Land Initialized\n");
	//! initialize the syscall entries
	initialize_syscall ();

	debug_print ("System call initialized\n");

	hal_cpu_feature_enable();


    x64_sti ();
	
}


void hal_cpu_feature_enable () {
	uint64_t cr0 = x64_read_cr0();
	cr0 &= ~(1<<2);
	cr0 |= (1<<1);
	x64_write_cr0(cr0);

	size_t a, b, c, d;
	x64_cpuid(1, &a, &b, &c, &d, 0);
	if ((c & (1<<26)) != 0) {
			/* Enable XCR0 register */
		uint64_t cr4 = x64_read_cr4();
		cr4 |= (1 << 18);
		x64_write_cr4(cr4);
	}

	if ((d & (1 << 25)) != 0){
		size_t cr4 = x64_read_cr4();
		

		if ((d & (1 << 24)) != 0) {
			cr4 |= (1 << 9);
			printf("FXSAVE enabled\n");
			_fxsave = true;
		}
		cr4 |= (1 << 10);
		x64_write_cr4(cr4);
	}
	else if ((d & (1 << 26)) != 0) {
		printf("[aurora]: SSE2 is supported \n");
	}
	else if ((c & (1 << 0)) != 0)
		printf("[aurora]: SSE3 is supported \n");
}

bool is_cpu_fxsave_supported () {
	return _fxsave;
}

bool is_cpu_xsave_supported () {
	return _xsave;
}


