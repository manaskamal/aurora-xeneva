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

#include <shirq.h>
#include <hal.h>
#include <stdio.h>

shirq_t *shdevice[256];
size_t   shdevice_count = 0;
bool SharedHandlerInstalled;
/*
 * AuSharedDeviceInit -- Initialize Shared device manager
 */
void AuSharedDeviceInit () {
	shdevice_count = 0;
	for (int i = 0; i < 256; i++)
		shdevice[i] = 0;
	SharedHandlerInstalled = false;
}

/*
 * AuSharedDeviceRegister -- Registers a Shared
 * Device
 * @param shdev -- shared device structure pointer
 */
void AuSharedDeviceRegister (shirq_t *shdev) {
	shdevice[shdevice_count] = shdev;
	shdevice_count++;
}


/*
 * AuCheckSharedDevice -- Checks if already a device with same
 * irq is registered, if yes return true so that we can ReAllocate
 * the SharedIrqHandler, NOTE: device id should be different, because
 * shared device must not have same device id
 * @param irq -- irq to check
 * @param device_id -- unique pci device id
 */
bool AuCheckSharedDevice(uint8_t irq, uint32_t device_id) {
	for (int i = 0; i < shdevice_count; i++) {
		shirq_t *shdev = shdevice[i];
		if (shdev->irq == irq && shdev->device_id != device_id)
			return true;
	}
	return false;
}


/*
 * AuSharedHandler -- Shared Device Handler
 */
void AuSharedHandler(size_t v, void* p) {
	x64_cli();
	/* Call each IRQHandler */
	for (int i = 0; i < shdevice_count; i++){
		shirq_t *device = shdevice[i];
		if (device->IrqHandler)
			device->IrqHandler(v,p);
	}
	x64_sti();
	//AuInterruptEnd(0);
}

/**
 * AuInstallSharedHandler -- Install the shared handler
 * @param irq
 */
void AuInstallSharedHandler (uint8_t irq, bool level) {
	if (SharedHandlerInstalled)
		return;
	//AuInterruptSet(irq,AuSharedHandler, irq, level);
	SharedHandlerInstalled = true;
}

void AuFiredSharedHandler (uint8_t irq, size_t v, void* p, shirq_t *fired) {
	for (int i = 0; i < shdevice_count; i++){
		shirq_t* device = shdevice[i];
		if (device->irq == irq && device->IrqHandler != NULL)
			device->IrqHandler(v,p);
	}
}

