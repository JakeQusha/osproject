#pragma once
#include <vector>
namespace page {
    using Page = unsigned;
    struct PagingData{
        std::vector<Page> pages;
        std::vector<Page> frames;
        unsigned frames_capacity;
        unsigned page_faults;
        unsigned max_page;
    };
    template <typename T>
    concept PageAlgorithm = requires(T t, PagingData& pd,const PagingData& cpd) {
        { T::name } -> std::convertible_to<const char *>;
        { t.tick(pd)};
        { t.reset(cpd)};
    };
    struct Fifo {
        static constexpr auto name = "First In First Out";
        unsigned current_frame;
        void tick(PagingData& pd);
        void reset([[maybe_unused]] const PagingData& pd);

    };
    struct Lfu {
        static constexpr auto name = "Least Frequently Used";

        void tick(PagingData& pd);
        std::vector<unsigned> frequency;
        void reset([[maybe_unused]]const PagingData& pd);

    };
    struct Lru {
        static constexpr auto name = "Least Recently Used";
        std::vector<unsigned> last_used;
        void tick(PagingData& pd);
        void reset([[maybe_unused]] const PagingData& pd);

    };
}