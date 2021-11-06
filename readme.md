#Aurora's Xeneva
An Operating System fully written from scratch level. It usage UEFI based bootloader called Xnldr {Currently not included here} to boot
the kernel called Aurora. Further Aurora launch the window compositor system process and other applications. Currently applications
are not included here.

Now, EFI-based bootloader called Xnldr is also included in the repository "uefi\bootx64.efi"

#Features:
1. x86_64 based kernel called Aurora Kernel
2. Multitasking / Multi-threading
3. FAT32 file-system with {Read-Write support only on root dir}
4. Driver Loader {loads PE32+ dll files as drivers}
5. Process Manager {loads PE32+ executable as application}
6. Custom system architecture design
7. Custom system call table
8. Graphics support
9. Paging enabled
10. Sound-Blaster 16 audio driver loaded as pre-boot driver dll
11. User Space with multiple address space
12. IPC-Message passing and shared memory message passing
[Userspace]:
13. Window Compositor {with transclucent support}

#Hardware Features
1. e1000 nic [half done]
2. USB xhci [incomplete]
3. HD-Audio 
4. VMware SVGA driver
5. PCI-Express
6. AMD PCnet
7. Legacy PS/2 Keyboard Mouse
6. APIC & IOAPIC support
7. ACPI with shutdown and reset
8. MSI/MSI-X support
9. RTL8139 NIC 
10. AC97 Sound support
11. ATA
12. RTC 
13. VMware mouse support


#Screenshot
![alt text](https://github.com/manaskamal/aurora-xeneva/blob/master/images/xenevaFocus.jpg?raw=true)
![alt text](https://github.com/manaskamal/aurora-xeneva/blob/master/images/RetroXe.jpg.jpg?raw=true)

About Me:
I am Manas Kamal Choudhury from Assam, India. I have been programming since class 6. I am self-taught.
I am interested in system programming and this is my own operating system written from scratch. You can 
contact me through e-mail
gmail:- manaskamal.kandupur@gmail.com