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

#ifndef __CPU_H__
#define __CPU_H__


#include <stdint.h>
//#include <arch\x86_64\apic.h>
#include <aurora.h>

#define GDT_ENTRY_NULL 0
#define GDT_ENTRY_KERNEL_CODE 1
#define GDT_ENTRY_KERNEL_DATA 2
#define GDT_ENTRY_USER_CODE32 3
#define GDT_ENTRY_USER_DATA 4
#define GDT_ENTRY_USER_CODE 5
#define GDT_ENTRY_KERNEL_CODE32 6
#define GDT_ENTRY_TSS 7
#define GDT_ENTRY_MAX 9		//TSS takes two entries



#define SEGVAL(gdtent, rpl) \
	((gdtent << 3) | rpl)

#define SEGVAL_LDT(ldtent, rpl) \
	((ldtent << 3) | 0x4 | rpl)

enum sregs {
	SREG_CS,
	SREG_DS,
	SREG_ES,
	SREG_FS,
	SREG_GS,
	SREG_SS
};

#define GDT_FLAG_GRAN 0x8
#define GDT_FLAG_32BT 0x4
#define GDT_FLAG_64BT 0x2

#define GDT_ACCESS_PRESENT 0x80
#define GDT_ACCESS_PRIVL(x) (x << 5)
#define GDT_ACCESS_TYPE 0x10
#define GDT_ACCESS_EX 0x8
#define GDT_ACCESS_DC 0x4
#define GDT_ACCESS_RW 0x2
#define GDT_ACCESS_AC 0x1

#define MSR_IA32_MTRRCAP 0xFE
#define MSR_IA32_MTRRBASE 0x200
#define MSR_IA32_PAT 0x277
#define MSR_IA32_MTRR_DEF_TYPE 0x2FF

#define MSR_IA32_MISC_ENABLE 0x1A0
#define MSR_IA32_ENERGY_PERF_BIAS 0x1B0
#define MSR_IA32_PERF_CTL 0x199
#define MSR_IA32_PERF_STATUS 0x198
#define MSR_IA32_PM_ENABLE 0x770
#define MSR_IA32_HWP_CAPABILITIES 0x771
#define MSR_IA32_HWP_REQUEST_PKG 0x772
#define MSR_IA32_HWP_INTERRUPT 0x773
#define MSR_IA32_HWP_REQUEST 0x774
#define MSR_IA32_HWP_PECI_REQUEST_INFO 0x775
#define MSR_IA32_HWP_STATUS 0x777
#define MSR_IA32_FS_BASE 0xC0000100
#define MSR_IA32_GS_BASE 0xC0000101
#define MSR_IA32_KERNELGS_BASE 0xC0000102
#define IA32_EFER  0xC0000080

#pragma pack(push, 1)

typedef struct _gdt {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t  base_mid;
	uint8_t  access;
	uint8_t  flags_limit;
	uint8_t  base_high;
}gdt_entry, *pgdt_entry;

typedef struct _gdtr{
	uint16_t size;
	pgdt_entry gdtaddr;
}gdtr, *pgdtr;

#pragma pack(pop)


//! Interrupt Descriptor Table
#pragma pack(push, 1)
typedef struct _idt {
	uint16_t offset_1;
	uint16_t selector;
	uint8_t  ist;
	uint8_t  type_attr;
	uint16_t offset_2;
	uint32_t offset_3;
	uint32_t zero;
}IDT;

typedef struct _idtr {
	uint16_t length;
	void*    idtaddr;
} IDTR;



typedef struct _stack_frame_ {
	_stack_frame_* baseptr;
	size_t  rip;
}stack_frame;


struct interrupt_stack_frame {
	stack_frame* baseptr;
	size_t  error;
	size_t  rip;
	size_t  cs;
	size_t  rflags;
	size_t  rsp;
	size_t  ss;
};
#pragma pack (pop)

#pragma pack(push,1)
typedef struct _fx_state_ {
	uint16_t fcw;
	uint16_t fsw;
	uint8_t ftw;
	uint8_t zero;
	uint16_t fop;
	uint64_t rip;
	uint64_t rdp;
	uint32_t mxcsr;
	uint32_t mxcsrMask;
	uint8_t  st[8][16];
	uint8_t  xmm[16][16];
}fx_state_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _tss {
	uint32_t reserved;
	size_t   rsp[3];
	size_t reserved2;
	size_t   IST[7];
	size_t   resv3;
	uint16_t  resv4;
	uint16_t  iomapbase;
}TSS;
#pragma pack(pop)

