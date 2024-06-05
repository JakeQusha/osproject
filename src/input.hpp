#pragma once

#include "scheduling/simulator.hpp"
#include "generator.hpp"
#include <print>
#include <iostream>
#include <functional>

template<sch::Scheduler... Sch>
[[nodiscard]]auto select_sim() {
    unsigned number = 0;
    std::print("SELECT FUNCTION\n");
    ([&]() { std::println("{}: {}", number++, Sch::name); }(), ...);
    unsigned input = 0;
    std::cin >> input;
    while (std::cin.fail() || input >= number) {
        std::print("Choose valid option between 0 and {}\n", number - 1);
        std::cin >> input;
    }
    number = 0;
    auto val = std::variant<sch::Simulator<Sch>...>{};
    val = sch::Simulator<sch::Rr>();
    ([&]() { if (input == number++) { val = sch::Simulator<Sch>(); }}(), ...);
    return val;
}

[[nodiscard]]auto get_bool(const char *massage, bool def) -> bool;

[[nodiscard]]auto get_val(const char *massage, unsigned def) -> unsigned;
namespace sch {
    [[nodiscard]]auto make_cfg() -> sch::GenConfig;
}
namespace page {
    [[nodiscard]]auto make_cfg() -> page::GenConfig;
}