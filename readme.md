![alt text](https://github.com/manaskamal/aurora-xeneva/blob/master/images/XELogo.jpg?raw=true)

# Latest Updates

## [Moved to new repository, new rewritten version of Xeneva is here ]( https://github.com/manaskamal/XenevaOS )


# Aurora's Xeneva

Aurora's Xeneva is an operating system completely build from scratch. The system uses x86_64 architecture and can be booted from uefi environment.
The Kernel is known as _'Aurora'_ with hybrid kernel design and the entire operating system is known as _'Xeneva'_. The


## __Features__:
1. x64 based Kernel
2. Compositing Window Manager
3. A very basic Widget Library
4. A very basic C Library
5. TrueType fonts
6. ACPI (basic)
7. High-Definition Audio
8. Basic Networking (under development)
9. Driver Manager (_loading and linking dll files as drivers_)
10. Fully Higher half with MMIO mappings
11. Multiprocessor support (multiprocessor scheduler not ready!!)
12. Software Audio Mixer 
13. Dynamic Library (Shared Library)
14. SSE/SSE2
15. USB3

## __Ported Projects__:
1. FreeType 

# Building the project

The project is build on Windows environment. It requires Microsoft Visual Studio 2012 or later.
By downloading the project, one can open the solution file (_.sln_) which is configured as per the
project requirements. {_FIXME: The Project directories are need to be manually configured for now_}.
Nasm is used as the main assembler. Setup of nasm under Visual Studio is also required.

## __Requirements__:

i> Nasm as the assembler <br>
ii> Microsoft Visual Studio 2012 or later <br>
iii> EFI-Based partition to store the Kernel {_'xnkrnl.exe'_} and
     the bootloader {_'BOOTx64.efi' - stored in 'uefi directory under the repo'_}


## __Project Directory Structures:__
__Aurora/Aurora/__ -- The main kernel directory <br>
__Aurora/PriWM/__ -- PriWM Compositor directory <br>
__Aurora/include/__ -- inlcude directory <br>
__Drivers/__ -- Drivers Project directories. <br>
__images/__ -- Screenshots directory <br>
__uefi/__ -- UEFI required headers directory <br>
__xnlib/lib64/__ -- Xeneva required static libraries <br>
__xnlib/xnacrylic/__ -- Xeneva Graphics libraries <br>
__xnlib/xnclib/__ -- C library  <br>


## __Creating and Using Drivers inside Aurora__
_Please refer to __"Drivers/"__ directory_


# Screenshot
![alt text](https://github.com/manaskamal/aurora-xeneva/blob/master/images/XENEVA64-2022-11-04-18-07-25.png?raw=true)
                             _Aurora's Xeneva in 1024x768 resolution_

# About Me:
I am Manas Kamal Choudhury from Assam, India. I have been programming since class 6. I am self-taught.
I am interested in system programming and this is my own operating system written from scratch. You can 
contact me through e-mail _'manaskamal.kandupur@gmail.com'_