#pragma pack(push,1)
/* cpu structure */
typedef struct _cpu_ {
	uint8_t cpu_id;     // 0
	uint64_t*   au_current_thread; // offset -> 1
	TSS*    kernel_tss; //offset -> 9
}cpu_t;
#pragma pack(pop)

//!=======================================================
//! G L O B A L     F U N C T I O N S
//!=======================================================
AU_EXTERN AU_EXPORT void x64_cli ();
AU_EXTERN AU_EXPORT void x64_sti ();
extern "C" void x64_hlt();
//! in & out port functions
extern "C" uint8_t x64_inportb(uint16_t port);
extern "C" uint16_t x64_inportw(uint16_t port);
extern "C" uint32_t x64_inportd(uint16_t port);

extern "C" void x64_outportb(uint16_t port, uint8_t data);
extern "C" void x64_outportw(uint16_t port, uint16_t data);
extern "C" void x64_outportd(uint16_t port, uint32_t data);

//! MSR functions
extern "C" uint64_t x64_read_msr(size_t msr);
extern "C" void x64_write_msr(size_t msr, uint64_t data);

//!Mfench
extern "C" void x64_mfence ();

//!Pause
extern "C" void x64_pause();

//!x64_cpuid
extern "C" void x64_cpuid(size_t page, size_t* a, size_t* b, size_t* c, size_t* d, size_t subpage = 0);

//!Control Register
extern "C" size_t x64_read_cr0();
extern "C" size_t x64_read_cr2();
extern "C" size_t x64_read_cr3();
extern "C" size_t x64_read_cr4();
extern "C" void x64_write_cr0(size_t);
extern "C" void x64_write_cr3(size_t);
extern "C" void x64_write_cr4(size_t);

//!GDT &  IDT Function
extern "C" void x64_lgdt(void* location);
extern "C" void x64_sgdt(void* location);

//! TLB Flush
extern "C" void flush_tlb(void* addr);
extern "C" void cache_flush ();

extern "C" void x64_atom_exchange (size_t r1, size_t r2);

//!------------------------------------
//!  FXSAVE/FXRSTOR
//!------------------------------------
extern "C" void x64_fxsave(uint8_t* location);
extern "C" void x64_fxrstor(uint8_t* location);

/*
 *  FS & GS Base
 */
extern "C" uint8_t x64_fs_readb(size_t offset);
extern "C" uint16_t x64_fs_readw(size_t offset);
extern "C" uint32_t x64_fs_readd(size_t offset);
extern "C" uint64_t x64_fs_readq(size_t offset);
extern "C" void x64_fs_writeb(size_t offset, uint8_t val);
extern "C" void x64_fs_writew(size_t offset, uint16_t val);
extern "C" void x64_fs_writed(size_t offset, uint32_t val);
extern "C" void x64_fs_writeq(size_t offset, uint64_t val);
extern "C" uint8_t x64_gs_readb(size_t offset);
extern "C" uint16_t x64_gs_readw(size_t offset);
extern "C" uint32_t x64_gs_readd(size_t offset);
extern "C" uint64_t x64_gs_readq(size_t offset);
extern "C" void x64_gs_writeb(size_t offset, uint8_t val);
extern "C" void x64_gs_writew(size_t offset, uint16_t val);
extern "C" void x64_gs_writed(size_t offset, uint32_t val);
extern "C" void x64_gs_writeq(size_t offset, uint64_t val);

extern "C" void x64_set_kstack (void* ktss,size_t stack);
extern "C" size_t x64_get_kstack (void* ktss);

//! init -- initializer of x86_64 hal subsystem
extern void x86_64_gdt_init ();
//! setvect -- installs a interrupt vector
AU_EXTERN AU_EXPORT void setvect(size_t vector, void (*function)(size_t vector, void* param));

extern "C" void gdt_initialize();
/*
 * gdt_initialize_ap -- initialize gdt for Application
 * processors
 */
extern void gdt_initialize_ap();
/*
 * interrupt_initialize_ap -- intialises interrupts for
 * for each APs
 */
extern void interrupt_initialize_ap();
extern void  interrupt_initialize();
extern void  interrupt_initialize();
extern void exception_init ();
extern void x86_64_init_cpu ();
extern uint8_t x86_64_cpu_get_id ();
extern void hal_cpu_feature_enable ();
extern bool is_cpu_fxsave_supported ();
extern bool is_cpu_xsave_supported ();
/*
 * cpu_msi_address -- calculates the cpu msi address
 * @param data -- msi data to return
 * @param vector -- interrupt vector number
 * @param processor -- processor number
 * @param edge -- edge triggered or level triggered
 * @param deassert -- deassert bit
 */
extern uint64_t cpu_msi_address (uint64_t* data, size_t vector, uint32_t processor, uint8_t edge, uint8_t deassert);
#endif