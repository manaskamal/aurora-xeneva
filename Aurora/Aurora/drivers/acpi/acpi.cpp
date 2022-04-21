/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *   ACPI.h -- Advanced Configuration and Power Interface
 *
 *  /PROJECT - Aurora Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ============================================================
 */

#include <drivers\acpi\acpi.h>
#include <arch\x86_64\mmngr\paging.h>
#include <arch\x86_64\ioapic.h>
#include <string.h>
#include <pmmngr.h>
#include <stdio.h>
#include <hal.h>


#define POWER_BUTTON_ENABLE  (1<<8)
#define SCI_EN (1<<0)
#define SLP_EN (1<<13)

aurora_acpi kern_acpi;


void acpi_power_button_enable () {
	x64_outportw (kern_acpi.fadt->pm1aEventBlock, (1<<5));
	x64_outportw (kern_acpi.fadt->pm1aEventBlock, (1<<8));
	x64_outportw (kern_acpi.fadt->pm1aEventBlock, (1<<5));
	x64_outportw (kern_acpi.fadt->pm1aEventBlock, POWER_BUTTON_ENABLE);
	x64_outportw (kern_acpi.fadt->pm1aEventBlock, (1<<9));
}

//! Enable ACPI 
void acpi_enable () {
	if (!kern_acpi.fadt || !kern_acpi.fadt->pm1aCtrlBlock) {
		printf ("[ACPI]: data structures are incomplete\n");
		return;
	}
	uint16_t word = x64_inportw(kern_acpi.fadt->pm1aCtrlBlock);
	if ((word & ACPI_PMCTRL_SCI_EN) == 1) {
		printf ("[ACPI]: Already enabled\n");
		return;
	}
	x64_outportb (kern_acpi.fadt->sciCmdPort, kern_acpi.fadt->acpiEnable);
	uint16_t word_1 = x64_inportw(kern_acpi.fadt->pm1aCtrlBlock);	
	printf ("PM1aCTRLBlock -> %x\n", kern_acpi.fadt->pm1aCtrlBlock);
	if ((word_1 & ACPI_PMCTRL_SCI_EN) == 1){

		printf ("[ACPI]: Enabled successfully\n");

	}

	if (kern_acpi.fadt->pm1bCtrlBlock){
		printf ("[ACPI]: Verifying pm1bCtrlBlock \n");
		uint16_t word_3 = x64_inportw(kern_acpi.fadt->pm1bCtrlBlock);
		if ((word_3 & ACPI_PMCTRL_SCI_EN) == 1){
			printf ("[ACPI]: Enabled successfully\n");
		}
	}

	acpi_power_button_enable();
	return;
}


void fadt_handler (size_t v, void* p) {
	printf ("[ACPI]: Fadt interrupt fired\n");
	AuInterruptEnd(9);
}

