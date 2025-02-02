#ifndef LEX_ORDER_H
#define LEX_ORDER_H

#include <stdint.h>
#include <float.h>
#include <limits.h>
#include <math.h>

#include "byte_order/byte_order.h"

static inline void lex_ordered_write_int8(uint8_t *buffer, int8_t value) {
    buffer[0] = (uint8_t)(value ^ 0x80);
}

static inline int8_t lex_ordered_read_int8(uint8_t *buffer) {
    return (int8_t)(buffer[0] ^ 0x80);
}

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

typedef union {
    uint32_t u;
    float f;
} float_bits;

static inline void lex_ordered_write_float(uint8_t *buffer, float value) {
    uint32_t encoded;
    if (value == 0) {
        encoded = (1u << 31);
    } else if (isnan(value)) {
        encoded = UINT_MAX;
    } else if (value > FLT_MAX) {
        encoded = UINT_MAX - 1;
    } else if (value < -FLT_MAX) {
        encoded = 0;
    } else {
        float_bits value_bits;
        value_bits.f = value;
        if ((value_bits.u & (1U << 31)) == 0) {
            encoded = value_bits.u | (1U << 31);
        } else {
            encoded = ~value_bits.u;
        }
    }
    write_uint32_big_endian(buffer, encoded);
}


static inline float lex_ordered_read_float(uint8_t *buffer) {
    uint32_t encoded = read_uint32_big_endian(buffer);
    if (encoded == UINT_MAX) {
        return NAN;
    } else if (encoded == UINT_MAX - 1) {
        return INFINITY;
    } else if (encoded == 0) {
        return -INFINITY;
    } else {
        float_bits value_bits;
        if ((encoded & (1U << 31))) {
            value_bits.u = encoded ^ (1U << 31);
        } else {
            // negative
            value_bits.u = ~encoded;
        }
        return value_bits.f;
    }
}

typedef union {
    uint64_t u;
    double d;
} double_bits;

static inline void lex_ordered_write_double(uint8_t *buffer, double value) {
    uint64_t encoded;
    if (value == 0) {
        encoded = (1ULL << 63);
    } else if (isnan(value)) {
        encoded = ULLONG_MAX;
    } else if (value > DBL_MAX) {
        encoded = ULLONG_MAX - 1;
    } else if (value < -DBL_MAX) {
        encoded = 0;
    } else {
        double_bits value_bits;
        value_bits.d = value;
        if ((value_bits.u & (1ULL << 63)) == 0) {
            encoded = value_bits.u | (1ULL << 63);
        } else {
            encoded = ~value_bits.u;
        }
    }
    write_uint64_big_endian(buffer, encoded);
}

static inline double lex_ordered_read_double(uint8_t *buffer) {
    uint64_t encoded = read_uint64_big_endian(buffer);
    if (encoded == ULLONG_MAX) {
        return NAN;
    } else if (encoded == ULLONG_MAX - 1) {
        return INFINITY;
    } else if (encoded == 0) {
        return -INFINITY;
    } else {
        double_bits value_bits;
        if ((encoded & (1ull << 63))) {
            value_bits.u = encoded ^ (1ull << 63);
        } else {
            // negative
            value_bits.u = ~encoded;
        }
        return value_bits.d;
    }
}

#endif // LEX_ORDER_H