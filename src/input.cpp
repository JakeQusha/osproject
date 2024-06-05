#include "input.hpp"
#include <ranges>
static auto get_val(const char *massage, unsigned  def) -> unsigned {
    std::string input;
    std::println("{} (default: {}):",massage,def);
    std::print("> ");
    std::getline(std::cin, input);
    if (input.empty()) {
        return def;
    } else {
        try {
            return std::stoi(input);
        } catch (std::invalid_argument const &ex) {
            std::println("Invalid input. Falling back to default.");
            return def;
        }
    }
}
static auto get_generator(const char *massage,sym::GeneratorType def) -> sym::GeneratorType {
    std::string input;
    std::println("{} (default: {}):",massage,sym::get_gen_name(def));
    //print all generator types
    for (unsigned i : std::views::iota(0u, static_cast<unsigned>(sym::GeneratorType::CNT))){
        std::println("{}: {}",i,sym::get_gen_name(static_cast<sym::GeneratorType>(i)));
    }
    std::print("> ");
    std::getline(std::cin, input);
    if (input.empty()) {
        return def;
    } else {
        try {
            return static_cast<sym::GeneratorType>(std::stoi(input));
        } catch (std::invalid_argument const &ex) {
            std::println("Invalid input. Falling back to default.");
            return def;
        }
    }
}
auto make_cfg() -> sym::GenConfig {
    sym::GenConfig cfg{};
    cfg.arrival_gen = get_generator("Input ARRIVAL generator type",sym::GeneratorType::RANDOM);
    switch (cfg.arrival_gen){
        case sym::GeneratorType::NORMAL_DIST:
            cfg.typical_arrival = get_val("Input typical ARRIVAL time",5);
            cfg.arrival_deviation = get_val("Input ARRIVAL deviation",2);
        case sym::GeneratorType::RANDOM:
            cfg.min_arrival_time = get_val("Input minimum ARRIVAL time",0);
            cfg.max_arrival_time = get_val("Input maximum ARRIVAL time",10);
            break;
        case sym::GeneratorType::CONSTANT:
            cfg.typical_arrival = get_val("Input constant ARRIVAL time",5);
            break;
        default:
            break;
    }
    cfg.burst_gen = get_generator("Input BURST generator type",sym::GeneratorType::NORMAL_DIST);
    switch (cfg.burst_gen) {
        case sym::GeneratorType::NORMAL_DIST:
            cfg.typical_burst = get_val("Input typical BURST time",5);
            cfg.burst_deviation = get_val("Input BURST deviation",2);
        case sym::GeneratorType::RANDOM:
            cfg.min_burst_time = get_val("Input minimum BURST time",1);
            cfg.max_burst_time = get_val("Input maximum BURST time",10);
            break;
        case sym::GeneratorType::CONSTANT:
            cfg.typical_burst = get_val("Input constant BURST time",5);
            break;
        default:
            break;
    }
    return cfg;
}
