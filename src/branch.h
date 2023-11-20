#pragma once
#include <cstdint>

void beq(int32_t rs, int32_t rt, int16_t offset);

void bne(int32_t rs, int32_t rt, int16_t offset);

void blez(int32_t rs, int16_t offset);

void bgtz(int32_t rs, int16_t offset);

void j(uint32_t addr);

void jr(int32_t rs);

void jal(uint32_t addr);
