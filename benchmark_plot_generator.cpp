#include "benchmark_plot_generator.h"

benchmark_plot_generator::benchmark_plot_generator(benchmark_statistics pool_statistics, benchmark_statistics malloc_statistics) :
    m_pool_statistic{std::move(pool_statistics)},
    m_malloc_statistic{std::move(malloc_statistics)}
{}

void benchmark_plot_generator::generate_matlab_plot() const {
    std::ofstream output_file_string("ADVANCED_PROGRAMMING_CONCEPTS_MATLAB.m");

    auto pool_result_vec = m_pool_statistic.get_all_results();
    auto malloc_result_vec = m_malloc_statistic.get_all_results();

    output_file_string << "%% ADVANCED_PROGRAMMING_CONCEPTS_ALLOCATOR\n\nmemory_sizes = [";

    std::for_each(pool_result_vec.begin(), pool_result_vec.end(), [&] (const std::tuple<std::string, std::size_t, std::size_t>& single_statistic) {
        output_file_string << std::get<1>(single_statistic) << ((*std::prev(pool_result_vec.end()) != single_statistic) ? "," : "");
    });

    output_file_string << "];\npool_time = [";

    std::for_each(pool_result_vec.begin(), pool_result_vec.end(), [&] (const std::tuple<std::string, std::size_t, std::size_t>& single_statistic) {
        output_file_string << std::get<2>(single_statistic) << ((*std::prev(pool_result_vec.end()) != single_statistic) ? "," : "");
    });

    output_file_string << "];\nmalloc_time = [";

    std::for_each(malloc_result_vec.begin(), malloc_result_vec.end(), [&] (const std::tuple<std::string, std::size_t, std::size_t>& single_statistic) {
        output_file_string << std::get<2>(single_statistic) << ((*std::prev(malloc_result_vec.end()) != single_statistic) ? "," : "");
    });

    output_file_string << "];\n\nplot(memory_sizes, pool_time)\nhold on\nplot(memory_sizes, malloc_time)\n\ntitle(\"Execution time allocating memory\")\nxlabel(\"memory_size (elements)\")\nylabel(\"Execution time allocating (milliseconds)\")\nlegend(\"Memory pool\", \"Malloc\")\n";

    output_file_string.close();
}