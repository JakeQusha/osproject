#pragma once

#include "scheduling/simulator.hpp"
#include "scheduling/process.hpp"

enum class GeneratorType {
    RANDOM,
    NORMAL_DIST,
    CONSTANT,
    CNT
};

auto get_gen_name(GeneratorType type) -> const char *;

namespace sch {

    struct GenConfig {
        unsigned min_arrival_time;
        unsigned max_arrival_time;
        unsigned typical_arrival;
        unsigned arrival_deviation;
        unsigned min_burst_time;
        unsigned max_burst_time;
        unsigned typical_burst;
        unsigned burst_deviation;
        GeneratorType arrival_gen;
        GeneratorType burst_gen;
    };


    auto generate_data(unsigned amount, GenConfig gc) -> std::vector<Process>;

} // namespace sch

namespace page{

}