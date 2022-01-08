#ifndef ALLOCATOR_ALLOCATOR_TESTER_H
#define ALLOCATOR_ALLOCATOR_TESTER_H

#define ASSERT_TRUE(expression, message) { if (!(expression)) std::cerr << message; } // Custom-made assert, that checks if the given expression is true.
#define ASSERT_EQ(expected, actual, message) ASSERT_TRUE((expected) == (actual), message) // Custom-made assert, that checks if the expected value is equal to the actual value.

#include <iostream> // Include here all the 'iostream' facilities.
#include <vector> // Include here all the 'vector' facilities.

#include "pool_allocator.h" // Include here all the 'pool_allocator' facilities.

/// This structure 'allocator_tester' will test our memory pool allocator.
struct allocator_tester {
    /// This static method validates the memory pool with integers.
    static void pool_validate_int();

    /// This static method validates the memory pool with doubles.
    static void pool_validate_double();

    /// This static method validates the memory pool with a compound type.
    static void pool_validate_compound();
};

#endif