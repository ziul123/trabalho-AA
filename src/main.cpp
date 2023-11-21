#include "global.h"
#include "mem.h"
#include "alu.h"
#include "syscall.h"
#include "branch.h" 
#include "dump.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#define MEM_SIZE 4096

int32_t mem[MEM_SIZE] = { 0 };
uint32_t pc = 0, ri = 0;
int32_t hi = 0, lo = 0, regs[32] = { 0 };
uint8_t opcode, rs, rt, rd, shamnt, func;
int16_t k16;
uint32_t k26;


void load_mem(){
#define TEXT_SIZE 0x2000
#define DATA_SIZE 0x2000//MEM_SIZE * 4 - TEXT_SIZE
	std::ifstream text, data;
	char text_buf[TEXT_SIZE] = { 0 };
	char data_buf[DATA_SIZE] = { 0 };
	text.open("text.bin", ios::in | ios::binary);
	text.read(text_buf, TEXT_SIZE);
	text.close();
	data.open("data.bin", ios::in | ios::binary);
	data.read(data_buf, DATA_SIZE);
	data.close();

	int32_t *wordPtr = (int32_t *) text_buf;
	for (int i = 0; i < TEXT_SIZE / 4; i++)
		mem[i] = wordPtr[i];

	wordPtr = (int32_t *) data_buf;
	for (int i = 0; i < DATA_SIZE / 4; i++)
		mem[0x2000/4 + i] = wordPtr[i];
}

void fetch(){
	ri = mem[pc/4];
	pc += 4;
}

void decode(){
	opcode = (ri >> 26) & 0x03F;
	rs = (ri >> 21) & 0x01F;
	rt = (ri >> 16) & 0x01F;
	rd = (ri >> 11) & 0x01F;
	shamnt = (ri >> 6) & 0x01F;
	func = ri & 0x03F;
	k16 = ri & 0x0FFFF;
	k26 = ri & 0x03FFFFFF;
}

void execute(){
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
			regs[rt] = lw((uint32_t) regs[rs], k16);
			break;
		case LB:
			regs[rt] = lb((uint32_t) regs[rs], k16);
			break;
		case LBU:
			regs[rt] = lbu((uint32_t) regs[rs], k16);
			break;
		case LH:
			regs[rt] = lh((uint32_t) regs[rs], k16);
			break;
		case LHU:
			regs[rt] = lhu((uint32_t) regs[rs], k16);
			break;
		case LUI:
			regs[rt] = lui(k16);
			break;
		case SW:
			sw((uint32_t) regs[rs], k16, regs[rt]);
			break;
		case SB:
			sb((uint32_t) regs[rs], k16, regs[rt]);
			break;
		case SH:
			sh((uint32_t) regs[rs], k16, regs[rt]);
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

void step(){
	fetch();
	decode();
	execute();
}

void run(){
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

int main(int argc, char **argv){
	load_mem();
/*	
	while (true) {
		step();
		dump_reg('h');
		char c;
		std::cin >> c;
		if (c == 's')
			break;
	}
*/	
	run();
	dump_mem(0x0, 0x60, 'h');
	dump_mem(0x2000, 0x2060, 'h');
	dump_reg('h');
}
