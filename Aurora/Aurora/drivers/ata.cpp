/**
 *   Copyright (C) Manas Kamal Choudhury 2020
 *
 *   ata - Advanced Technology Attachment
 *
 *   /PROJECT - Xeneva v1.0
 *   /AUTHOR  - Manas Kamal Choudhury
 *
 *   ------------------------------------------------
 */

#include <drivers\ata.h>
#include <drivers\pci.h>

uint8_t ata_pm = 0;
uint8_t ide_buf[512];
uint8_t ata_drive;
uint8_t ata_slave_drive;
char    ata_device_name[40];

extern void debug_print(const char *text, ...);

void   ide_select_drive (uint8_t bus, uint8_t i)
{
	if (bus == ATA_PRIMARY )
		if (i == ATA_MASTER)
			outportb(ATA_PRIMARY_IO + ATA_REG_HDDEVSEL, 0xA0);
		else
			outportb(ATA_PRIMARY_IO + ATA_REG_HDDEVSEL, 0xB0);
	else
		if (i == ATA_MASTER)
			outportb(ATA_SECONDARY_IO + ATA_REG_HDDEVSEL, 0xA0);
		else
			outportb(ATA_SECONDARY_IO + ATA_REG_HDDEVSEL, 0xB0);
}


static void ata_wait_busy (uint16_t io)
{
	while (inportb(io + ATA_REG_STATUS) & STATUS_BSY)
		;
}

static void ata_wait_drq (uint16_t io)
{
	while (!(inportb (io + ATA_REG_STATUS) & STATUS_RDY))
		;
}

static void reset_ata_controller (uint16_t io)
{

	outportb (io + ATA_REG_CONTROL, 0x04);
	for (int i=0; i<20; i++)
		;

	ata_wait_busy(io);

	outportb (io + ATA_REG_CONTROL, 0);

	ata_wait_busy (io);

	for (int j = 0; j < 30000000; j++)
		;

}

unsigned int ide_irq_invoked = 0;

void ide_primary_irq (size_t vector, void* param)
{
	ide_irq_invoked = 1;
	AuInterruptEnd(14);
}

void ide_secondary_irq (size_t vector, void* param)
{
	reset_ata_controller (ATA_SECONDARY_IO);
	AuInterruptEnd(15);
}

void ide_wait_irq () {
	while (!ide_irq_invoked)
		;
	ide_irq_invoked = 0;
}

bool  ide_identify (uint8_t bus, uint8_t drive)
{
	ide_select_drive (bus, drive);

	uint16_t  io = bus == ATA_PRIMARY ? ATA_PRIMARY_IO : ATA_SECONDARY_IO;

	outportb(io + ATA_REG_SECCOUNT0, 0);
	outportb(io + ATA_REG_LBA0, 0);
	outportb(io + ATA_REG_LBA1, 0);
	outportb(io + ATA_REG_LBA2, 0);

	// now send identify
	outportb(io + ATA_REG_COMMAND, ATA_CMD_IDENTIFY);

	//! read status port
	uint8_t status = inportb (io + ATA_REG_STATUS );
	if (status)
	{
		while ((inportb(io + ATA_REG_STATUS) & ATA_SR_BSY) != 0);
pm_stat_read:
		status = inportb (io + ATA_REG_STATUS);
		if (status & ATA_SR_ERR)
		{
			printf("ATA: %s s has error. disabled, \n", bus == ATA_PRIMARY ? "primary" : "secondary", 
				drive == ATA_PRIMARY ? "master " : "slave");
			//return false;
		}

		while (! (status & ATA_SR_DRQ))
		{
			goto pm_stat_read;
		}

		for (int i = 0; i < 256;i++ )
		{
			*(uint16_t *) (ide_buf + i*2) = inportw(io + ATA_REG_DATA);
			//("\n%x %x", *(uint16_t*) (ide_buf + i * 2) >> 8, *(uint16_t *)(ide_buf + i * 2) & 0xFF);
		}
		return true;
	}
	else
	{
		//printf("ATA: Status 0\n");
	}
	return false;
}

void  ide_400ns_delay (uint16_t io)
{
	
	for (int i = 0; i < 40; i++)
	{
		uint8_t data = inportb(io + ATA_REG_ALTSTATUS);
	}
}

