#include "pool_allocator.h"
#include "malloc_allocator.h"

#include "allocator_tester.h"
#include "allocator_benchmark.h"
#include "benchmark_plot_generator.h"

int main() {
    pool_allocator<int> allocator{3};

    auto first_value = allocator.get_memory();
    auto second_value = allocator.get_memory();
    auto third_value = allocator.get_memory();
    auto fourth_value = allocator.get_memory();

    first_value->m_data = 5;
    second_value->m_data = 6;
    third_value->m_data = 7;
    fourth_value->m_data = 8;

    std::cout << "First value: " << first_value->m_data << std::endl;
    std::cout << "Second value: " << second_value->m_data << std::endl;
    std::cout << "Third value: " << third_value->m_data << std::endl;
    std::cout << "Fourth value: " << fourth_value->m_data << std::endl;

    allocator.release_blocks();

    allocator_tester::pool_validate_int();
    allocator_tester::pool_validate_double();
    allocator_tester::pool_validate_compound();

    allocator_benchmark benchmarker{{32, 64, 128, 256, 512, 1024, 2048, 4096}};
    auto benchmark_memory_pool = benchmarker.benchmark_memory_pool();
    auto benchmark_memory_malloc = benchmarker.benchmark_memory_malloc();

    benchmark_plot_generator plotter{benchmark_memory_pool, benchmark_memory_malloc};
    plotter.generate_matlab_plot();

    return 0;
}