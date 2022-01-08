#include "allocator_benchmark.h"

// This is the constructor of the 'allocator_benchmark' class.
allocator_benchmark::allocator_benchmark(const std::initializer_list<std::size_t> &elements_list, const std::initializer_list<std::size_t> &run_list) :
    m_number_of_runs{run_list},
    m_number_of_elements{elements_list}
{}

// This method benchmarks the memory pool allocator.
benchmark_statistics allocator_benchmark::benchmark_memory_pool() const {
    std::cout << "---- BENCHMARK MEMORY POOL ----" << std::endl;

    benchmark_statistics new_statistic{benchmark_statistics::statistics_recognition::memory_pool}; // A statistic for the memory pool allocator.

    // Go through the list of all your specified runs.
    for (const auto& single_run : m_number_of_runs) {
        std::vector<long> sum_durations{}; // A vector with the durations of each run.

        // Go through all the memory sizes for a single specified run.
        for (const auto& memory_size : m_number_of_elements) {
            std::vector<chunk<int>*> assigned_addresses{single_run}; // This vector will contain allocated addresses.
            pool_allocator<int> memory_pool{memory_size}; // This is our memory pool allocator.

            auto begin_time = std::chrono::high_resolution_clock::now(); // The start time.

            for (auto& get_memory_addresses : assigned_addresses)
                get_memory_addresses = memory_pool.allocate(); // Allocate memory, get addresses.

            for (auto& free_memory_addresses : assigned_addresses)
                memory_pool.deallocate(free_memory_addresses); // Deallocate memory.

            auto end_time = std::chrono::high_resolution_clock::now(); // The end time.

            sum_durations.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time).count()); // Calculate the duration of a single test.
        }

        auto average_duration = (double)std::accumulate(sum_durations.begin(), sum_durations.end(), average_running_time{}); // Here, you are calculating the average running time of a singel run.
        new_statistic.add_result(std::make_tuple("pool_" + std::to_string(single_run), single_run, average_duration)); // Create a new statistic for your run.

        std::cout << "Elapsed time for your specified runs, is: " << average_duration << " microseconds" << std::endl;
    }

    std::cout << "---- END BENCHMARK MEMORY POOL ----" << std::endl;

    return new_statistic; // Return the statistics.
}

// This method benchmarks the 'malloc' allocator.
benchmark_statistics allocator_benchmark::benchmark_memory_malloc() const {
    std::cout << "---- BENCHMARK MEMORY MALLOC ----" << std::endl;

    benchmark_statistics new_statistic{benchmark_statistics::statistics_recognition::memory_malloc}; // A statistic for the 'malloc' allocator.

    // Go through the list of all your specified runs.
    for (const auto& single_run : m_number_of_runs) {
        std::vector<long> sum_durations{}; // A vector with the durations of each run.

        // Go through all the memory sizes for a single specified run.
        for (const auto& memory_size : m_number_of_elements) {
            std::vector<int*> assigned_addresses{single_run}; // This vector will contain allocated addresses.
            malloc_allocator<int> memory_malloc{}; // This is our 'malloc' allocator.

            auto begin_time = std::chrono::high_resolution_clock::now(); // The start time.

            for (auto& get_memory_addresses : assigned_addresses)
                get_memory_addresses = memory_malloc.allocate(memory_size); // Allocate memory, get addresses.

            for (auto& free_memory_addresses : assigned_addresses)
                memory_malloc.deallocate(free_memory_addresses, memory_size); // Deallocate memory.

            auto end_time = std::chrono::high_resolution_clock::now(); // The end time.

            sum_durations.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time).count()); // Calculate the duration of a single test.
        }

        auto average_duration = (double)std::accumulate(sum_durations.begin(), sum_durations.end(), average_running_time{}); // Here, you are calculating the average running time of a singel run.
        new_statistic.add_result(std::make_tuple("malloc_" + std::to_string(single_run), single_run, average_duration)); // Create a new statistic for your run.

        std::cout << "Elapsed time for your specified runs, is: " << average_duration << " microseconds" << std::endl;
    }

    std::cout << "---- END BENCHMARK MEMORY MALLOC ----" << std::endl;

    return new_statistic; // Return the statistics.
}