void  ide_poll (uint16_t io)
{
	for (int i = 0; i < 4; i++)
	{
		inportb (io + ATA_REG_STATUS);
	}
retry:
	uint8_t status = inportb (io + ATA_REG_STATUS);

	if (status & ATA_SR_BSY)
	{
		//kprintf ("\n ATA status busy");
		goto retry;
	}

retry2:
	status = inportb (io + ATA_REG_STATUS);
	if (status & ATA_SR_ERR)
	{
		printf("[ATA]: error!, device failure!\n");
	}

	if (! (status & ATA_SR_DRQ))
	{
		//printf ("[ATA]: Status, drq");
		goto retry2;
	}

	return;
}

uint8_t  ata_write_one (uint8_t *buf, uint32_t lba)
{
	uint16_t io = 0;
	switch (ata_drive)
	{
	case (ATA_PRIMARY << 1 | ATA_MASTER):
		io = ATA_PRIMARY_IO;
		ata_drive = ATA_MASTER;
		break;
	case (ATA_PRIMARY << 1 | ATA_SLAVE):
		io = ATA_PRIMARY_IO;
		ata_drive = ATA_SLAVE;
		break;
	case (ATA_SECONDARY << 1 | ATA_MASTER):
		io = ATA_SECONDARY_IO;
		ata_drive = ATA_MASTER;
		break;
	case (ATA_SECONDARY << 1 | ATA_SLAVE):
		io = ATA_SECONDARY_IO;
		ata_drive = ATA_SLAVE;
		break;
	default:
		return 0;
	}

	uint8_t  cmd = (ata_drive == ATA_MASTER ? 0xE0 : 0xF0);

	ata_wait_busy (io);
	outportb(io + ATA_REG_HDDEVSEL, (cmd | (uint8_t) ((lba >> 24 & 0xFF))));
	outportb(io + 1, 0x00);

	//! single sector write
    outportb(io + ATA_REG_SECCOUNT0, 1);

	//! select LBA
	outportb(io + ATA_REG_LBA0, (uint8_t)((lba)));
	outportb(io + ATA_REG_LBA1, (uint8_t)((lba) >> 8));
	outportb(io + ATA_REG_LBA2, (uint8_t)((lba) >> 16));

	//! select write command
	outportb (io + ATA_REG_COMMAND, ATA_CMD_WRITE_PIO);

	//! wait until ready
	ide_poll(io);

	ata_wait_busy (io);
	ata_wait_drq (io);
	for (int i=0; i < 256; i++)
	{
	
		x64_outportw(io + ATA_REG_DATA, *(uint16_t *)(buf + i * 2));
	}

	ide_400ns_delay (io);
	return 1;
}

uint8_t  ata_read_28 (uint32_t lba, uint16_t sec_count, uint8_t *buf)
{
	//! we only support 28 bit LBA so far
	uint16_t io = 0;
	switch (ata_drive)
	{
	case (ATA_PRIMARY << 1 |  ATA_MASTER):
		io = ATA_PRIMARY_IO;
		ata_drive = ATA_MASTER;
		break;
	case (ATA_PRIMARY << 1 | ATA_SLAVE):
		io = ATA_PRIMARY_IO;
		ata_drive = ATA_SLAVE;
		break;
	case (ATA_SECONDARY << 1 | ATA_MASTER):
		io = ATA_SECONDARY_IO;
		ata_drive = ATA_MASTER;
		break;
	case (ATA_SECONDARY << 1 | ATA_SLAVE):
		io = ATA_SECONDARY_IO;
		ata_drive = ATA_SLAVE;
		break;
	default:{
		printf ("[ATA]: Read28 -- no selected io & drive\n");
		return 0;
	}
	}

	/*printf ("[ATA]: Read28 -- io device selected -> %x\n", io);
	printf ("[ATA]: Read28 -- ata drive selected -> %x\n", ata_drive);*/
	uint8_t cmd = (ata_drive == ATA_MASTER ? 0xE0 : 0xF0);

	ata_wait_busy (io);
	
	outportb (io + ATA_REG_HDDEVSEL, (cmd | (uint8_t) ((lba >> 24 & 0x0F))));
	outportb (io + 1, 0x00);

	//! single sector read
	outportb (io + ATA_REG_SECCOUNT0, sec_count);

	//! select LBA
	outportb (io + ATA_REG_LBA0, (uint8_t)((lba)));
	outportb (io + ATA_REG_LBA1, (uint8_t)((lba) >> 8));
	outportb (io + ATA_REG_LBA2, (uint8_t)((lba) >> 16));

	//! select read command
	outportb (io + ATA_REG_COMMAND, ATA_CMD_READ_PIO);

	//! wait untill ready
	ide_poll (io);
	
	for (int i = 0; i < 256; i++ )
	{
			
	   *(uint16_t*)(buf + i * 2) = inportw (io + ATA_REG_DATA);
    }
	
	
	ide_400ns_delay(io);
	//ide_wait_irq ();
	return 0;
}

