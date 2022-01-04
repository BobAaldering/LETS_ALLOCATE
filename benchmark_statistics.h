#ifndef ALLOCATOR_BENCHMARK_STATISTICS_H
#define ALLOCATOR_BENCHMARK_STATISTICS_H

#include <vector>
#include <string>
#include <tuple>

class benchmark_statistics {
public:
    explicit benchmark_statistics(std::string  identifier_benchmark_section);

    void add_result(const std::tuple<std::string, std::size_t, std::size_t>& result_of_benchmark);
    [[nodiscard]] const std::vector<std::tuple<std::string, std::size_t, std::size_t>>& get_all_results() const;

private:
    std::string m_total_identifier;
    std::vector<std::tuple<std::string, std::size_t, std::size_t>> m_statistic_information;
};

#endif