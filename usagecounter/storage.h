#ifndef STORAGE_H
#define STORAGE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t tot_life;
    uint16_t tot_sess;
    uint32_t cut_life;
    uint16_t cut_sess;
    uint32_t eff_life;
    uint16_t eff_sess;
    uint16_t reboots;
    uint16_t checksum;
} counter_t;

typedef struct {
    uint16_t tot;
    uint16_t cut;
    uint16_t eff;
} seconds_t;

void encode(counter_t *c, uint8_t *buf);
bool decode(uint8_t *buf, counter_t *c);

#endif /* STORAGE_H */

