#pragma once

#include "../input.hpp"
#include "simulator.hpp"

inline auto paging_main() -> int {
    using Page = unsigned;
    //generate data
    auto org_data = page::PagingData(page::generate_data(get_val("ENTER NUMBER OF PAGES", 10), page::make_cfg()));
    //print data
    std::println("Generated data: ");
    for (auto &p: org_data.pages) {
        std::print("{} ", p);
    }
    std::print("\n");
    reset:
    //copy data for current simulation
    auto data = page::PagingData(org_data);
    //select simulation
    auto sim = page::select_page_algorithm<page::Fifo, page::Lfu, page::Lru>();
    //prepare simulation
    std::visit([&](auto &&arg) {
        arg.setup(data);
    }, sim);
    //simulate
    while (!page::is_simulation_done(data)) {
        std::visit([&](auto &&arg) {
            arg.simulate(data);
        }, sim);
    }
    //print result
    std::println("Page faults: {}", data.page_faults);
    if (!get_bool("Again?", true)) {
        return 0;
    }
    goto reset;
}
