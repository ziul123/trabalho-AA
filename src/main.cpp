#include "mem.h"
#include "mips.h"
#include <systemc.h>
#define MEM_SIZE 4096

int sc_main(int argc, char **argv){
	mips cpu("cpu");
	mem_mips pmem("pmem", MEM_SIZE);
	cpu.pmem(pmem);
	sc_signal<bool> reset;
	cpu.reset(reset);
	pmem.load_mem();

	sc_start();

	pmem.dump_mem(0x0, 0x60, 'h');
	pmem.dump_mem(0x2000, 0x2060, 'h');
	cpu.dump_reg('h');
	return 0;
}
