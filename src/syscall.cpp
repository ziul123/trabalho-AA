#include "syscall.h"
#include "global.h"
#include <stdio.h>
#include <iostream>

void syscall_write_int(){
	printf("%d", regs[4]);
}

void syscall_write_string(){
	char *bytePtr = (char *) mem;
	char *str = bytePtr + regs[4];
	fputs(str, stdout);
}

void syscall_exit(){
	throw 0;
}
