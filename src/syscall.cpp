#include "mips.h"
#include <stdio.h>
#include <iostream>

void mips::syscall_write_int(){
	printf("%d", regs[4]);
}

void mips::syscall_write_string(){
	int32_t tmp, i = 0;
	while ((tmp = pmem->lbu(regs[4], i)) != 0){
		printf("%c", tmp);
		i++;
	}
}

void mips::syscall_exit(){
	throw 0;
}