void  ata_read_48 (uint64_t lba, uint16_t sector_count, uint8_t *target)
{

	uint16_t io = 0;
	switch (ata_drive)
	{
	case (ATA_PRIMARY << 1 |  ATA_MASTER):
		io = ATA_PRIMARY_IO;
		ata_drive = ATA_MASTER;
		break;
	case (ATA_PRIMARY << 1 | ATA_SLAVE):
		io = ATA_PRIMARY_IO;
		ata_drive = ATA_SLAVE;
		break;
	case (ATA_SECONDARY << 1 | ATA_MASTER):
		io = ATA_SECONDARY_IO;
		ata_drive = ATA_MASTER;
		break;
	case (ATA_SECONDARY << 1 | ATA_SLAVE):
		io = ATA_SECONDARY_IO;
		ata_drive = ATA_SLAVE;
		break;
	default:
		return;
	}

	uint8_t cmd = (ata_drive == ATA_MASTER ? 0x40 : 0x50);

	outportb (io + ATA_REG_HDDEVSEL, cmd);
	outportb (io + ATA_REG_SECCOUNT0, (sector_count >> 8) & 0xFF);
	outportb (io + ATA_REG_LBA0, (lba >> 24) & 0xFF);
	outportb (io + ATA_REG_LBA1, (lba >> 32) & 0xFF);
	outportb (io + ATA_REG_LBA2, (lba >> 40) & 0xFF);
	outportb (io + ATA_REG_SECCOUNT0, sector_count & 0xFF);
	outportb (io + ATA_REG_LBA0, lba & 0xFF);
	outportb (io + ATA_REG_LBA1, (lba >> 8) & 0xFF);
	outportb (io + ATA_REG_LBA2, (lba >> 16) & 0xFF);
	outportb (io + ATA_REG_STATUS, ATA_CMD_READ_PIO_EXT);
	

	ide_poll(io);
	uint8_t i;
	for (i = 0; i < 256; i++)
	{

		 *(uint16_t*)(target + i * 2) = inportw (io + ATA_REG_DATA);
		
	}
    
	ide_400ns_delay(io);
	//kprintf("\nData 48 bit read");
}

uint8_t  ata_slave_read_28 (uint32_t lba, uint16_t sec_count, uint8_t *buf)
{
	//! we only support 28 bit LBA so far
	uint16_t io = 0;
	switch (ata_slave_drive)
	{
	case (ATA_PRIMARY << 1 |  ATA_MASTER):
		io = ATA_PRIMARY_IO;
		ata_slave_drive = ATA_MASTER;
		break;
	case (ATA_PRIMARY << 1 | ATA_SLAVE):
		io = ATA_PRIMARY_IO;
		ata_slave_drive = ATA_SLAVE;
		break;
	case (ATA_SECONDARY << 1 | ATA_MASTER):
		io = ATA_SECONDARY_IO;
		ata_slave_drive = ATA_MASTER;
		break;
	case (ATA_SECONDARY << 1 | ATA_SLAVE):
		io = ATA_SECONDARY_IO;
		ata_slave_drive = ATA_SLAVE;
		break;
	default:
		return 0;
	}

	uint8_t cmd = (ata_slave_drive == ATA_MASTER ? 0xE0 : 0xF0);

	ata_wait_busy (io);
	
	outportb (io + ATA_REG_HDDEVSEL, (cmd | (uint8_t) ((lba >> 24 & 0x0F))));
	outportb (io + 1, 0x00);

	//! single sector read
	outportb (io + ATA_REG_SECCOUNT0, sec_count);

	//! select LBA
	outportb (io + ATA_REG_LBA0, (uint8_t)((lba)));
	outportb (io + ATA_REG_LBA1, (uint8_t)((lba) >> 8));
	outportb (io + ATA_REG_LBA2, (uint8_t)((lba) >> 16));

	//! select read command
	outportb (io + ATA_REG_COMMAND, ATA_CMD_READ_PIO);

	//! wait untill ready
	ide_poll (io);
	
	for (int i = 0; i < 256; i++ )
	{
			
	   *(uint16_t*)(buf + i * 2) = inportw (io + ATA_REG_DATA);
    }
	
	
	ide_400ns_delay(io);
	//ide_wait_irq ();
	return 0;
}

