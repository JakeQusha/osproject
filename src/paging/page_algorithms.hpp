#pragma once
#include <vector>
namespace page {
    using Page = unsigned;
    struct PagingData{
        std::vector<Page> pages;
        std::vector<Page> frames;
        unsigned frames_capacity;
        unsigned page_faults;
    };
    template <typename T>
    concept PageAlgorithm = requires(T t, PagingData pd) {
        { T::name } -> std::convertible_to<const char *>;
        { t.tick(pd)};
        { t.reset()};
    };
    struct Fifo {
        static constexpr auto name = "First In First Out";

        void tick(PagingData pd);
        void reset();

    };
    struct LFU {
        static constexpr auto name = "Least Frequently Used";

        void tick(PagingData pd);
        void reset();

    };
}