//! Initialize the acpi data structures
void AuInitializeBasicAcpi (void* acpi_base) {
	memset (&kern_acpi, 0, sizeof(aurora_acpi));
	acpiRsdp *rsdp = (acpiRsdp*)acpi_base;
	acpiRsdt *rsdt = (acpiRsdt*)rsdp->rsdtAddr;
	acpiXsdt *xsdt = (acpiXsdt*)rsdp->xsdtAddr;
	char sig[5];
	int entries = (rsdt->header.length - sizeof(rsdt->header))/4;
	acpiSysDescHeader* header = nullptr;

	for (int count = 0; count < entries; count++) {
		header = (acpiSysDescHeader*)rsdt->entry[count];
		strncpy (sig, header->signature, 4);
		sig[4] = '\0';

		if (!strncmp(sig, ACPI_SIG_FADT, strlen(ACPI_SIG_FADT))) {
			kern_acpi.fadt = (acpiFadt*) header;
			printf ("[ACPI]: Fadt table found\n");
		}
		 
		else if (!strncmp(sig, ACPI_SIG_APIC, strlen("CIPA"))) {
			kern_acpi.madt = (acpiMadt*) header;
			printf ("[ACPI]: Madt table found\n");
			acpi_parse_madt ();
		}

		else if (!strncmp(sig, ACPI_SIG_SRAT, strlen(ACPI_SIG_SRAT))) {
			printf ("[ACPI]: Srat table found\n");
			acpi_table_srat_xe* srat = (acpi_table_srat_xe*)header;
			printf ("[ACPI]: Srat -> %d length -> %d\n", srat->Header.revision, srat->Header.length);
			acpi_sub_table *sub = (acpi_sub_table*)&srat[1];
			while (raw_diff(sub,srat) < srat->Header.length) {
				switch (sub->type) {
				case acpi_srat_type_memory_affinity: {
					printf ("[ACPI]: Srat memory affinity found \n");
					acpi_srat_mem_affinity *mem_affinity = (acpi_srat_mem_affinity*)sub;
					printf ("Mem start -> %x \n", mem_affinity->base_address);
					printf ("Mem end -> %x \n", (mem_affinity->base_address + mem_affinity->length)*4096);
					printf ("Mem Length -> %d MB \n", (mem_affinity->length / 1024 / 1024));
					printf ("Numa Domain -> %d \n", mem_affinity->proximity_domain);
					printf ("Mem LLength -> %d\n", mem_affinity->header.length);
					break;
				}case acpi_srat_type_cpu_affinity:
					printf ("[ACPI]: Srat cpu affinity found \n");
					break;
				case acpi_srat_type_generic_affinity:
					printf ("[ACPI]: Generic affinity found \n");
					break;
				case acpi_srat_type_gicc_affinity:
					printf ("[ACPI]: GICC affinity found \n");
					break;
				case acpi_srat_type_gic_its_affinity:
					printf ("[ACPI]: GIC ITS Affinity found \n");
					break;
				case acpi_srat_type_x2apic_cpu_affinity:
					printf ("[ACPI]: X2APIC CPU Affinity found \n");
					break;
				case acpi_srat_type_reserved:
					printf ("[ACPI]: Srat type reserved \n");
					break;
				}
				sub = raw_offset<acpi_sub_table*>(sub, sub->length);					
			}
		}

		else if (!strncmp(sig, ACPI_SIG_SLIT, strlen(ACPI_SIG_SLIT))) {
			printf ("[ACPI]: Slit table found \n");
		}
		else if (!strncmp(sig, ACPI_SIG_MCFG, strlen(ACPI_SIG_MCFG))) {
			//printf ("[ACPI]: Mcfg table found\n");
			kern_acpi.mcfg = (acpiMcfg*) header;
			acpiMcfgAlloc *allocs = mem_after<acpiMcfgAlloc*>(kern_acpi.mcfg);
			for (; raw_diff(allocs, kern_acpi.mcfg) < kern_acpi.mcfg->header.length; ++allocs) {
				printf ("PCIe Start bus num -> %d, End bus num -> %d, base address-> %x\n", allocs->startBusNum, allocs->endBusNum,
					allocs->baseAddress);
			}
		}
		else if (!strncmp(sig, ACPI_SIG_HPET, strlen(ACPI_SIG_HPET))) {
			printf ("[ACPI]: HPET table found\n");
		}
		else if (!strncmp(sig, ACPI_SIG_MCHI, strlen(ACPI_SIG_MCHI))) {
			printf ("[ACPI]: Management Controller Host Interface Table\n");
		}

	}

	if (kern_acpi.fadt && kern_acpi.fadt->facsAddr) {

		kern_acpi.facs = (acpiFacs*)kern_acpi.fadt->facsAddr;

	}

	if (kern_acpi.fadt && kern_acpi.fadt->dsdtAddr) {

		kern_acpi.dsdt = (acpiDsdt*)kern_acpi.fadt->dsdtAddr;
		printf ("[ACPI]: Dsdt found -> %x\n", kern_acpi.dsdt);
		printf ("[ACPI]: Sci Interrupt -> %d\n", kern_acpi.fadt->sciInt);
		AuInterruptSet(kern_acpi.fadt->sciInt,fadt_handler, kern_acpi.fadt->sciInt);
		uint8_t* S5Block = search_s5(kern_acpi.dsdt);
		if (S5Block != NULL) {
			printf ("S5Block found\n");
			S5Block += 4;
			S5Block += ((*S5Block & 0xC0) >> 6) + 2;
			
			if (*S5Block == 0x0A)
				S5Block++;
			kern_acpi.slp_typa = *S5Block;
			S5Block++;

			if ( *S5Block == 0x0A)
				S5Block++;

			kern_acpi.slp_typb = *S5Block;
			printf ("[ACPI]: SLP_typA -> %x, SLP_typB -> %x\n", kern_acpi.slp_typa, kern_acpi.slp_typb);
		}
	}
	acpi_enable ();
}


