#ifndef ALLOCATOR_BENCHMARK_STATISTICS_H
#define ALLOCATOR_BENCHMARK_STATISTICS_H

#include <vector>
#include <string>
#include <tuple>

class benchmark_statistics {
public:
    enum class statistics_recognition {
        memory_malloc,
        memory_pool,
        memory_mmap,
        memory_new
    };

    explicit benchmark_statistics(const statistics_recognition& identifier_benchmark_section);

    void add_result(const std::tuple<std::string, std::size_t, double>& result_of_benchmark);

    [[nodiscard]] const std::vector<std::tuple<std::string, std::size_t, double>>& get_all_results() const;
    [[nodiscard]] const statistics_recognition& get_total_identifier() const;

private:
    statistics_recognition m_total_identifier;
    std::vector<std::tuple<std::string, std::size_t, double>> m_statistic_information;
};

#endif