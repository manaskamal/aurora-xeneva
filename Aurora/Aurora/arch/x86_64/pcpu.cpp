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

#include <arch\x86_64\pcpu.h>
#include <arch\x86_64\cpu.h>
#include <stdio.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <arch\x86_64\thread.h>

cpu_t *cpus[256];
/*
 * AuCreatePCPU -- Creates a per-cpu data structure
 * @param alloc -- allocation address only for AP's
 */
void AuCreatePCPU(void* alloc) {
	cpu_t * cpu;
	if (alloc != 0){
		/* because AP's got already allocated structure */
		cpu = (cpu_t*)alloc;
	}else  {
		cpu = (cpu_t*)malloc(sizeof(cpu_t));
		memset(cpu, 0, sizeof(cpu_t));
	}
	/* if cpu id == 0, means we are in bsp */
	if (cpu->cpu_id == 0)
		cpu->cpu_id = 0;

	cpus[cpu->cpu_id] = cpu;
	x64_write_msr(MSR_IA32_GS_BASE, (uint64_t)cpu);
}

cpu_t *AuPCPUGetCpu (uint8_t id) {
	return cpus[id];
}
/*
 * AuPCPUSetCPUID -- Sets CPU id for current processor
 * @param id -- cpu id
 */
void AuPCPUSetCPUID (uint8_t id) {
	x64_gs_writeb(0,id);
}

/*
 * AuPCPUGetCPUID -- Gets CPU id for current processor
 */
uint8_t AuPCPUGetCPUID () {
	return x64_gs_readb(0);
}
/*
 * AuPCPUSetCurrentThread -- Set Current CPU Current thread
 * @param thread -- thread address
 */
void AuPCPUSetCurrentThread (thread_t* thread) {
	x64_gs_writeq(1,(uint64_t)thread);
}

/**
 * AuPCPUGetCurrentThread -- Get the current cpu current thread
 */
thread_t* AuPCPUGetCurrentThread() {
	return (thread_t*)x64_gs_readq(1);
}

/** 
 * AuPCPUSetKernelTSS -- Sets Kernel TSS structure
 * @param tss -- pointer to tss structure
 */
void AuPCPUSetKernelTSS(TSS *tss) {
	x64_gs_writeq(9,(uint64_t)tss);
}

/**
 * AuPCPUGetKernelTSS -- Gets the kernel TSS structure
 */
TSS* AuPCPUGetKernelTSS() {
	return (TSS*)x64_gs_readq(9);
}




