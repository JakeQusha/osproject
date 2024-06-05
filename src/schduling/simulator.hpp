#pragma once
#include <vector>
#include "schedulers.hpp"
#include "process.hpp"
namespace sym{
    struct SchedulingData{
        std::vector<Process> waiting;
        std::vector<Process> current{};
        std::vector<Process> finished{};
        void update(unsigned time);
    };
    bool is_simulation_done(const SchedulingData& data);
    template<sym::Scheduler T>
    void simulate(SchedulingData& data) {
        if constexpr (std::is_empty_v<T>){
            T::tick(data.current,data.finished);
        } else{
            static T t;
            t.tick(data.current,data.finished);
        }
    }
}