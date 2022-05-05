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

#ifndef __SHIRQ_H__
#define __SHIRQ_H__

#include <stdint.h>
#include <aurora.h>

/* shirq -- shared irq device */
typedef struct _shirq_ {
	uint8_t irq;
	uint32_t device_id;
	uint32_t vendor_id;
	void (*IrqHandler)(size_t v, void* p);
}shirq_t;


/*
 * AuSharedDeviceInit -- Initialize Shared device manager
 */
extern void AuSharedDeviceInit ();

/*
 * AuSharedDeviceRegister -- Registers a Shared
 * Device
 * @param shdev -- shared device structure pointer
 */
AU_EXTERN AU_EXPORT void AuSharedDeviceRegister (shirq_t *shdev);

/**
 * AuInstallSharedHandler -- Install the shared handler
 * @param irq
 */
AU_EXTERN AU_EXPORT void AuInstallSharedHandler (uint8_t irq);

/*
 * AuCheckSharedDevice -- Checks if already a device with same
 * irq is registered, if yes return true so that we can ReAllocate
 * the SharedIrqHandler, NOTE: device id should be different, because
 * shared device must not have same device id
 * @param irq -- irq to check
 * @param device_id -- unique pci device id
 */
AU_EXTERN AU_EXPORT bool AuCheckSharedDevice(uint8_t irq, uint32_t device_id);


#endif