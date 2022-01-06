#include "benchmark_statistics.h"

benchmark_statistics::benchmark_statistics(const statistics_recognition &identifier_benchmark_section) :
    m_total_identifier{identifier_benchmark_section},
    m_statistic_information{}
{}

void benchmark_statistics::add_result(const std::tuple<std::string, std::size_t, double> &result_of_benchmark) {
    m_statistic_information.push_back(result_of_benchmark);
}

const std::vector<std::tuple<std::string, std::size_t, double>> &benchmark_statistics::get_all_results() const {
    return m_statistic_information;
}

const benchmark_statistics::statistics_recognition &benchmark_statistics::get_total_identifier() const {
    return m_total_identifier;
}