//! Parse the MADT Table
void acpi_parse_madt () {
	acpiApicHeader *apic_header = (acpiApicHeader*)kern_acpi.madt->entry;

	while (raw_diff(apic_header, kern_acpi.madt) < kern_acpi.madt->header.length) {
		switch (apic_header->type) {
		case ACPI_APICTYPE_LAPIC: {
			acpiLocalApic *lapic = (acpiLocalApic*)apic_header;
			printf ("[ACPI]: Madt entry -> LAPIC id -> %d, address -> %x\n", lapic->lapicId, lapic->procId);
			if (lapic->procId != 0)
				kern_acpi.num_cpu = lapic->procId;
			break;
		}							 
		case ACPI_APICTYPE_IOAPIC:{
			acpiIoApic *io_apic = (acpiIoApic*)apic_header;
			printf ("[ACPI]: Madt entry -> I/O APIC address -> %x, GSI -> %d\n",io_apic->ioApicAddr, io_apic->gsiBase );
			break;
		}
		case ACPI_APICTYPE_ISOVER:{
			apic_interrupt_override* over = (apic_interrupt_override*)apic_header;
			printf ("[ACPI]: Interrupt Source Override, GSI -> %d, SRC -> %d\n", over->interrupt, over->source);
			break;
		}
		default:{
			break;
		}
		}

		apic_header = raw_offset <acpiApicHeader*>(apic_header, apic_header->length);
	}
}


void acpi_system_reboot () {
	printf ("[ACPI]: Reset Address -> %x, Reset value -> %x\n", kern_acpi.fadt->resetReg.address, kern_acpi.fadt->resetValue);
	x64_outportw (kern_acpi.fadt->resetReg.address, kern_acpi.fadt->resetValue);
}

void acpi_shutdown () {
	x64_cli();
	x64_outportd (kern_acpi.fadt->sciCmdPort, 0);
	if (kern_acpi.fadt->pm1aCtrlBlock != NULL) {
		x64_outportd (kern_acpi.fadt->pm1aCtrlBlock, kern_acpi.slp_typa | SLP_EN);
		printf ("Shutdown step1 complete\n");
	}

	if (kern_acpi.fadt->pm1bCtrlBlock){
		printf ("[ACPI] pm1bCtrlBlock -> %x\n", kern_acpi.fadt->pm1bCtrlBlock);
		x64_outportd (kern_acpi.fadt->pm1bCtrlBlock,  (kern_acpi.slp_typb << 0) | SLP_EN);
	} 

	printf ("\nShutdown step2 complete\n");
	printf ("[ACPI]: Shutdown failed\n");
	for(;;);
}


uint8_t* search_s5 (acpiDsdt* header) {
	uint32_t l;
	uint32_t* S5;

	l = header->header.length - sizeof(acpiDsdt);
	S5 = (uint32_t*)(header + sizeof(acpiDsdt));
	while(l--) {
		if (*S5 == (uint32_t)'_5S_') {
			return (uint8_t*)S5;
		}
		S5 = (uint32_t*)((uint32_t)S5 + 1);
	}

	return (uint8_t*)NULL;
}

//! Checks for PCIe support
bool acpi_pcie_supported () {
	//if (!kern_acpi->mcfg) {
	//	return false;
	//} 
	////! for now let's use pci legacy mode
	//return true;
	return false;
}

//! Get MCFG table
acpiMcfg *acpi_get_mcfg () {
	return kern_acpi.mcfg;
}

/*
 * AuGetNumCPU -- get the total number
 * of cpu
 */
uint8_t AuGetNumCPU () {
	return kern_acpi.num_cpu;
}