#include "usagecounter/buffer.h"
#include "usagecounter/storage.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

static void test1(void)
{
    uint8_t buffer[16];
    uint8_t *pb = buffer;
    memset(buffer, 0xFF, sizeof(buffer));

    put8(&pb, 0x01);
    put16(&pb, 0x0203);
    put32(&pb, 0x04050607);

    int i;
    for (i = 0; i < 7; i++) {
        printf(" %02X", buffer[i]);
    }
    printf("\n");

    pb = buffer;
    uint8_t b = get8(&pb);
    uint16_t w = get16(&pb);
    uint32_t l = get32(&pb);

    printf("b = %02X\n", b);
    printf("w = %04X\n", w);
    printf("l = %08X\n", l);
}

static void test2(void)
{
    uint8_t buffer[16];

    counter_t c;
    memset(&c, 0, sizeof(c));
    c.tot_life = 1234;
    c.tot_sess = 17;    
    c.reboots = 18;

    encode(&c, buffer);
    bool ok = decode(buffer, &c);

    printf("ok=%d\n", ok);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    test1();
    printf("test1\n");
    test2();

    return 0;
}
