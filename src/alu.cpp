#include "mips.h"

int32_t mips::add(int32_t rs, int32_t rt){
	return rs + rt;
}

int32_t mips::sub(int32_t rs, int32_t rt){
	return rs - rt;
}

void mips::mult(int32_t rs, int32_t rt){
	int64_t r = (int64_t) rs * rt;
	lo = (int32_t) r;
	hi = (int32_t) (r >> 32);
}

void mips::_div(int32_t rs, int32_t rt){
	lo = rs / rt;
	hi = rs % rt;
}

int32_t mips::_and(int32_t rs, int32_t rt){
	return rs & rt;
}

int32_t mips::_or(int32_t rs, int32_t rt){
	return rs | rt;
}

int32_t mips::_xor(int32_t rs, int32_t rt){
	return rs ^ rt;
}

int32_t mips::_nor(int32_t rs, int32_t rt){
	return ~(rs | rt);
}

int32_t mips::slt(int32_t rs, int32_t rt){
	return (rs < rt) ? 1 : 0;
}

int32_t mips::sll(int32_t rs, int32_t rt){
	return rs << rt;
}

int32_t mips::srl(int32_t rs, int32_t rt){
	return (rs >> rt) & 0x7FFFFFFF;
}

int32_t mips::sra(int32_t rs, int32_t rt){
	return (int32_t) ((int64_t) rs >> rt);
}

int32_t mips::lui(int16_t imm){
	return ((int32_t) imm) << 16;
}

//TODO cast logic operations to uint32_t

int32_t mips::addi(int32_t rs, int16_t imm){
	return rs + (int32_t) imm;
}

int32_t mips::slti(int32_t rs, int16_t imm){
	return (rs < imm) ? 1 : 0;
}

int32_t mips::sltiu(int32_t rs, int16_t imm){
	return ((uint32_t) rs < (uint16_t) imm) ? 1 : 0;
}

int32_t mips::andi(int32_t rs, int16_t imm){
	return rs & (uint32_t) imm;
}

int32_t mips::ori(int32_t rs, int16_t imm){
	return rs | (uint32_t) imm;
}

int32_t mips::xori(int32_t rs, int16_t imm){
	return rs ^ (uint32_t) imm;
}

