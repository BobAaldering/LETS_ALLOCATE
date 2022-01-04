#ifndef ALLOCATOR_ALLOCATOR_BENCHMARK_H
#define ALLOCATOR_ALLOCATOR_BENCHMARK_H

#include <iostream>
#include <vector>
#include <chrono>
#include <tuple>

#include "pool_allocator.h"
#include "malloc_allocator.h"

#include "benchmark_statistics.h"

class allocator_benchmark {
public:
    allocator_benchmark(const std::initializer_list<std::size_t>& m_elements_list);

    [[nodiscard]] benchmark_statistics benchmark_memory_pool() const;
    [[nodiscard]] benchmark_statistics benchmark_memory_malloc() const;

private:
    std::vector<std::size_t> m_number_of_elements;
};


#endif