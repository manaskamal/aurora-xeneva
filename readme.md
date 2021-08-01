# Aurora's Xeneva
An Operating System fully written from scratch level. It usage UEFI based bootloader called Xnldr {Currently not included here} to boot
the kernel called Aurora. Further Aurora launch the window compositor system process and other applications. Currently applications
are not included here.

Features:
1. x86_64 based kernel called Aurora Kernel
2. Multitasking
3. FAT32 file-system with {Read-Write Files but no mkdir yet}
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
14. Userspace library called libxeneva
15. Applications like {About.exe, Calc.exe,..etc}


#Screenshot
![alt text](https://github.com/manaskamal/aurora-xeneva/blob/master/images/xenevaFocus.jpg?raw=true)
![alt text](https://github.com/manaskamal/aurora-xeneva/blob/master/images/xeneva_transp.jpg?raw=true)

About Me:
I am Manas Kamal Choudhury from Assam, India. I have been programming since class 6. I am self-taught.
I am interested in system programming and this is my own operating system written from scratch. You can 
contact me through e-mail
gmail:- manaskamal.kandupur@gmail.com