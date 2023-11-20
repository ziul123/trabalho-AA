#include "dump.h"
#include "global.h"
#include <iostream>
#include <iomanip>

void dump_mem(int start, int end, char format){
#define MEM_COLS 8
	auto saveFlags = std::cout.flags();
	auto saveFill = std::cout.fill();

	if (format == 'd') {
		std::cout << std::dec << std::noshowbase << std::right << std::setfill(' ');
	} else if (format == 'h') {
		std::cout << std::hex << std::showbase << std::internal << std::setfill('0');
	}

	auto oldFlags = std::cout.flags();
	auto oldFill = std::cout.fill();
	std::cout << "     \t";
	for (int i = 0; i < MEM_COLS; i++) {
		std::stringstream s;
		s << std::hex << std::noshowbase << i*4;
		std::cout  << std::right << std::setfill(' ') << (format=='d'?std::setw(11):std::setw(10)) << "+" + s.str() << " ";
	}
	std::cout << std::endl;
	std::cout.flags(oldFlags);
	std::cout.fill(oldFill);

	for (int j = start; j <= end;) {
		oldFlags = std::cout.flags();
		oldFill = std::cout.fill();
		std::cout << std::hex << std::showbase << std::internal << std::setfill('0') << std::setw(5) << j << "\t";
		std::cout.flags(oldFlags);
		std::cout.fill(oldFill);
		for (int i = 0; i < MEM_COLS; i++) {
			if (j+i*4 > end)
				break;
			std::cout << (format=='d'?std::setw(11):std::setw(10)) << mem[j/4 + i] << " ";
		}
		j += MEM_COLS * 4;
		std::cout << std::endl;
	}

	std::cout.flags(saveFlags);
	std::cout.fill(saveFill);
}

void dump_reg(char format){
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
}
