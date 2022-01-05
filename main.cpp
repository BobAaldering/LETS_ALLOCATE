#include "allocator_tester.h"
#include "allocator_benchmark.h"
#include "benchmark_plot_generator.h"

int main() {
    allocator_tester::pool_validate_int();
    allocator_tester::pool_validate_double();
    allocator_tester::pool_validate_compound();

    // Why testing, and what is the difference? Check: https://stackoverflow.com/questions/12545044/memory-pool-vs-malloc and https://en.wikipedia.org/wiki/Memory_pool
    // Why is programming teasing me... https://en.cppreference.com/w/cpp/memory/allocator/allocate

    allocator_benchmark benchmarker{{32, 64, 128, 256, 512}, {10, 100, 1000, 10000}};
    auto benchmark_memory_pool = benchmarker.benchmark_memory_pool();
    auto benchmark_memory_malloc = benchmarker.benchmark_memory_malloc();

    benchmark_plot_generator plotter{benchmark_memory_pool, benchmark_memory_malloc};
    plotter.generate_matlab_plot();

    return 0;
}