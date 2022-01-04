#include "allocator_benchmark.h"

allocator_benchmark::allocator_benchmark(const std::initializer_list<std::size_t> &m_elements_list) :
    m_number_of_elements{m_elements_list}
{}

benchmark_statistics allocator_benchmark::benchmark_memory_pool() const {
    std::cout << "---- BENCHMARK MEMORY POOL ----" << std::endl;

    benchmark_statistics new_statistic{"memory_pool"};

    for (const auto& elements_in_memory : m_number_of_elements) {
        std::vector<chunk<int>*> assigned_addresses{elements_in_memory};
        pool_allocator<int> memory_pool{elements_in_memory};

        auto begin_time = std::chrono::high_resolution_clock::now();

        for (auto& get_memory : assigned_addresses)
            get_memory = memory_pool.get_memory();

        for (auto& free_memory : assigned_addresses)
            memory_pool.back_memory(free_memory);

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time).count();

        new_statistic.add_result(std::make_tuple("pool_" + std::to_string(elements_in_memory), elements_in_memory, duration));

        std::cout << "Elapsed time (the number of elements: " << elements_in_memory << "), is: " << duration << " microseconds" << std::endl;
    }
    std::cout << "---- END BENCHMARK MEMORY POOL ----" << std::endl;

    return new_statistic;
}

benchmark_statistics allocator_benchmark::benchmark_memory_malloc() const {
    std::cout << "---- BENCHMARK MEMORY MALLOC ----" << std::endl;

    benchmark_statistics new_statistic{"memory_malloc"};

    for (const auto& elements_in_memory : m_number_of_elements) {
        std::vector<int*> assigned_addresses{elements_in_memory};
        malloc_allocator<int> memory_pool{elements_in_memory};

        auto begin_time = std::chrono::high_resolution_clock::now();

        for (auto& get_memory : assigned_addresses)
            get_memory = memory_pool.allocate();

        for (auto& free_memory : assigned_addresses)
            memory_pool.deallocate(free_memory);

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time).count();

        new_statistic.add_result(std::make_tuple("pool_" + std::to_string(elements_in_memory), elements_in_memory, duration));

        std::cout << "Elapsed time (the number of elements: " << elements_in_memory << "), is: " << duration << " microseconds" << std::endl;
    }
    std::cout << "---- END BENCHMARK MEMORY MALLOC ----" << std::endl;

    return new_statistic;
}