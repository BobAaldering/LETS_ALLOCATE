#include "benchmark_plot_generator.h"

// This is the constructor of the 'benchmark_plot_generator' class.
benchmark_plot_generator::benchmark_plot_generator(std::vector<benchmark_statistics> statistics_of_benchmark) :
    m_statistics{std::move(statistics_of_benchmark)}
{}

// This method generates a MATLAB-plot with our data from the benchmark function.
void benchmark_plot_generator::generate_matlab_plot() const {
    // Append the filename with the current date and time, for better recognition:
    auto time_point = std::time(nullptr); // Create a time point.
    auto local_time = std::localtime(&time_point); // Get the local time.

    std::stringstream string_stream_title_file{}; // This 'string stream' is used for generating a file name.

    string_stream_title_file << "APC_MATLAB_" << std::put_time(local_time, "%Y_%m_%dT%H_%M_%S") << ".m"; // Your filename for the MATLAB script. You appending it with a timestamp.

    std::ofstream output_file_string(string_stream_title_file.str()); // Create a file with the name you specified above.

    auto pool_result_vec = std::find_if(m_statistics.begin(), m_statistics.end(), [] (const benchmark_statistics& statistic) { return statistic.get_total_identifier() == benchmark_statistics::statistics_recognition::memory_pool; })->get_all_results(); // Get all the results of the benchmark with the memory pool.
    auto malloc_result_vec = std::find_if(m_statistics.begin(), m_statistics.end(), [] (const benchmark_statistics& statistics) { return statistics.get_total_identifier() == benchmark_statistics::statistics_recognition::memory_malloc; })->get_all_results(); // Get all the results of the benchmark with the 'malloc' allocator.
    auto mmap_result_vec = std::find_if(m_statistics.begin(), m_statistics.end(), [] (const benchmark_statistics& statistics) { return statistics.get_total_identifier() == benchmark_statistics::statistics_recognition::memory_mmap; })->get_all_results(); // Get all the results of the benchmark with the 'mmap' allocator.
    auto new_result_vec = std::find_if(m_statistics.begin(), m_statistics.end(), [] (const benchmark_statistics& statistics) { return statistics.get_total_identifier() == benchmark_statistics::statistics_recognition::memory_new; })->get_all_results(); // Get all the results of the benchmark with the 'new' allocator.

    output_file_string << "%% ADVANCED_PROGRAMMING_CONCEPTS_ALLOCATOR\n\nmemory_sizes = ["; // Here, create a section within your MATLAB-script.

    // Get the different amount of runs used within the allocator benchmarker.
    std::for_each(pool_result_vec.begin(), pool_result_vec.end(), [&] (const std::tuple<std::string, std::size_t, double>& single_statistic) {
        output_file_string << std::get<1>(single_statistic) << ((*std::prev(pool_result_vec.end()) != single_statistic) ? "," : ""); // Write everything to your MATLAB-script.
    });

    output_file_string << "];\npool_time = ["; // Here, create a new variable within the MATLAB-script.

    // Get the different average running time values for the memory pool allocator.
    std::for_each(pool_result_vec.begin(), pool_result_vec.end(), [&] (const std::tuple<std::string, std::size_t, double>& single_statistic) {
        output_file_string << std::get<2>(single_statistic) << ((*std::prev(pool_result_vec.end()) != single_statistic) ? "," : ""); // Write everything to your MATLAB-script.
    });

    output_file_string << "];\nmalloc_time = ["; // Here, create a new variable within the MATLAB-script.

    // Get the different average running time values for the 'malloc' allocator.
    std::for_each(malloc_result_vec.begin(), malloc_result_vec.end(), [&] (const std::tuple<std::string, std::size_t, double>& single_statistic) {
        output_file_string << std::get<2>(single_statistic) << ((*std::prev(malloc_result_vec.end()) != single_statistic) ? "," : ""); // Write everything to your MATLAB-script.
    });

    output_file_string << "];\nmmap_time = ["; // Here, create a new variable within the MATLAB-script.

    // Get the different average running time values for the 'mmap' allocator.
    std::for_each(mmap_result_vec.begin(), mmap_result_vec.end(), [&] (const std::tuple<std::string, std::size_t, double>& single_statistic) {
        output_file_string << std::get<2>(single_statistic) << ((*std::prev(mmap_result_vec.end()) != single_statistic) ? "," : ""); // Write everything to your MATLAB-script.
    });

    output_file_string << "];\nnew_time = ["; // Here, create a new variable within the MATLAB-script.

    // Get the different average running time values for the 'new' allocator.
    std::for_each(new_result_vec.begin(), new_result_vec.end(), [&] (const std::tuple<std::string, std::size_t, double>& single_statistic) {
        output_file_string << std::get<2>(single_statistic) << ((*std::prev(new_result_vec.end()) != single_statistic) ? "," : ""); // Write everything to your MATLAB-script.
    });

    // Here, you want to create nice graphs for your MATLAB script. You are doing this for all the specified variables, whereby all the lines are in the same plot. Also provide different names for the axis, with a legend and a title for the graph.
    output_file_string << "];\n\nplot(memory_sizes, pool_time)\nhold on\nplot(memory_sizes, malloc_time)\nplot(memory_sizes, mmap_time)\nplot(memory_sizes, new_time)\n\ntitle(\"Execution time allocating memory\")\nxlabel(\"Number of runs\")\nylabel(\"Execution time allocating (microseconds)\")\nlegend(\"MEMORY POOL\", \"MALLOC\", \"MMAP\", \"NEW\")\n"; // You see that it is just a normal string that you have to write to a file.

    output_file_string.close(); // Close the connection with your file (in our case, the MATLAB-script).
}