// This method benchmarks the 'mmap' allocator.
benchmark_statistics allocator_benchmark::benchmark_memory_mmap() const {
    std::cout << "---- BENCHMARK MEMORY MMAP ----" << std::endl;

    benchmark_statistics new_statistic{benchmark_statistics::statistics_recognition::memory_mmap}; // A statistic for the 'mmap' allocator.

    // Go through the list of all your specified runs.
    for (const auto& single_run : m_number_of_runs) {
        std::vector<long> sum_durations{}; // A vector with the durations of each run.

        // Go through all the memory sizes for a single specified run.
        for (const auto& memory_size : m_number_of_elements) {
            std::vector<int*> assigned_addresses{single_run}; // This vector will contain allocated addresses.
            mmap_allocator<int> memory_mmap{}; // This is our 'mmap' allocator.

            auto begin_time = std::chrono::high_resolution_clock::now(); // The start time.

            for (auto& get_memory_addresses : assigned_addresses)
                get_memory_addresses = memory_mmap.allocate(memory_size); // Allocate memory, get addresses.

            for (auto& free_memory_addresses : assigned_addresses)
                memory_mmap.deallocate(free_memory_addresses, memory_size); // Deallocate memory.

            auto end_time = std::chrono::high_resolution_clock::now(); // The end time.

            sum_durations.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time).count()); // Calculate the duration of a single test.
        }

        auto average_duration = (double)std::accumulate(sum_durations.begin(), sum_durations.end(), average_running_time{}); // Here, you are calculating the average running time of a singel run.
        new_statistic.add_result(std::make_tuple("malloc_" + std::to_string(single_run), single_run, average_duration)); // Create a new statistic for your run.

        std::cout << "Elapsed time for your specified runs, is: " << average_duration << " microseconds" << std::endl;
    }

    std::cout << "---- END BENCHMARK MEMORY MMAP ----" << std::endl;

    return new_statistic; // Return the statistics.
}

// This method benchmarks the 'new' allocator.
benchmark_statistics allocator_benchmark::benchmark_memory_new() const {
    std::cout << "---- BENCHMARK MEMORY NEW ----" << std::endl;

    benchmark_statistics new_statistic{benchmark_statistics::statistics_recognition::memory_new}; // A statistic for the 'new' allocator.

    // Go through the list of all your specified runs.
    for (const auto& single_run : m_number_of_runs) {
        std::vector<long> sum_durations{}; // A vector with the durations of each run.

        // Go through all the memory sizes for a single specified run.
        for (const auto& memory_size : m_number_of_elements) {
            std::vector<int*> assigned_addresses{single_run}; // This vector will contain allocated addresses.
            new_allocator<int> memory_new{}; // This is our 'new' allocator.

            auto begin_time = std::chrono::high_resolution_clock::now(); // The start time.

            for (auto& get_memory_addresses : assigned_addresses)
                get_memory_addresses = memory_new.allocate(memory_size); // Allocate memory, get addresses.

            for (auto& free_memory_addresses : assigned_addresses)
                memory_new.deallocate(free_memory_addresses, memory_size); // Deallocate memory.

            auto end_time = std::chrono::high_resolution_clock::now(); // The end time.

            sum_durations.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time).count()); // Calculate the duration of a single test.
        }

        auto average_duration = (double)std::accumulate(sum_durations.begin(), sum_durations.end(), average_running_time{}); // Here, you are calculating the average running time of a singel run.
        new_statistic.add_result(std::make_tuple("malloc_" + std::to_string(single_run), single_run, average_duration)); // Create a new statistic for your run.

        std::cout << "Elapsed time for your specified runs, is: " << average_duration << " microseconds" << std::endl;
    }

    std::cout << "---- END BENCHMARK MEMORY NEW ----" << std::endl;

    return new_statistic; // Return the statistics.
}