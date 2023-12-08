#pragma once

#include <systemc.h>
#include "mem_if.h"

SC_MODULE(mips){

	sc_port<mem_if> pmem;
	sc_in<bool> reset;
	
	void init();
	void fetch();
	void decode();
	void execute();
	void step();
	void run();
	void dump_reg(char format);

	SC_CTOR(mips){
		SC_THREAD(run);
	}

	private:
		uint32_t pc, ri;
		int32_t hi, lo, regs[32];
		uint8_t opcode, rs, rt, rd, shamnt, func;
		int16_t k16;
		uint32_t k26;

	enum OPCODES {
		EXT=0x00,		LW=0x23,		LB=0x20,		LBU=0x24,
		LH=0x21,		LHU=0x25,		LUI=0x0F,		SW=0x2B,
		SB=0x28,		SH=0x29,		BEQ=0x04,		BNE=0x05,
		BLEZ=0x06,		BGTZ=0x07,		ADDI=0x08,		SLTI=0x0A,
		SLTIU=0x0B,		ANDI=0x0C,		ORI=0x0D,		XORI=0x0E,
		J=0x02,			JAL=0x03
	};

	enum FUNCT {
		ADD=0x20,		SUB=0x22,		MULT=0x18,		DIV=0x1A,
		AND=0x24,		OR=0x25,		XOR=0x26,		NOR=0x27,
		SLT=0x2A,		JR=0x08,		SLL=0x00,		SRL=0x02,
		SRA=0x03,		SYSCALL=0x0C,	MFHI=0x10,		MFLO=0x12
	};

	/********* ULA *********/
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

	/********* BRANCH *********/
	void beq(int32_t rs, int32_t rt, int16_t offset);
	void bne(int32_t rs, int32_t rt, int16_t offset);
	void blez(int32_t rs, int16_t offset);
	void bgtz(int32_t rs, int16_t offset);
	void j(uint32_t addr);
	void jr(int32_t rs);
	void jal(uint32_t addr);

	/********* SYSCALL *********/
	void syscall_write_int();
	void syscall_write_string();
	void syscall_exit();
};
