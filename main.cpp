#include "allocator_tester.h"
#include "allocator_benchmark.h"
#include "benchmark_plot_generator.h"

int main() {
    allocator_tester::pool_validate_int();
    allocator_tester::pool_validate_double();
    allocator_tester::pool_validate_compound();

    // Why testing, and what is the difference? Check: https://stackoverflow.com/questions/12545044/memory-pool-vs-malloc and https://en.wikipedia.org/wiki/Memory_pool
    // Why is programming teasing me... https://en.cppreference.com/w/cpp/memory/allocator/allocate
    // Another nice information: https://www.codetd.com/en/article/12255921 and https://blog.feabhas.com/2019/03/thanks-for-the-memory-allocator/

    std::vector<benchmark_statistics> all_statistics{};
    allocator_benchmark benchmarker{{32, 64, 128, 256, 512}, {10, 100, 1000}};

    all_statistics.push_back(benchmarker.benchmark_memory_pool());
    all_statistics.push_back(benchmarker.benchmark_memory_malloc());
    all_statistics.push_back(benchmarker.benchmark_memory_mmap());
    all_statistics.push_back(benchmarker.benchmark_memory_new());

    benchmark_plot_generator plotter{all_statistics};
    plotter.generate_matlab_plot();

    return 0;
}