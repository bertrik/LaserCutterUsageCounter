
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "buffer.h"
#include "storage.h"

// combines a 22 bit number with 10-bit number
static uint32_t combine(uint32_t life, uint16_t sess)
{
    if (life > 4194303) {
        life = 4194303;
    }
    if (sess > 1023) {
        sess = 1023;
    }
    uint32_t combined;
    combined = (life << 10) | sess;

    return combined;
}

static void extract(uint32_t combined, uint32_t *life, uint16_t *sess)
{
    *life = (combined >> 10) & 0x3FFFFF;
    *sess = (combined & 0x3FF);
}

uint16_t fletcher16( uint8_t const *data, size_t bytes )
{
    uint16_t sum1 = 0xff, sum2 = 0xff;

    while (bytes) {
            size_t tlen = bytes > 20 ? 20 : bytes;
            bytes -= tlen;
            do {
                    sum2 += sum1 += *data++;
            } while (--tlen);
            sum1 = (sum1 & 0xff) + (sum1 >> 8);
            sum2 = (sum2 & 0xff) + (sum2 >> 8);
    }
    /* Second reduction step to reduce sums to 8 bits */
    sum1 = (sum1 & 0xff) + (sum1 >> 8);
    sum2 = (sum2 & 0xff) + (sum2 >> 8);
    return sum2 << 8 | sum1;
}


void encode(counter_t *c, uint8_t *buf)
{
    uint8_t *pb = buf;

    put32(&pb, combine(c->tot_life, c->tot_sess));
    put32(&pb, combine(c->cut_life, c->cut_sess));
    put32(&pb, combine(c->eff_life, c->eff_sess));
    put16(&pb, c->reboots);

    uint16_t checksum = fletcher16(buf, 14);

    put16(&pb, checksum);
}

bool decode(uint8_t *buf, counter_t *c)
{
    // verify checksum first
    uint8_t *pb = &buf[14];
    uint16_t check_exp = fletcher16(buf, 14);
    uint16_t check_act = get16(&pb);
    if (check_exp != check_act) {
        return false;
    }

    pb = buf;
    uint32_t l;
    l = get32(&pb);
    extract(l, &c->tot_life, &c->tot_sess);
    l = get32(&pb);
    extract(l, &c->cut_life, &c->cut_sess);
    l = get32(&pb);
    extract(l, &c->eff_life, &c->eff_sess);
    c->reboots = get16(&pb);
    c->checksum = check_act;

    return true;
}

