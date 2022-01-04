#ifndef ALLOCATOR_ALLOCATOR_TESTER_H
#define ALLOCATOR_ALLOCATOR_TESTER_H

#define ASSERT_TRUE(expression, message) { if (!(expression)) std::cerr << message; } // Custom-made assert, that checks if the given expression is true.
#define ASSERT_EQ(expected, actual, message) ASSERT_TRUE((expected) == (actual), message) // Custom-made assert, that checks if the expected value is equal to the actual value.

#include <iostream>
#include <vector>

#include "pool_allocator.h"

struct allocator_tester {
    static void pool_validate_int();
    static void pool_validate_double();
    static void pool_validate_compound();
};

#endif