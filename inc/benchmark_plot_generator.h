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
    benchmark_plot_generator(benchmark_statistics pool_statistics, benchmark_statistics malloc_statistics);

    void generate_matlab_plot() const;

private:
    benchmark_statistics m_pool_statistic;
    benchmark_statistics m_malloc_statistic;
};

#endif