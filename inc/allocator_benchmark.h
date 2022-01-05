#ifndef ALLOCATOR_ALLOCATOR_BENCHMARK_H
#define ALLOCATOR_ALLOCATOR_BENCHMARK_H

#include <iostream>
#include <vector>
#include <chrono>
#include <tuple>
#include <numeric>

#include "pool_allocator.h"
#include "malloc_allocator.h"

#include "allocator.h"

#include "benchmark_statistics.h"

struct average_running_time {
public:
    average_running_time& operator+(const std::size_t& summing_value) {
        m_total_running_time += summing_value;
        m_number_of_runnings++;

        return *this;
    }

    explicit operator double() const {
        return (double)m_total_running_time / (double)m_number_of_runnings; // Return the average running time.
    }
private:
    std::size_t m_total_running_time{};
    std::size_t m_number_of_runnings{};
};

class allocator_benchmark {
public:
    allocator_benchmark(const std::initializer_list<std::size_t>& elements_list, const std::initializer_list<std::size_t>& run_list);

    [[nodiscard]] benchmark_statistics benchmark_memory_pool() const;
    [[nodiscard]] benchmark_statistics benchmark_memory_malloc() const;

private:
    std::vector<std::size_t> m_number_of_runs;
    std::vector<std::size_t> m_number_of_elements;
};


#endif