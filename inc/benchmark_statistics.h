#ifndef ALLOCATOR_BENCHMARK_STATISTICS_H
#define ALLOCATOR_BENCHMARK_STATISTICS_H

#include <vector> // Include here all the 'vector' facilities.
#include <string> // Include here all the 'string' facilities.
#include <tuple> // Include here all the 'tuple' facilities.

/// This is the 'benchmark_statistics' class. It contains all the statistics generated during the benchmark of all the different allocators.
class benchmark_statistics {
public:
    /// This enumeration class 'statistics_recognition' is used for recognizing different allocators within the benchmark.
    enum class statistics_recognition {
        memory_malloc, // Used for recognizing the 'malloc' allocator.
        memory_pool, // Used for recognizing the memory pool allocator.
        memory_mmap, // Used for recognizing the 'mmap' allocator.
        memory_new // Used for recognizing the 'new' allocator.
    };

    /// This is the constructor of the 'benchmark_statistics' class.
    /// \param identifier_benchmark_section The identifier for your specific benchmark of the allocator.
    explicit benchmark_statistics(const statistics_recognition& identifier_benchmark_section);

    /// This method adds a new result to its internal vector. This vector will contain all the different results.
    /// \param result_of_benchmark A tuple that contains various fields that are generated during the benchmark.
    void add_result(const std::tuple<std::string, std::size_t, double>& result_of_benchmark);

    /// This method returns a vector with all the result of the benchmark.
    /// \return A constant reference to the vector with the various results of the benchmarker.
    [[nodiscard]] const std::vector<std::tuple<std::string, std::size_t, double>>& get_all_results() const;

    /// This method returns the recognition of your total identifier
    /// \return A constant reference to the identifier for your current statistic.
    [[nodiscard]] const statistics_recognition& get_total_identifier() const;

private:
    statistics_recognition m_total_identifier; // This field is used for identifying your current statistic.
    std::vector<std::tuple<std::string, std::size_t, double>> m_statistic_information; // This field is a vector that contains all the statistics used within the benchmark (its type is a tuple).
};

#endif