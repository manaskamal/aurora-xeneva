/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **/

#include <arch\x86_64\cpu.h>
#include <stdio.h>
#include <arch\x86_64\apic.h>
#include <arch\x86_64\pcpu.h>
#include <arch\x86_64\user64.h>

/*
 * AuApInit -- Main entry for Application 
 * Processor
 * @param cpu -- passed by BSP
 */
void AuApInit(void* cpu) {
	x64_cli();
	
	AuCreatePCPU(cpu);
	/* Initialize GDT & Interrupts for each core */
	gdt_initialize_ap();
	interrupt_initialize_ap();
	/* Setup exception for each core */
	exception_init();
	initialize_apic(false);

	size_t efer = x64_read_msr(IA32_EFER);
	efer |= (1<<11);
	efer |= 1;
	efer |= (1<<0);
	efer |= 1;
	x64_write_msr(IA32_EFER, efer);

	initialize_user_land_ap(64);
	initialize_syscall();
	hal_cpu_feature_enable();
	printf ("Welcome to Application Processor %d\n", x86_64_cpu_get_id());

	/* From here scheduler should be initialized with good spinlock
	 * system */
	AuAPStarted();
	for(;;) {
		x64_pause();
	}
}