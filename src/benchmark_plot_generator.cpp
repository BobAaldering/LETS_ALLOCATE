#include "benchmark_plot_generator.h"

benchmark_plot_generator::benchmark_plot_generator(benchmark_statistics pool_statistics, benchmark_statistics malloc_statistics) :
    m_pool_statistic{std::move(pool_statistics)},
    m_malloc_statistic{std::move(malloc_statistics)}
{}

void benchmark_plot_generator::generate_matlab_plot() const {
    // Append the filename with the current date and time, for better recognition:
    auto time_point = std::time(nullptr);
    auto local_time = std::localtime(&time_point);

    std::stringstream string_stream_title_file{};

    string_stream_title_file << "APC_MATLAB_" << std::put_time(local_time, "%Y_%m_%dT%H_%M_%S") << ".m"; // Your filename for the MATLAB script.

    std::ofstream output_file_string(string_stream_title_file.str());

    auto pool_result_vec = m_pool_statistic.get_all_results();
    auto malloc_result_vec = m_malloc_statistic.get_all_results();

    output_file_string << "%% ADVANCED_PROGRAMMING_CONCEPTS_ALLOCATOR\n\nmemory_sizes = [";

    std::for_each(pool_result_vec.begin(), pool_result_vec.end(), [&] (const std::tuple<std::string, std::size_t, double>& single_statistic) {
        output_file_string << std::get<1>(single_statistic) << ((*std::prev(pool_result_vec.end()) != single_statistic) ? "," : "");
    });

    output_file_string << "];\npool_time = [";

    std::for_each(pool_result_vec.begin(), pool_result_vec.end(), [&] (const std::tuple<std::string, std::size_t, double>& single_statistic) {
        output_file_string << std::get<2>(single_statistic) << ((*std::prev(pool_result_vec.end()) != single_statistic) ? "," : "");
    });

    output_file_string << "];\nmalloc_time = [";

    std::for_each(malloc_result_vec.begin(), malloc_result_vec.end(), [&] (const std::tuple<std::string, std::size_t, double>& single_statistic) {
        output_file_string << std::get<2>(single_statistic) << ((*std::prev(malloc_result_vec.end()) != single_statistic) ? "," : "");
    });

    output_file_string << "];\n\nplot(memory_sizes, pool_time)\nhold on\nplot(memory_sizes, malloc_time)\n\ntitle(\"Execution time allocating memory\")\nxlabel(\"Number of runs\")\nylabel(\"Execution time allocating (milliseconds)\")\nlegend(\"MEMORY POOL\", \"MALLOC\")\n";

    output_file_string.close();
}