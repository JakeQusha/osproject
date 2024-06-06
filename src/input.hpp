#pragma once

#include "scheduling/simulator.hpp"
#include "paging/simulator.hpp"
#include "generator.hpp"
#include <print>
#include <iostream>
#include <functional>
namespace sch {
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

    [[nodiscard]]auto make_cfg() -> sch::GenConfig;
}
namespace page {
    template<page::PageAlgorithm... Plg>
    [[nodiscard]]  auto select_page_algorithm(){
        unsigned number = 0;
        std::print("SELECT FUNCTION\n");
        ([&]() { std::println("{}: {}", number++, Plg::name); }(), ...);
        unsigned input = 0;
        std::cin >> input;
        while (std::cin.fail() || input >= number) {
            std::print("Choose valid option between 0 and {}\n", number - 1);
            std::cin >> input;
        }
        number = 0;
        auto val = std::variant<page::Simulator<Plg>...>{};
        val = page::Simulator<page::Fifo>();
        ([&]() { if (input == number++) { val = page::Simulator<Plg>(); }}(), ...);
        return val;
    }
    [[nodiscard]]auto make_cfg() -> page::GenConfig;
}
[[nodiscard]]auto get_bool(const char *massage, bool def) -> bool;
[[nodiscard]]auto get_bool(const char *massage,char true_op, char false_op, bool def) -> bool;
[[nodiscard]]auto get_val(const char *massage, unsigned def) -> unsigned;