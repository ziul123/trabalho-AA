#pragma once
#include <cstdint>

int32_t add(int32_t rs, int32_t rt);

int32_t sub(int32_t rs, int32_t rt);

void mult(int32_t rs, int32_t rt);

void _div(int32_t rs, int32_t rt);

int32_t _and(int32_t rs, int32_t rt);

int32_t _or(int32_t rs, int32_t rt);

int32_t _xor(int32_t rs, int32_t rt);

int32_t _nor(int32_t rs, int32_t rt);

int32_t slt(int32_t rs, int32_t rt);

int32_t sll(int32_t rs, int32_t rt);

int32_t srl(int32_t rs, int32_t rt);

int32_t sra(int32_t rs, int32_t rt);

int32_t lui(int16_t imm);

int32_t addi(int32_t rs, int16_t imm);

int32_t slti(int32_t rs, int16_t imm);

int32_t sltiu(int32_t rs, int16_t imm);

int32_t andi(int32_t rs, int16_t imm);

int32_t ori(int32_t rs, int16_t imm);

int32_t xori(int32_t rs, int16_t imm);

