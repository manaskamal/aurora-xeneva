///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  signals.h -- Signal ipc
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!--------------------------------------------------


#ifndef __SIGNALS_H__
#define __SIGNALS_H__

#include <stdint.h>

/* Signal names */
#define SIGHUP   1  /*Hangup */
#define SIGINT   2  /*Interrupt */
#define SIGQUIT  3  /*Quit */
#define SIGILL   4  /* Illegal instruction */
#define SIGTRAP  5  /* A breakpoint or trace instruction has been reached */
#define SIGABRT  6  /* Another process has requested that you abort */
#define SIGEMT   7  /* Emulation trap XXX */
#define SIGFPE   8  /* Floating-point arithmetic exception */
#define SIGKILL  9  /* Kill */
#define SIGBUS   10 /* Bus error (device error) */
#define SIGSEGV  11  /* Segmentation fault */
#define SIGSYS   12
#define SIGPIPE  13
#define SIGALRM  14
#define SIGTERM  15
#define SIGUSR1  16
#define SIGUSR2  17
#define SIGCHLD  18
#define SIGPWR   19
#define SIGWINCH 20
#define SIGURG   21
#define SIGPOLL  22
#define SIGSTOP  23
#define SIGTSTP  24
#define SIGCONT  25
#define SIGTTIN  26
#define SIGTTOUT 27
#define SIGVTALRM  28
#define SIGPROF    29
#define SIGXCPU    30
#define SIGXFSZ    31
#define SIGWAITING 32
#define SIGDIAF    33
#define SIGHATE    34
#define SIGWINEVENT 35
#define SIGCAT      36
#define SIGTTOU     37

#define NUMSIGNALS  38
#define NSIG        NUMSIGNALS

///! Handler
typedef void (*sig_handler) (int sig_num);

#endif