#pragma once
#include <systemc.h>
#include <cstdint>

struct mem_if: public sc_interface{

	virtual int32_t lb(uint32_t reg, int32_t cte) = 0;
	virtual int32_t lbu(uint32_t reg, int32_t cte) = 0;
	virtual int32_t lh(uint32_t reg, int32_t cte) = 0;
	virtual int32_t lhu(uint32_t reg, int32_t cte) = 0;
	virtual int32_t lw(uint32_t reg, int32_t cte) = 0;

	virtual void sb(uint32_t reg, int32_t cte, int32_t dado) = 0;
	virtual void sh(uint32_t reg, int32_t cte, int32_t dado) = 0;
	virtual void sw(uint32_t reg, int32_t cte, int32_t dado) = 0;

	virtual void reset() = 0;
};
