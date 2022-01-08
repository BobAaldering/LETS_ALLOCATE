#include "allocator_tester.h" // Include here all the 'allocator_tester' facilities.
#include "allocator_benchmark.h" // Include here all the 'allocator_benchmark' facilities.
#include "benchmark_plot_generator.h" // Include here all the 'benchmark_plot_generator' facilities.

int main() {
    // Why testing, and what is the difference? Check: https://stackoverflow.com/questions/12545044/memory-pool-vs-malloc and https://en.wikipedia.org/wiki/Memory_pool
    // Why is programming teasing me... https://en.cppreference.com/w/cpp/memory/allocator/allocate
    // Another nice information: https://www.codetd.com/en/article/12255921 and https://blog.feabhas.com/2019/03/thanks-for-the-memory-allocator/

    // --- TEST SECTION --- //
    allocator_tester::pool_validate_int(); // Validate the memory pool allocator with integers.
    allocator_tester::pool_validate_double(); // Validate the memory pool allocator with doubles.
    allocator_tester::pool_validate_compound(); // Validate the memory pool allocator with compound types.

    // --- BENCHMARK SECTION --- //
    std::vector<benchmark_statistics> all_statistics{}; // This vector contains your statistics of the benchmark.
    allocator_benchmark benchmarker{{32, 64, 128, 256, 512}, {10, 100, 1000}}; // The first list are the amount of memory elements, the second list are the number of runs.

    all_statistics.push_back(benchmarker.benchmark_memory_pool()); // Benchmark the memory pool allocator.
    all_statistics.push_back(benchmarker.benchmark_memory_malloc()); // Benchmark the 'malloc' allocator.
    all_statistics.push_back(benchmarker.benchmark_memory_mmap()); // Benchmark the 'mmap' allocator.
    all_statistics.push_back(benchmarker.benchmark_memory_new()); // Benchmark the 'new' allocator.

    benchmark_plot_generator plotter{all_statistics}; // Create a plotter with the statistics.
    plotter.generate_matlab_plot(); // Generate a MATLAB-script with the plot.

    return 0;
}