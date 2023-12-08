#include "mem.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>

int32_t mem_mips::lb(uint32_t reg, int32_t cte) {
    int8_t *bytePtr = (int8_t*) _mem;
    int32_t loadedData;
    
    if (bytePtr[reg + cte] < 0) {
        int mask = (-1) ^ (255);    // 255 = 2 ** 8 - 1, 8 bits como 1
        loadedData = mask | bytePtr[reg + cte];
    } else
        loadedData = bytePtr[reg + cte];

    return loadedData;
}

int32_t mem_mips::lbu(uint32_t reg, int32_t cte) {
    int8_t *bytePtr = (int8_t*) _mem;

    // esse and garante que, n importando a forma como eh feito o casting, os bits depois do 8o vao ser 0
    return bytePtr[reg + cte] & 255;
}

int32_t mem_mips::lh(uint32_t reg, int32_t cte) {
    int16_t *halfPtr = (int16_t*) _mem;
    int32_t loadedData;

    if ((reg + cte) % 2 != 0)
        throw std::string("Unaligned address");
    else {
        if (halfPtr[(reg + cte) >> 1] < 0) {
            int mask = ~(65535);                    // 65535 = 2**16 - 1, 16 bits como 1
            loadedData = mask | halfPtr[(reg + cte) >> 1];
        } else 
            loadedData = halfPtr[(reg + cte) >> 1];
    }

    return loadedData;
}

int32_t mem_mips::lhu(uint32_t reg, int32_t cte) {
    int16_t *halfPtr = (int16_t*) _mem;

    if ((reg + cte) % 2 != 0)
        throw std::string("Unaligned address");
    else
        return halfPtr[(reg + cte) >> 1] & 65535;
}

int32_t mem_mips::lw(uint32_t reg, int32_t cte) {
    if ((reg + cte) % 4 != 0)
        throw std::string("Unaligned address");
    else
        return _mem[(reg + cte) >> 2];
}

void mem_mips::sb(uint32_t reg, int32_t cte, int32_t dado) {
    int8_t *bytePtr = (int8_t*) _mem;

    bytePtr[reg + cte] = 255 & dado;
}

void mem_mips::sh(uint32_t reg, int32_t cte, int32_t dado) {
    int16_t *halfPtr = (int16_t*) _mem;

    if ((reg + cte) % 2 != 0)
        throw std::string("Unaligned address");
    else
        halfPtr[(reg + cte) >> 1] = 65535 & dado;
}

void mem_mips::sw(uint32_t reg, int32_t cte, int32_t dado) {
    if ((reg + cte) % 4 != 0)
        throw std::string("Unaligned address");
    else
        _mem[(reg + cte) >> 2] = dado;
}

void mem_mips::load_mem(){
#define TEXT_SIZE 0x2000
#define DATA_SIZE 0x2000	//MEM_SIZE * 4 - TEXT_SIZE
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
		_mem[i] = wordPtr[i];

	wordPtr = (int32_t *) data_buf;
	for (int i = 0; i < DATA_SIZE / 4; i++)
		_mem[0x2000/4 + i] = wordPtr[i];
}

void mem_mips::dump_mem(int start, int end, char format){
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
			std::cout << (format=='d'?std::setw(11):std::setw(10)) << _mem[j/4 + i] << " ";
		}
		j += MEM_COLS * 4;
		std::cout << std::endl;
	}

	std::cout.flags(saveFlags);
	std::cout.fill(saveFill);
	std::cout << std::endl;
}

void mem_mips::reset(){
	std::fill(_mem, _mem+_size, 0);
}
