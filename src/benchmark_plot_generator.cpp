#include "benchmark_plot_generator.h"

benchmark_plot_generator::benchmark_plot_generator(std::vector<benchmark_statistics> statistics_of_benchmark) :
    m_statistics{std::move(statistics_of_benchmark)}
{}

void benchmark_plot_generator::generate_matlab_plot() const {
    // Append the filename with the current date and time, for better recognition:
    auto time_point = std::time(nullptr);
    auto local_time = std::localtime(&time_point);

    std::stringstream string_stream_title_file{};

    string_stream_title_file << "APC_MATLAB_" << std::put_time(local_time, "%Y_%m_%dT%H_%M_%S") << ".m"; // Your filename for the MATLAB script.

    std::ofstream output_file_string(string_stream_title_file.str());

    auto pool_result_vec = std::find_if(m_statistics.begin(), m_statistics.end(), [] (const benchmark_statistics& statistic) { return statistic.get_total_identifier() == benchmark_statistics::statistics_recognition::memory_pool; })->get_all_results();
    auto malloc_result_vec = std::find_if(m_statistics.begin(), m_statistics.end(), [] (const benchmark_statistics& statistics) { return statistics.get_total_identifier() == benchmark_statistics::statistics_recognition::memory_malloc; })->get_all_results();
    auto mmap_result_vec = std::find_if(m_statistics.begin(), m_statistics.end(), [] (const benchmark_statistics& statistics) { return statistics.get_total_identifier() == benchmark_statistics::statistics_recognition::memory_mmap; })->get_all_results();
    auto new_result_vec = std::find_if(m_statistics.begin(), m_statistics.end(), [] (const benchmark_statistics& statistics) { return statistics.get_total_identifier() == benchmark_statistics::statistics_recognition::memory_new; })->get_all_results();

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

    output_file_string << "];\nmmap_time = [";

    std::for_each(mmap_result_vec.begin(), mmap_result_vec.end(), [&] (const std::tuple<std::string, std::size_t, double>& single_statistic) {
        output_file_string << std::get<2>(single_statistic) << ((*std::prev(mmap_result_vec.end()) != single_statistic) ? "," : "");
    });

    output_file_string << "];\nnew_time = [";

    std::for_each(new_result_vec.begin(), new_result_vec.end(), [&] (const std::tuple<std::string, std::size_t, double>& single_statistic) {
        output_file_string << std::get<2>(single_statistic) << ((*std::prev(new_result_vec.end()) != single_statistic) ? "," : "");
    });

    output_file_string << "];\n\nplot(memory_sizes, pool_time)\nhold on\nplot(memory_sizes, malloc_time)\nplot(memory_sizes, mmap_time)\nplot(memory_sizes, new_time)\n\ntitle(\"Execution time allocating memory\")\nxlabel(\"Number of runs\")\nylabel(\"Execution time allocating (milliseconds)\")\nlegend(\"MEMORY POOL\", \"MALLOC\", \"MMAP\", \"NEW\")\n";

    output_file_string.close();
}