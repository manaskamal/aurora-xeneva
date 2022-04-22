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

#ifndef __PCPU_H__
#define __PCPU_H__

#include <arch\x86_64\thread.h>
#include <stdint.h>


extern cpu_t *AuPCPUGetCpu (uint8_t id);
/*
 * AuCreatePCPU -- Creates a per-cpu data structure
 * @param alloc -- allocation address only for AP's
 */
extern void AuCreatePCPU(void* alloc);

/*
 * AuPCPUSetCPUID -- Sets CPU id for current processor
 * @param id -- cpu id
 */
extern void AuPCPUSetCPUID (uint8_t id);

/*
 * AuPCPUGetCPUID -- Gets CPU id for current processor
 */
extern uint8_t AuPCPUGetCPUID ();
/*
 * AuPCPUSetCurrentThread -- Set Current CPU Current thread
 * @param thread -- thread address
 */
extern void AuPCPUSetCurrentThread (thread_t* thread);

/**
 * AuPCPUGetCurrentThread -- Get the current cpu current thread
 */
extern thread_t* AuPCPUGetCurrentThread();

/** 
 * AuPCPUSetKernelTSS -- Sets Kernel TSS structure
 * @param tss -- pointer to tss structure
 */
extern void AuPCPUSetKernelTSS(TSS *tss);

/**
 * AuPCPUGetKernelTSS -- Gets the kernel TSS structure
 */
extern TSS* AuPCPUGetKernelTSS();

#endif