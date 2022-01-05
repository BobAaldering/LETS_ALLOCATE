#include "allocator_benchmark.h"

allocator_benchmark::allocator_benchmark(const std::initializer_list<std::size_t> &elements_list, const std::initializer_list<std::size_t> &run_list) :
    m_number_of_runs{run_list},
    m_number_of_elements{elements_list}
{}

benchmark_statistics allocator_benchmark::benchmark_memory_pool() const {
    std::cout << "---- BENCHMARK MEMORY POOL ----" << std::endl;

    benchmark_statistics new_statistic{"memory_pool"};

    for (const auto& single_run : m_number_of_runs) {
        std::vector<long> sum_durations{};

        for (const auto& memory_size : m_number_of_elements) {
            std::vector<chunk<int>*> assigned_addresses{single_run};
            pool_allocator<int> memory_pool{memory_size};

            auto begin_time = std::chrono::high_resolution_clock::now();

            for (auto& get_memory_addresses : assigned_addresses)
                get_memory_addresses = memory_pool.get_memory();

            for (auto& free_memory_addresses : assigned_addresses)
                memory_pool.back_memory(free_memory_addresses);

            auto end_time = std::chrono::high_resolution_clock::now();

            sum_durations.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time).count());
        }

        auto average_duration = (double)std::accumulate(sum_durations.begin(), sum_durations.end(), average_running_time{});
        new_statistic.add_result(std::make_tuple("pool_" + std::to_string(single_run), single_run, average_duration));

        std::cout << "Elapsed time for your specified runs, is: " << average_duration << " microseconds" << std::endl;
    }

    std::cout << "---- END BENCHMARK MEMORY POOL ----" << std::endl;

    return new_statistic;
}

benchmark_statistics allocator_benchmark::benchmark_memory_malloc() const {
    std::cout << "---- BENCHMARK MEMORY MALLOC ----" << std::endl;

    benchmark_statistics new_statistic{"memory_malloc"};

    for (const auto& single_run : m_number_of_runs) {
        std::vector<long> sum_durations{};

        for (const auto& memory_size : m_number_of_elements) {
            std::vector<int*> assigned_addresses{single_run};
            malloc_allocator<int> memory_malloc{memory_size};

            auto begin_time = std::chrono::high_resolution_clock::now();

            for (auto& get_memory_addresses : assigned_addresses)
                get_memory_addresses = memory_malloc.allocate();

            for (auto& free_memory_addresses : assigned_addresses)
                memory_malloc.deallocate(free_memory_addresses);

            auto end_time = std::chrono::high_resolution_clock::now();

            sum_durations.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time).count());
        }

        auto average_duration = (double)std::accumulate(sum_durations.begin(), sum_durations.end(), average_running_time{});
        new_statistic.add_result(std::make_tuple("malloc_" + std::to_string(single_run), single_run, average_duration));

        std::cout << "Elapsed time for your specified runs, is: " << average_duration << " microseconds" << std::endl;
    }

    std::cout << "---- END BENCHMARK MEMORY MALLOC ----" << std::endl;

    return new_statistic;
}