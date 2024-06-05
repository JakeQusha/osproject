#pragma once
#include "../input.hpp"
#include "simulator.hpp"
inline auto fake_main() -> int {
    using Page = unsigned;
    auto org_data = page::PagingData(page::generate_data(get_val("ENTER NUMBER OF PAGES", 10), page::make_cfg()));
    //print data
    for (auto &p: org_data.pages) {
        std::println("Page: {}", p);
    }
    reset:
    auto data = org_data;
    return 0;
}
