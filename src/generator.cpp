#include "generator.hpp"
#include <ranges>
#include <random>
#include <algorithm>

auto random(unsigned int min, unsigned int max) -> unsigned {
    static std::random_device rd{};
    std::uniform_int_distribution distribution(min, max);
    return distribution(rd);
}

auto normal(unsigned int typical, unsigned int deviation,unsigned int min, unsigned int max) -> unsigned {
    static std::random_device rd{};
    static std::mt19937 gen{rd()};
    std::normal_distribution distribution{(float) typical, (float) deviation};
    return std::clamp(static_cast<unsigned>(std::round(distribution(gen))),min,max);
}

auto swe(sym::GeneratorType type, unsigned int min, unsigned int max, unsigned int typical,
         unsigned int deviation) -> unsigned {
    switch (type) {
        case sym::GeneratorType::RANDOM:
            return random(min, max);
        case sym::GeneratorType::NORMAL_DIST:
            return normal(typical, deviation,min,max);
        case sym::GeneratorType::CONSTANT:
            return typical;

    }
    return 0;
}

auto sym::generate_data(unsigned amount, GenConfig gc) -> std::vector<Process> {
    std::vector<Process> val;
    for (unsigned id: std::views::iota(0u, amount)) {
        val.emplace_back(
                id,
                swe(gc.arrival_gen, gc.min_arrival_time, gc.max_arrival_time, gc.typical_arrival, gc.arrival_deviation),
                swe(gc.burst_gen, gc.min_burst_time, gc.max_burst_time, gc.typical_burst, gc.burst_deviation));
    }
    return val;
}

auto sym::get_gen_name(sym::GeneratorType type) -> const char * {
    switch (type) {
        case GeneratorType::RANDOM:
            return "Random";
        case GeneratorType::NORMAL_DIST:
            return "Normal Distribution";
        case GeneratorType::CONSTANT:
            return "Constant";
    }
    return "Unknown";
}
