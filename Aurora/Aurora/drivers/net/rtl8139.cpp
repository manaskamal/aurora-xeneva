/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  rtl8139.h -- Realtek 8139 driver for Xeneva
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *=================================================
 */

#include <drivers\net\rtl8139.h>
#include <drivers\pci.h>
#include <stdio.h>

rtl8139_dev *rtl_net_dev;
uint8_t TSAD_Array[4] = {0x20,0x24,0x28,0x2C};
uint8_t TSD_Array[4] = {0x10, 0x14, 0x18,0x1C};
uint32_t current_packet_ptr;


void rtl8139_handler (size_t v, void* p) {
	printf ("***RTL8139: Interrupt fired ***\n");
	uint16_t status = x64_inportw(rtl_net_dev->io_base + 0x3e);

	if (status & ROK) {
		printf ("Receive packet\n");
	}
	x64_outportw (rtl_net_dev->io_base + 0x3E, 0x5);
	interrupt_end(rtl_net_dev->irq);
}

void rtl_read_mac_address () {
	uint32_t mac_part1 = x64_inportd (rtl_net_dev->io_base + 0x00);
	uint16_t mac_part2 = x64_inportw (rtl_net_dev->io_base + 0x04);
	rtl_net_dev->mac_addr[0] = mac_part1 >> 0;
	rtl_net_dev->mac_addr[1] = mac_part1 >> 8;
	rtl_net_dev->mac_addr[2] = mac_part1 >> 16;
	rtl_net_dev->mac_addr[3] = mac_part1 >> 24;

	rtl_net_dev->mac_addr[4] = mac_part2 >> 0;
	rtl_net_dev->mac_addr[5] = mac_part2 >> 8;

	printf ("RTL8192 MAC:");
	for (int i = 0; i < 6; i++){
	 printf (":%x", rtl_net_dev->mac_addr[i]);
	}
	printf ("\n");
}


void rtl_send_packet (void* data, uint32_t len) {
	void *transfar_data = malloc(len);
	void *phys_addr = get_physical_address((uint64_t)transfar_data);

	x64_outportd (rtl_net_dev->io_base + TSAD_Array[rtl_net_dev->tx_cur], (uint32_t)phys_addr);
	x64_outportd (rtl_net_dev->io_base + TSD_Array[rtl_net_dev->tx_cur++], len);
	if (rtl_net_dev->tx_cur > 3)
		rtl_net_dev->tx_cur = 0;
}

void rtl8139_initialize () {
	rtl_net_dev = (rtl8139_dev*)pmmngr_alloc();
	pci_address *dev_addr = (pci_address*)pmmngr_alloc();
	/*if (!pci_find_device (RTL8139_VENDOR_ID,RTL8139_DEVICE_ID,dev_addr)) {
		printf ("Realtek RTL8139 Device not found\n");
		return;
	}*/
	/*uint32_t ret = pci_get_bar_addr(dev_addr, 0);
	rtl_net_dev->bar_type = ret & 0x1;
	rtl_net_dev->io_base = ret & (~0x3);
	rtl_net_dev->mem_base = ret & (~0xf);

	printf ("Realtek RTL8139 Device found, io_addr -> %x, mem_base -> %x\n", rtl_net_dev->io_base, rtl_net_dev->mem_base);
	
	uint32_t irq_num = pci_config_read8 (dev_addr, offsetof (pci_config_space,intr_line));	*/
	//rtl_net_dev->irq = irq_num;
   // interrupt_set (irq_num,rtl8139_handler,irq_num);
	//rtl_net_dev->tx_cur = 0;

	////! enable bus mastering
	//uint32_t pci_command_reg = pci_config_read8 (dev_addr,0x04);
	//printf ("PCI Command reg -> %x\n", pci_command_reg);
	//pci_command_reg |= (1 << 2);
 //   pci_config_write8(dev_addr, 0x04,pci_command_reg);
 //   printf ("RTL8139 Bus Mastering enabled\n");
	//
	//
	//x64_outportb (rtl_net_dev->io_base + 0x52, 0x0);

	////! Soft reset 
	//x64_outportb(rtl_net_dev->io_base + 0x37, 0x10);
	//while ((x64_inportb (rtl_net_dev->io_base + 0x37) & 0x10) != 0) {
	//}
	//
	////! allocate receive buffer
	//rtl_net_dev->rx_buffer = (char*)malloc(8192 + 16 + 1500);
	//memset(rtl_net_dev->rx_buffer, 0x0, 8192 + 16 + 1500);
	//x64_outportd (rtl_net_dev->io_base + 0x30, (uint32_t)get_physical_address((uint64_t)rtl_net_dev->rx_buffer));

	//x64_outportw (rtl_net_dev->io_base + 0x3C, 0x0005);

	//x64_outportd (rtl_net_dev->io_base + 0x44, 0xf | (1 << 7));

	//x64_outportb (rtl_net_dev->io_base + 0x37, 0x0C);

	//
	//printf ("RTL8139 Irq -> %d\n", irq_num);
	//
	//rtl_read_mac_address();

	//rtl_send_packet(NULL, 64);
}