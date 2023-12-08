#pragma once

#include <systemc.h>
#include <cstdint>
#include <cstdlib>
#include "mem_if.h"

struct mem_mips: public sc_module, public mem_if{

	int32_t lb(uint32_t reg, int32_t cte);
	int32_t lbu(uint32_t reg, int32_t cte);
	int32_t lh(uint32_t reg, int32_t cte);
	int32_t lhu(uint32_t reg, int32_t cte);
	int32_t lw(uint32_t reg, int32_t cte);

	void sb(uint32_t reg, int32_t cte, int32_t dado);
	void sh(uint32_t reg, int32_t cte, int32_t dado);
	void sw(uint32_t reg, int32_t cte, int32_t dado);

	void dump_mem(int start, int end, char format);

	void load_mem();

	void reset();

	mem_mips(sc_module_name n, uint32_t size)
	:sc_module(n), _size(size){
		_mem = new int32_t[_size];
	}

	~mem_mips(){
		delete _mem;
	}

	private:
		uint32_t _size;
		int32_t *_mem;

};
