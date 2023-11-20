#pragma once
#include <cstdint>

int32_t lb(uint32_t reg, int32_t cte);

int32_t lbu(uint32_t reg, int32_t cte);

int32_t lh(uint32_t reg, int32_t cte);

int32_t lhu(uint32_t reg, int32_t cte);

int32_t lw(uint32_t reg, int32_t cte);

void sb(uint32_t reg, int32_t cte, int32_t dado);

void sh(uint32_t reg, int32_t cte, int32_t dado);

void sw(uint32_t reg, int32_t cte, int32_t dado);
