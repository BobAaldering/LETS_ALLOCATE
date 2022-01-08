#include "benchmark_statistics.h"

// This is the constructor of the 'benchmark_statistics' class.
benchmark_statistics::benchmark_statistics(const statistics_recognition &identifier_benchmark_section) :
    m_total_identifier{identifier_benchmark_section},
    m_statistic_information{}
{}

// This method adds a new result to its internal vector. This vector will contain all the different results.
void benchmark_statistics::add_result(const std::tuple<std::string, std::size_t, double> &result_of_benchmark) {
    m_statistic_information.push_back(result_of_benchmark); // Ad a new result to the 'm_statistics_information' vector.
}

// This method returns a vector with all the result of the benchmark.
const std::vector<std::tuple<std::string, std::size_t, double>> &benchmark_statistics::get_all_results() const {
    return m_statistic_information; // Return a constant reference to the 'm_statistics_information' vector.
}

// This method returns the recognition of your total identifier
const benchmark_statistics::statistics_recognition &benchmark_statistics::get_total_identifier() const {
    return m_total_identifier; // Return a constant reference to the 'm_total_identifier' field.
}