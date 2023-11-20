#include "mem.h"
#include "global.h"

int32_t lb(uint32_t reg, int32_t cte) {
    int8_t *bytePtr = (int8_t*) mem;
    int32_t loadedData;
    
    if (bytePtr[reg + cte] < 0) {
        int mask = (-1) ^ (255);    // 255 = 2 ** 8 - 1, 8 bits como 1
        loadedData = mask | bytePtr[reg + cte];
    } else
        loadedData = bytePtr[reg + cte];

    return loadedData;
}

int32_t lbu(uint32_t reg, int32_t cte) {
    int8_t *bytePtr = (int8_t*) mem;

    // esse and garante que, n importando a forma como eh feito o casting, os bits depois do 8o vao ser 0
    return bytePtr[reg + cte] & 255;
}

int32_t lh(uint32_t reg, int32_t cte) {
    int16_t *halfPtr = (int16_t*) mem;
    int32_t loadedData;

    if ((reg + cte) % 2 != 0)
        throw "Unaligned address";
    else {
        if (halfPtr[(reg + cte) >> 1] < 0) {
            int mask = ~(65535);                    // 65535 = 2**16 - 1, 16 bits como 1
            loadedData = mask | halfPtr[(reg + cte) >> 1];
        } else 
            loadedData = halfPtr[(reg + cte) >> 1];
    }

    return loadedData;
}

int32_t lhu(uint32_t reg, int32_t cte) {
    int16_t *halfPtr = (int16_t*) mem;

    if ((reg + cte) % 2 != 0)
        throw "Unaligned address";
    else
        return halfPtr[(reg + cte) >> 1] & 65535;
}

int32_t lw(uint32_t reg, int32_t cte) {
    if ((reg + cte) % 4 != 0)
        throw "Unaligned address";
    else
        return mem[(reg + cte) >> 2];
}

void sb(uint32_t reg, int32_t cte, int32_t dado) {
    int8_t *bytePtr = (int8_t*) mem;

    bytePtr[reg + cte] = 255 & dado;
}

void sh(uint32_t reg, int32_t cte, int32_t dado) {
    int16_t *halfPtr = (int16_t*) mem;

    if ((reg + cte) % 2 != 0)
        throw "Unaligned address";
    else
        halfPtr[(reg + cte) >> 1] = 65535 & dado;
}

void sw(uint32_t reg, int32_t cte, int32_t dado) {
    if ((reg + cte) % 4 != 0)
        throw "Unaligned address";
    else
        mem[(reg + cte) >> 2] = dado;
}
