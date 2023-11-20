#include "branch.h"
#include "global.h"

void beq(int32_t rs, int32_t rt, int16_t offset){
	if (rs == rt)
		pc += (((int32_t) offset) << 2);
}

void bne(int32_t rs, int32_t rt, int16_t offset){
	if (rs != rt)
		pc += (((int32_t) offset) << 2);
}

void blez(int32_t rs, int16_t offset){
	if (rs <= 0)
		pc += (((int32_t) offset) << 2);
}

void bgtz(int32_t rs, int16_t offset){
	if (rs > 0)
		pc += (((int32_t) offset) << 2);
}

void j(uint32_t addr){
	pc = (pc & 0xF0000000) | (addr << 2);
}

void jr(int32_t rs){
	pc = (uint32_t) rs;
}

void jal(uint32_t addr){
	regs[31] = pc;
	pc = (pc & 0xF0000000) | (addr << 2);
}
