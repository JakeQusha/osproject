#include "input.hpp"
#include <ranges>

auto get_val(const char *massage, unsigned int def) -> unsigned {
    std::string input;
    std::println("{} (default: {}):", massage, def);
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

[[nodiscard]]static auto get_generator(const char *massage, GeneratorType def) -> GeneratorType {
    std::string input;
    std::println("{} (default: {}):", massage, get_gen_name(def));
    //print all generator types
    for (unsigned i: std::views::iota(0u, static_cast<unsigned>(GeneratorType::CNT))) {
        std::println("{}: {}", i, get_gen_name(static_cast<GeneratorType>(i)));
    }
    std::print("> ");
    std::getline(std::cin, input);
    if (input.empty()) {
        return def;
    } else {
        try {
            return static_cast<GeneratorType>(std::stoi(input));
        } catch (std::invalid_argument const &ex) {
            std::println("Invalid input. Falling back to default.");
            return def;
        }
    }
}

auto sch::make_cfg() -> sch::GenConfig {
    sch::GenConfig cfg{};
    cfg.arrival_gen = get_generator("Input ARRIVAL generator type", GeneratorType::RANDOM);
    switch (cfg.arrival_gen) {
        case GeneratorType::NORMAL_DIST:
            cfg.typical_arrival = get_val("Input typical ARRIVAL time", 5);
            cfg.arrival_deviation = get_val("Input ARRIVAL deviation", 2);
        case GeneratorType::RANDOM:
            cfg.min_arrival_time = get_val("Input minimum ARRIVAL time", 0);
            cfg.max_arrival_time = get_val("Input maximum ARRIVAL time", 10);
            break;
        case GeneratorType::CONSTANT:
            cfg.typical_arrival = get_val("Input constant ARRIVAL time", 5);
            break;
        case GeneratorType::TWO_VAL:
            cfg.min_arrival_time = get_val("Input first ARRIVAL time", 0);
            cfg.max_arrival_time = get_val("Input second ARRIVAL time", 10);
            break;
        case GeneratorType::LINEAR:
            cfg.max_arrival_time = get_val("Input max ARRIVAL time", 1000);
            break;
        default:
            break;
    }
    cfg.burst_gen = get_generator("Input BURST generator type", GeneratorType::NORMAL_DIST);
    switch (cfg.burst_gen) {
        case GeneratorType::NORMAL_DIST:
            cfg.typical_burst = get_val("Input typical BURST time", 5);
            cfg.burst_deviation = get_val("Input BURST deviation", 2);
        case GeneratorType::RANDOM:
            cfg.min_burst_time = get_val("Input minimum BURST time", 1);
            cfg.max_burst_time = get_val("Input maximum BURST time", 10);
            break;
        case GeneratorType::CONSTANT:
            cfg.typical_burst = get_val("Input constant BURST time", 5);
            break;
        case GeneratorType::TWO_VAL:
            cfg.min_burst_time = get_val("Input first BURST time", 1);
            cfg.max_burst_time = get_val("Input second BURST time", 10);
            break;
        case GeneratorType::LINEAR:
            cfg.max_burst_time = get_val("Input max BURST time", 1000);
            break;
        default:
            break;
    }
    return cfg;
}

auto get_bool(const char *massage, bool def) -> bool {
    std::string input;
    std::println("{} {}:", massage, (def ? "[Y/n]" : "[y/N]"));
    std::print("> ");
    std::getline(std::cin, input);
    if (input.empty()) {
        return def;
    } else {
        if (input == "y" || input == "Y" || input == "yes" || input == "YES") {
            return true;
        } else if (input == "n" || input == "N" || input == "no" || input == "NO") {
            return false;
        } else {
            std::println("Invalid input. Falling back to default.");
            return def;
        }
    }
}

auto get_bool(const char *massage, const char true_op, const char false_op, bool def) -> bool {
    std::string input;
    std::println("{} [{}/{}]:", massage, (char) (def ? std::toupper(true_op) : std::tolower(true_op)), (char)
            (def ? std::tolower(false_op) : std::toupper(false_op)));
    std::print("> ");
    std::getline(std::cin, input);
    if (input.empty()) {
        return def;
    } else {
        if (input.front() == std::toupper(true_op) || input.front() == std::tolower(true_op)) {
            return true;
        } else if (input.front() == std::toupper(false_op) || input.front() == std::tolower(false_op)) {
            return false;
        } else {
            std::println("Invalid input. Falling back to default.");
            return def;
        }
    }
}

auto page::make_cfg() -> page::GenConfig {
    page::GenConfig cfg{};
    cfg.page_gen = get_generator("Input PAGE generator type", GeneratorType::RANDOM);
    switch (cfg.page_gen) {
        case GeneratorType::NORMAL_DIST:
            cfg.typical_page = get_val("Input typical PAGE", 5);
            cfg.page_deviation = get_val("Input PAGE deviation", 2);
        case GeneratorType::RANDOM:
            cfg.max_page = get_val("Input maximum PAGE", 10);
            break;
        case GeneratorType::CONSTANT:
            cfg.typical_page = get_val("Input constant PAGE (XD?)", 5);
            break;
        default:
            break;
    }
    return cfg;
}
