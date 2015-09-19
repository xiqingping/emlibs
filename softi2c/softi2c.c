#include "softi2c_private.h"

static void inline start(const softi2c_t *i2c) {
    i2c->scl(1);
    i2c->sda(1);
    i2c->sda(0);
    i2c->scl(0);
}

static void inline stop(const softi2c_t *i2c) {
    i2c->sda(0);
    i2c->scl(1);
    i2c->sda(1);
}

static char inline onebit(const softi2c_t *i2c, char bit) {
    unsigned char timeout = 0;
    i2c->sda(bit);
    while (i2c->scl(1) == 0) {
        if (timeout++ > 100) {
            break;
        }
    }
    bit = i2c->sda(bit);
    i2c->scl(0);
    return bit;
}

static unsigned char inline onebyte(const softi2c_t *i2c, unsigned char dat) {
    unsigned char ret;
    unsigned char bit;
    for (ret = 0, bit = 0x80; bit != 0x00; bit = bit >> 1) {
        if (onebit(i2c, dat & bit)) {
            ret |= bit;
        }
    }
    return ret;
}


void softi2c_init(const softi2c_t *i2c) {
    i2c->init();
    i2c->sda(1);
    i2c->scl(1);
}



unsigned char softi2c_write(const softi2c_t *i2c, unsigned char addr, const unsigned char *dat, unsigned char len) {
    unsigned char i;

    start(i2c); // start
    onebyte(i2c, addr << 1); // addr + Write
    if (0 != onebit(i2c, 1)) { // check ACK
        return 0;
    }

    for (i = 0; i < len; ++i) {
        onebyte(i2c, *dat++);
        if (0 != onebit(i2c, 1)) { // check ACK
            break;
        }
    }
    stop(i2c);
    return i;
}

unsigned char softi2c_read(const softi2c_t *i2c, unsigned char addr, unsigned char *dat, unsigned char len) {
    unsigned char i;

    start(i2c); // start
    onebyte(i2c, (addr << 1)  + 1); // addr + Write
    if (0 != onebit(i2c, 1)) { // check ACK
        return 0;
    }

    for (i = 0; i < len;) {
        ++i;
        *dat++ = onebyte(i2c, 0xFF);
        onebit(i2c, i == len); // ACK
    }
    stop(i2c);
    return i;
}

