# Aurora's Xeneva

Aurora's Xeneva is an operating system completely build from scratch. The system uses x86_64 architecture and can be booted from uefi environment.
The Kernel is known as 'Aurora' with hybrid kernel design and the entire operating system is known as 'Xeneva'. The

In 2020,I started the system as a personal learning project for myself and still it can be considered as a learning project. At very first the system 
used x86 architecture and BIOS to boot from. The design of the kernel was same to the new one. The kernel used little drivers like ps2 mouse, keyboard and vbe for graphics
and a small stack based window manager in the kernel space. In 2021 the the entire system was re-written from scratch with focus on x64 architecture and uefi environment.

Currently the kernel design as hybrid kernel and uses drivers like ps2 mouse, keyboard, acpi, hd-audio, vmware-svga & e1000 network driver. Currently, the ACPI subsystem for kernel 
is in basic level which can shutdown the system and parse the acpi tables. With vmware-svga the graphics capabilities of the system is smoother than the previous kernel.
The system uses Compositing Window Manager for graphical display management which is known as 'Quince'{_named after fruit called 'Quince'}. The Compositing Window Manager runs on
user-space, which provides off-screen buffers to graphical application that request it. The application and Compositing Window Manager communicate using IPC-Message
based channel called Quince Channel. The system also provide a very basic Widget Library with {_Button,Menus,Window,EditBox,TextBox,Scrollbars}. Currently the development for 
Graphics, Sound and the Kernel is going on.

The Goal of the project is to produce a high-quality Operating system with full multimedia support.

## _Features:
1. x64 based Kernel
2. Compositing Window Manager
3. A very basic Widget Library
4. A very basic C Library
5. TrueType fonts
6. ACPI
7. High-Definition Audio
8. Networking (under development)

## _Ported Projects:
1. FreeType 

# Building the project

The project is build on Windows environment. It requires Microsoft Visual Studio 2012 or later.
By downloading the project, one can open the solution file (_.sln) which is configured as per the
project requirements. {_FIXME: The Project directories are need to be manually configured for now}.
Nasm is used as the main assembler. Setup of nasm under Visual Studio is also required.

## _Requirements:
i> Nasm as the assembler
ii> Microsoft Visual Studio 2012 or later
iii> EFI-Based partition to store the Kernel {_'xnkrnl.exe'} and
     the bootloader {_'BOOTx64.efi' -stored in 'uefi directory under the repo'}

## _Project's after build directory structure
   
   --ROOT--
    |
    |-----EFI/BOOT/
    |       |
    |       |----BOOTx64.efi
    |       |----startup.nsh
    |
    |
    |-----EFI/XENEVA/
    |       |
    |       |----font.psf {_Used by the krnl}
    |       |----sb16.dll 
    |       |----xnkrnl.exe {_The core of the system 'The kernel'}
    | 
    |-----quince.exe {_The Compositing Window Manager}
    |-----Forte.ttf  {_True type font}
    |-----river.jpg  {_A Wallpaper of the Brahmaputra River found in North East Assam, India..used as Desktop Wallpaper}
    |----- _etc files




# Screenshot
![alt text](https://github.com/manaskamal/aurora-xeneva/blob/master/images/XenevaFullResolution.jpg?raw=true)

# About Me:
I am Manas Kamal Choudhury from Assam, India. I have been programming since class 6. I am self-taught.
I am interested in system programming and this is my own operating system written from scratch. You can 
contact me through e-mail '_manaskamal.kandupur@gmail.com'