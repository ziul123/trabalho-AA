#include "alu.h"
#include "global.h"

int32_t add(int32_t rs, int32_t rt){
	return rs + rt;
}

int32_t sub(int32_t rs, int32_t rt){
	return rs - rt;
}

void mult(int32_t rs, int32_t rt){
	int64_t r = (int64_t) rs * rt;
	lo = (int32_t) r;
	hi = (int32_t) (r >> 32);
}

void _div(int32_t rs, int32_t rt){
	lo = rs / rt;
	hi = rs % rt;
}

int32_t _and(int32_t rs, int32_t rt){
	return rs & rt;
}

int32_t _or(int32_t rs, int32_t rt){
	return rs | rt;
}

int32_t _xor(int32_t rs, int32_t rt){
	return rs ^ rt;
}

int32_t _nor(int32_t rs, int32_t rt){
	return ~(rs | rt);
}

int32_t slt(int32_t rs, int32_t rt){
	return (rs < rt) ? 1 : 0;
}

int32_t sll(int32_t rs, int32_t rt){
	return rs << rt;
}

int32_t srl(int32_t rs, int32_t rt){
	return (rs >> rt) & 0x7FFFFFFF;
}

int32_t sra(int32_t rs, int32_t rt){
	return (int32_t) ((int64_t) rs >> rt);
}

int32_t lui(int16_t imm){
	return ((int32_t) imm) << 16;
}

int32_t addi(int32_t rs, int16_t imm){
	return rs + imm;
}

int32_t slti(int32_t rs, int16_t imm){
	return (rs < imm) ? 1 : 0;
}

int32_t sltiu(int32_t rs, int16_t imm){
	return ((uint32_t) rs < (uint16_t) imm) ? 1 : 0;
}

int32_t andi(int32_t rs, int16_t imm){
	return rs & imm;
}

int32_t ori(int32_t rs, int16_t imm){
	return rs | imm;
}

int32_t xori(int32_t rs, int16_t imm){
	return rs ^ imm;
}

