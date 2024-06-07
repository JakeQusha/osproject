#pragma once

#include <print>
#include "page_algorithms.hpp"

using Pages = unsigned;
namespace page {

    void setup_data(PagingData &data);

    bool is_simulation_done(const PagingData &data);

    template<PageAlgorithm T>
    class Simulator {
        T t;
    public:
        void setup(PagingData &data) {
            setup_data(data);
            t.reset(data);
        }

        void simulate(PagingData &data) {
            t.tick(data);
            data.pages.pop_back();
        }
    };
}