uint8_t  ata_slave_write_one (uint8_t *buf, uint32_t lba)
{
	uint16_t io = 0;
	switch (ata_slave_drive)
	{
	case (ATA_PRIMARY << 1 | ATA_MASTER):
		io = ATA_PRIMARY_IO;
		ata_slave_drive = ATA_MASTER;
		break;
	case (ATA_PRIMARY << 1 | ATA_SLAVE):
		io = ATA_PRIMARY_IO;
		ata_slave_drive = ATA_SLAVE;
		break;
	case (ATA_SECONDARY << 1 | ATA_MASTER):
		io = ATA_SECONDARY_IO;
		ata_slave_drive = ATA_MASTER;
		break;
	case (ATA_SECONDARY << 1 | ATA_SLAVE):
		io = ATA_SECONDARY_IO;
		ata_slave_drive = ATA_SLAVE;
		break;
	default:
		return 0;
	}

	uint8_t  cmd = (ata_slave_drive == ATA_MASTER ? 0xE0 : 0xF0);

	ata_wait_busy (io);
	outportb(io + ATA_REG_HDDEVSEL, (cmd | (uint8_t) ((lba >> 24 & 0xFF))));
	outportb(io + 1, 0x00);

	//! single sector write
    outportb(io + ATA_REG_SECCOUNT0, 1);

	//! select LBA
	outportb(io + ATA_REG_LBA0, (uint8_t)((lba)));
	outportb(io + ATA_REG_LBA1, (uint8_t)((lba) >> 8));
	outportb(io + ATA_REG_LBA2, (uint8_t)((lba) >> 16));

	//! select write command
	outportb (io + ATA_REG_COMMAND, ATA_CMD_WRITE_PIO);

	//! wait until ready
	ide_poll(io);

	ata_wait_busy (io);
	ata_wait_drq (io);
	for (int i=0; i < 256; i++)
	{
	
		x64_outportw(io + ATA_REG_DATA, *(uint16_t *)(buf + i * 2));
	}

	ide_400ns_delay (io);
	return 1;
}


void  ata_probe ()
{
	if (ide_identify (ATA_PRIMARY, ATA_MASTER))
	{
		ata_pm = 1;
		memset (ata_device_name, 0, 40);
		for (int i= 0; i < 40; i += 2)
		{
			ata_device_name[i] = ide_buf[ATA_IDENT_MODEL + i + 1];
			ata_device_name[i + 1] = ide_buf[ATA_IDENT_MODEL + i];
		}

		printf("[ATA]: Primary-Master Device: %s\n", ata_device_name);
		printf("[ATA]: Primary-Master Device Size -> %d GB\n", *((unsigned int*)(ide_buf + 200)) / 1024 / 1024 / 1024);
		ata_drive = (ATA_PRIMARY << 1) | ATA_MASTER;
	}

	if (ide_identify (ATA_PRIMARY, ATA_SLAVE)) {
		//ata_pm = 1;
		memset (ata_device_name, 0, 40);
		for (int i= 0; i < 40; i += 2)
		{
			ata_device_name[i] = ide_buf[ATA_IDENT_MODEL + i + 1];
			ata_device_name[i + 1] = ide_buf[ATA_IDENT_MODEL + i];
		}

		ata_slave_drive = (ATA_PRIMARY << 1) | ATA_SLAVE;
		printf("[ATA]: Primary-Slave Device: %s\n", ata_device_name);
	}
}

void ata_initialize (){

	x64_cli();
/*	pci_device_info info;
	int bus; int dev; int func;
	if (!pci_find_device_class (0x01,0x01,&info,&bus,&dev,&func)) {
		debug_print ("******************************************\n");
		debug_print ("System error!!!!\n");
		debug_print ("Xeneva initialization failed\n");
		debug_print ("Storage IDE mode error, halting system\n");
		debug_print ("******************************************\n");
		for(;;);
	}
	pci_enable_bus_master (bus,dev,func);*/
	
	AuInterruptSet(35, ide_primary_irq, 14, false);

	AuInterruptSet(36, ide_secondary_irq,15, false);

	ata_probe ();

	x64_sti();
}

