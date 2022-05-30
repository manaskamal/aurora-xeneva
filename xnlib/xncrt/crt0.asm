

extern XeMain
extern sys_exit
extern sys_link_libs

section .text
[BITS 64]

global _start
_start:
     mov rsi, rcx
	 mov rdi, rdx

	 sub rsp, 32
	 call sys_link_libs
	 add rsp, 32

	 sub rsp, 32
	 mov rcx, rsi
	 mov rdx, rdi
	 call XeMain
	 add rsp, 32

	 ;;//exit process
	 ;;//with a return code
	 call sys_exit

