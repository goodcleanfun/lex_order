#ifndef LEX_ORDER_H
#define LEX_ORDER_H

#include <stdint.h>
#include <float.h>
#include <limits.h>
#include <math.h>

#include "byte_order/byte_order.h"

static inline void lex_ordered_write_uint16(uint8_t *buffer, uint16_t value) {
    write_uint16_big_endian(buffer, value);
}

static inline uint16_t lex_ordered_read_uint16(uint8_t *buffer) {
    return read_uint16_big_endian(buffer);
}

typedef union {
    uint16_t u;
    int16_t s;
} int16_bits;

static inline void lex_ordered_write_int16(uint8_t *buffer, int16_t value) {
    int16_bits value_bits;
    value_bits.s = value;
    lex_ordered_write_uint16(buffer, value_bits.u ^ 0x8000);
}

static inline int16_t lex_ordered_read_int16(uint8_t *buffer) {
    int16_bits value_bits;
    value_bits.u = lex_ordered_read_uint16(buffer) ^ 0x8000;
    return value_bits.s;
}

static inline void lex_ordered_write_uint32(uint8_t *buffer, uint32_t value) {
    write_uint32_big_endian(buffer, value);
}

static inline uint32_t lex_ordered_read_uint32(uint8_t *buffer) {
    return read_uint32_big_endian(buffer);
}

typedef union {
    uint32_t u;
    int32_t s;
} int32_bits;

static inline void lex_ordered_write_int32(uint8_t *buffer, int32_t value) {
    int32_bits value_bits;
    value_bits.s = value;
    lex_ordered_write_uint32(buffer, value_bits.u ^ 0x80000000);
}

static inline int32_t lex_ordered_read_int32(uint8_t *buffer) {
    int32_bits value_bits;
    value_bits.u = lex_ordered_read_uint32(buffer) ^ 0x80000000;
    return value_bits.s;
}


static inline void lex_ordered_write_uint64(uint8_t *buffer, uint64_t value) {
    write_uint64_big_endian(buffer, value);
}

static inline uint64_t lex_ordered_read_uint64(uint8_t *buffer) {
    return read_uint64_big_endian(buffer);
}

typedef union {
    uint64_t u;
    int64_t s;
} int64_bits;

static inline void lex_ordered_write_int64(uint8_t *buffer, int64_t value) {
    int64_bits value_bits;
    value_bits.s = value;
    lex_ordered_write_uint64(buffer, value_bits.u ^ 0x8000000000000000);
}

static inline int64_t lex_ordered_read_int64(uint8_t *buffer) {
    int64_bits value_bits;
    value_bits.u = lex_ordered_read_uint64(buffer) ^ 0x8000000000000000;
    return value_bits.s;
}

#endif // LEX_ORDER_H