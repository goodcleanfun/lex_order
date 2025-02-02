#include <stdint.h>
#include <string.h>
#include "greatest/greatest.h"

#include "lex_order.h"

TEST test_lex_order(void) {
    int8_t c = -1;
    uint8_t buf8n[1];
    lex_ordered_write_int8(buf8n, c);
    ASSERT_EQ(lex_ordered_read_int8(buf8n), c);

    c = 0;
    uint8_t buf8z[1];
    lex_ordered_write_int8(buf8z, c);
    ASSERT_EQ(lex_ordered_read_int8(buf8z), c);

    c = 1;
    uint8_t buf8[1];
    lex_ordered_write_int8(buf8, c);
    ASSERT_EQ(lex_ordered_read_int8(buf8), c);

    // Test that negative signed integers are lexicographically
    // less than zero or positive signed integers
    ASSERT(strcmp((char *)buf8n, (char *)buf8z) < 0);
    ASSERT(strcmp((char *)buf8n, (char *)buf8) < 0);

    uint8_t buf16u[2];
    
    uint16_t unsigned_short_tests[] = {0, 1234, 0x8000, 0x8001, 0xFFFF};
    for (size_t i = 0; i < sizeof(unsigned_short_tests) / sizeof(uint16_t); i++) {
        lex_ordered_write_uint16(buf16u, unsigned_short_tests[i]);
        ASSERT_EQ(lex_ordered_read_uint16(buf16u), unsigned_short_tests[i]);
    }

    int16_t s = -1234;
    uint8_t buf16n[2];
    lex_ordered_write_int16(buf16n, s);
    ASSERT_EQ(lex_ordered_read_int16(buf16n), s);
    
    s = 0;
    uint8_t buf16z[2];
    lex_ordered_write_int16(buf16z, s);
    ASSERT_EQ(lex_ordered_read_int16(buf16z), s);

    s = 1234;
    uint8_t buf16[2];
    lex_ordered_write_int16(buf16, s);
    ASSERT_EQ(lex_ordered_read_int16(buf16), s);

    // Test that negative signed integers are lexicographically
    // less than zero or positive signed integers
    ASSERT(strcmp((char *)buf16n, (char *)buf16z) < 0);
    ASSERT(strcmp((char *)buf16n, (char *)buf16) < 0);
    ASSERT(strcmp((char *)buf16z, (char *)buf16) < 0);

    uint8_t buf32u[4];
    uint32_t unsigned_int_tests[] = {0, 1234, 0x80000000, 0x80000001, 0xFFFFFFFF};
    for (size_t i = 0; i < sizeof(unsigned_int_tests) / sizeof(uint32_t); i++) {
        lex_ordered_write_uint32(buf32u, unsigned_int_tests[i]);
        ASSERT_EQ(lex_ordered_read_uint32(buf32u), unsigned_int_tests[i]);
    }

    int32_t i = -123456789;
    uint8_t buf32n[4];
    lex_ordered_write_int32(buf32n, i);
    ASSERT_EQ(lex_ordered_read_int32(buf32n), i);

    i = 0;
    uint8_t buf32z[4];
    lex_ordered_write_int32(buf32z, i);
    ASSERT_EQ(lex_ordered_read_int32(buf32z), i);

    i = 123456789;
    uint8_t buf32[4];
    lex_ordered_write_int32(buf32, i);
    ASSERT_EQ(lex_ordered_read_int32(buf32), i);

    // Test that negative signed integers are lexicographically
    // less than zero or positive signed integers
    ASSERT(strcmp((char *)buf32n, (char *)buf32z) < 0);
    ASSERT(strcmp((char *)buf32n, (char *)buf32) < 0);
    ASSERT(strcmp((char *)buf32z, (char *)buf32) < 0);

    uint8_t buf64u[8];
    uint64_t unsigned_long_tests[] = {0, 1234, 0x8000000000000000, 0x8000000000000001, 0xFFFFFFFFFFFFFFFF};
    for (size_t i = 0; i < sizeof(unsigned_long_tests) / sizeof(uint64_t); i++) {
        lex_ordered_write_uint64(buf64u, unsigned_long_tests[i]);
        ASSERT_EQ(lex_ordered_read_uint64(buf64u), unsigned_long_tests[i]);
    }

    int64_t l = -1234567890123456789;
    uint8_t buf64n[8];
    lex_ordered_write_int64(buf64n, l);
    ASSERT_EQ(lex_ordered_read_int64(buf64n), l);
    
    l = 0;
    uint8_t buf64z[8];
    lex_ordered_write_int64(buf64z, l);
    ASSERT_EQ(lex_ordered_read_int64(buf64z), l);

    l = 1234567890123456789;
    uint8_t buf64[8];
    lex_ordered_write_int64(buf64, l);
    ASSERT_EQ(lex_ordered_read_int64(buf64), l);

    // Test that negative signed integers are lexicographically
    // less than zero or positive signed integers
    ASSERT(strcmp((char *)buf64n, (char *)buf64z) < 0);
    ASSERT(strcmp((char *)buf64n, (char *)buf64) < 0);
    ASSERT(strcmp((char *)buf64z, (char *)buf64) < 0);

    float f = -123456789.0123456789f;
    uint8_t buf_floatn[4];
    lex_ordered_write_float(buf_floatn, f);
    ASSERT_EQ(lex_ordered_read_float(buf_floatn), f);

    f = 0.0f;
    uint8_t buf_floatz[4];
    lex_ordered_write_float(buf_floatz, f);
    ASSERT_EQ(lex_ordered_read_float(buf_floatz), f);

    f = 123456789.0123456789f;
    uint8_t buf_float[4];
    lex_ordered_write_float(buf_float, f);
    ASSERT_EQ(lex_ordered_read_float(buf_float), f);

    f = -0.0f;
    uint8_t buf_float_negz[4];
    lex_ordered_write_float(buf_float_negz, f);
    ASSERT_EQ(lex_ordered_read_float(buf_float_negz), f);

    f = NAN;
    uint8_t buf_float_nan[4];
    lex_ordered_write_float(buf_float_nan, f);
    ASSERT(isnan(lex_ordered_read_float(buf_float_nan)));
    
    f = INFINITY;
    uint8_t buf_float_inf[4];
    lex_ordered_write_float(buf_float_inf, f);
    ASSERT_EQ(lex_ordered_read_float(buf_float_inf), f);

    f = -INFINITY;
    uint8_t buf_float_neginf[4];
    lex_ordered_write_float(buf_float_neginf, f);
    ASSERT_EQ(lex_ordered_read_float(buf_float_neginf), f);

    // Test that negative floats are lexicographically
    // less than zero or positive floats, NaN is greater than all
    ASSERT(strcmp((char *)buf_floatn, (char *)buf_floatz) < 0);
    ASSERT(strcmp((char *)buf_floatn, (char *)buf_float) < 0);
    ASSERT(strcmp((char *)buf_float_nan, (char *)buf_float) > 0);

    ASSERT(strcmp((char *)buf_float_inf, (char *)buf_float) > 0);
    ASSERT(strcmp((char *)buf_float_nan, (char *)buf_float_inf) > 0);
    ASSERT(strcmp((char *)buf_float_neginf, (char *)buf_floatn) < 0);

    double d = -123456789.01234567890123456789;
    uint8_t buf_doublen[8];
    lex_ordered_write_double(buf_doublen, d);
    ASSERT_EQ(lex_ordered_read_double(buf_doublen), d);
    
    d = 0.0;
    uint8_t buf_doublez[8];
    lex_ordered_write_double(buf_doublez, d);
    ASSERT_EQ(lex_ordered_read_double(buf_doublez), d);
    
    d = 123456789.01234567890123456789;
    uint8_t buf_double[8];
    lex_ordered_write_double(buf_double, d);
    ASSERT_EQ(lex_ordered_read_double(buf_double), d);
    
    d = -0.0;
    uint8_t buf_double_negz[8];
    lex_ordered_write_double(buf_double_negz, d);
    ASSERT_EQ(lex_ordered_read_double(buf_double_negz), d);
    
    d = NAN;
    uint8_t buf_double_nan[8];
    lex_ordered_write_double(buf_double_nan, d);
    ASSERT(isnan(lex_ordered_read_double(buf_double_nan)));
    
    d = INFINITY;
    uint8_t buf_double_inf[8];
    lex_ordered_write_double(buf_double_inf, d);
    ASSERT_EQ(lex_ordered_read_double(buf_double_inf), d);

    d = -INFINITY;
    uint8_t buf_double_neginf[8];
    lex_ordered_write_double(buf_double_neginf, d);
    ASSERT_EQ(lex_ordered_read_double(buf_double_neginf), d);

    // Test that negative doubles are lexicographically
    // less than zero or positive doubles, NaN is greater than all
    ASSERT(strcmp((char *)buf_doublen, (char *)buf_doublez) < 0);
    ASSERT(strcmp((char *)buf_doublen, (char *)buf_double) < 0);
    ASSERT(strcmp((char *)buf_double_nan, (char *)buf_double) > 0);
    ASSERT(strcmp((char *)buf_double_inf, (char *)buf_double) > 0);
    ASSERT(strcmp((char *)buf_double_nan, (char *)buf_double_inf) > 0);
    ASSERT(strcmp((char *)buf_double_neginf, (char *)buf_doublen) < 0);


    PASS();
}

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int32_t main(int32_t argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* command-line options, initialization. */

    RUN_TEST(test_lex_order);

    GREATEST_MAIN_END();        /* display results */
}
