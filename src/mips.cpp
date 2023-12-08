#include "mips.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

void mips::init(){
	pc = 0; ri = 0;
	hi = 0; lo = 0;
	std::fill(regs, regs+32, 0);
	regs[28] = 0x1800;
	regs[29] = 0x3FFC;
}

void mips::fetch(){
	ri = pmem->lw(pc, 0);
	pc += 4;
}

void mips::decode(){
	opcode = (ri >> 26) & 0x03F;
	rs = (ri >> 21) & 0x01F;
	rt = (ri >> 16) & 0x01F;
	rd = (ri >> 11) & 0x01F;
	shamnt = (ri >> 6) & 0x01F;
	func = ri & 0x03F;
	k16 = ri & 0x0FFFF;
	k26 = ri & 0x03FFFFFF;
}

void mips::execute(){
	switch (opcode){
		case EXT:
			switch (func){
				case ADD:
					regs[rd] = add(regs[rs], regs[rt]);
					break;
				case SUB:
					regs[rd] = sub(regs[rs], regs[rt]);
					break;
				case MULT:
					mult(regs[rs], regs[rt]);
					break;
				case DIV:
					div(regs[rs], regs[rt]);
					break;
				case AND:
					regs[rd] = _and(regs[rs], regs[rt]);
					break;
				case OR:
					regs[rd] = _or(regs[rs], regs[rt]);
					break;
				case XOR:
					regs[rd] = _xor(regs[rs], regs[rt]);
					break;
				case NOR:
					regs[rd] = _nor(regs[rs], regs[rt]);
					break;
				case SLT:
					regs[rd] = slt(regs[rs], regs[rt]);
					break;
				case SLL:
					regs[rd] = sll(regs[rs], regs[rt]);
					break;
				case SRL:
					regs[rd] = srl(regs[rs], regs[rt]);
					break;
				case SRA:
					regs[rd] = sra(regs[rs], regs[rt]);
					break;
				case JR:
					jr(regs[rs]);
					break;
				case SYSCALL:
					switch (regs[2]){
						case 1:
							syscall_write_int();
							break;
						case 4:
							syscall_write_string();
							break;
						case 10:
							syscall_exit();
							break;
						default:
							std::cout << "Syscall " << regs[2] << " not supported" << std::endl;
							break;
					}
					break;
				case MFHI:
					regs[rd] = hi;
					break;
				case MFLO:
					regs[rd] = lo;
					break;
				default:
					std::cout << "Funct [" << func << "] for opcode 000000 not supported" << std::endl;
					break;
			}
			break;
		case LW:
			regs[rt] = pmem->lw((uint32_t) regs[rs], k16);
			break;
		case LB:
			regs[rt] = pmem->lb((uint32_t) regs[rs], k16);
			break;
		case LBU:
			regs[rt] = pmem->lbu((uint32_t) regs[rs], k16);
			break;
		case LH:
			regs[rt] = pmem->lh((uint32_t) regs[rs], k16);
			break;
		case LHU:
			regs[rt] = pmem->lhu((uint32_t) regs[rs], k16);
			break;
		case LUI:
			regs[rt] = lui(k16);
			break;
		case SW:
			pmem->sw((uint32_t) regs[rs], k16, regs[rt]);
			break;
		case SB:
			pmem->sb((uint32_t) regs[rs], k16, regs[rt]);
			break;
		case SH:
			pmem->sh((uint32_t) regs[rs], k16, regs[rt]);
			break;
		case BEQ:
			beq(regs[rs], regs[rt], k16);
			break;
		case BNE:
			bne(regs[rs], regs[rt], k16);
			break;
		case BLEZ:
			blez(regs[rs], k16);
			break;
		case BGTZ:
			bgtz(regs[rs], k16);
			break;
		case ADDI:
			regs[rt] = addi(regs[rs], k16);
			break;
		case SLTI:
			regs[rt] = slti(regs[rs], k16);
			break;
		case SLTIU:
			regs[rt] = sltiu(regs[rs], k16);
			break;
		case ANDI:
			regs[rt] = andi(regs[rs], k16);
			break;
		case ORI:
			regs[rt] = ori(regs[rs], k16);
			break;
		case XORI:
			regs[rt] = xori(regs[rs], k16);
			break;
		case J:
			j(k26);
			break;
		case JAL:
			jal(k26);
			break;
		default:
			std::cout << "Opcode [" << opcode << "] not supported" << std::endl;
			break;
	}
	regs[0] = 0;
}

void mips::step(){
	fetch();
	decode();
	execute();
}

void mips::run(){
	init();
	try {
		while (true) {
			step();
			if (pc > 8000)
				throw 1;
		}
	}
	catch (int e) {
		if (e) {
			std::cout << "\nPC exceeded 2k word limit" << std::endl;
		} else {
			std::cout << "\nProgram exited successfully" << std::endl;
		}
	}
	catch (std::string s) {
		std::cout << "\nError at pc = " << std::hex << std::setfill('0') << std::showbase << std::setw(10) << pc-4 << ": " << s << std::endl;
	}
}

void mips::dump_reg(char format){
#define REG_COLS 2
	auto saveFlags = std::cout.flags();
	auto saveFill = std::cout.fill();

	const std::string reg_names[32] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"};

	std::cout << std::right << std::setfill(' ') << std::setw(7) << "pc = " << std::hex << std::showbase << std::internal << std::setfill('0') << std::setw(10) << pc << std::endl;

	if (format == 'd') {
		std::cout << std::dec << std::noshowbase << std::right << std::setfill(' ');
	} else if (format == 'h') {
		std::cout << std::hex << std::showbase << std::internal << std::setfill('0');
	}

	for (int j = 0; j < 32;){
		for (int i = 0; i < REG_COLS; i++){
			auto oldFlags = std::cout.flags();
			auto oldFill = std::cout.fill();
			std::cout << std::setfill(' ') << std::right << std::setw(7) << reg_names[j+i] + " = ";
			std::cout.flags(oldFlags);
			std::cout.fill(oldFill);
			std::cout << (format=='d'?std::setw(11):std::setw(10)) << regs[j+i];
		}
		j += REG_COLS;
		std::cout << std::endl;
	}
	auto oldFlags = std::cout.flags();
	auto oldFill = std::cout.fill();
	std::cout << std::right << std::setfill(' ') << std::setw(7) << "hi = ";
	std::cout.flags(oldFlags);
	std::cout.fill(oldFill);
	std::cout << (format=='d'?std::setw(11):std::setw(10)) << hi;
	oldFlags = std::cout.flags();
	oldFill = std::cout.fill();
	std::cout << std::right << std::setfill(' ') << std::setw(7) << "lo = ";
	std::cout.flags(oldFlags);
	std::cout.fill(oldFill);
	std::cout << (format=='d'?std::setw(11):std::setw(10)) << lo;
	std::cout << std::endl;

	std::cout.flags(saveFlags);
	std::cout.fill(saveFill);
	std::cout << std::endl;
	}
