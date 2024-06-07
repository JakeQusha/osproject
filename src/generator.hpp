#pragma once

#include "scheduling/simulator.hpp"
#include "scheduling/process.hpp"

enum class GeneratorType {
    RANDOM,
    NORMAL_DIST,
    CONSTANT,
    TWO_VAL,
    LINEAR,
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


    [[nodiscard]]auto generate_data(unsigned amount, GenConfig gc) -> std::vector<Process>;

} // namespace sch

namespace page {
    struct GenConfig {
        unsigned max_page;
        unsigned typical_page;
        unsigned page_deviation;
        GeneratorType page_gen;
    };
    using Page = unsigned;

    [[nodiscard]]auto generate_data(unsigned int amount, GenConfig gc) -> std::vector<Page>;
}