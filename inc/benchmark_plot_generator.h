#ifndef ALLOCATOR_BENCHMARK_PLOT_GENERATOR_H
#define ALLOCATOR_BENCHMARK_PLOT_GENERATOR_H

#include <fstream>
#include <tuple>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "benchmark_statistics.h"

class benchmark_plot_generator {
public:
    explicit benchmark_plot_generator(std::vector<benchmark_statistics> statistics_of_benchmark);

    void generate_matlab_plot() const;

private:
    std::vector<benchmark_statistics> m_statistics;
};

#endif