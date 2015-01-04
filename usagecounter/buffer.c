#include "buffer.h"
#include <stdint.h>

void put8(uint8_t **ppb, uint8_t b)
{
    **ppb = b;
    (*ppb)++;
}

void put16(uint8_t **ppv, uint16_t w)
{
    put8(ppv, (w >> 8) & 0xFF);
    put8(ppv, (w >> 0) & 0xFF);
}

void put32(uint8_t **ppv, uint32_t l)
{
    put16(ppv, (l >> 16) & 0xFFFF);
    put16(ppv, (l >>  0) & 0xFFFF);
}

uint8_t get8(uint8_t **ppb)
{
    uint8_t b = **ppb;
    (*ppb)++;
    return b;
}

uint16_t get16(uint8_t **ppv)
{
    uint16_t w;
    w = (((uint16_t)get8(ppv)) << 8) | (uint16_t)get8(ppv);
    return w;
}

uint32_t get32(uint8_t **ppv)
{
    uint32_t l;
    l = (((uint32_t)get16(ppv)) << 16) | (uint32_t)get16(ppv);
    return l;
}


