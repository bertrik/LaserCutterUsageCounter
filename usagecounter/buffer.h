#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

void put8(uint8_t **ppb, uint8_t b);
void put16(uint8_t **ppv, uint16_t w);
void put32(uint8_t **ppv, uint32_t l);
uint8_t get8(uint8_t **ppb);
uint16_t get16(uint8_t **ppv);
uint32_t get32(uint8_t **ppv);

#endif /* BUFFER_H */

