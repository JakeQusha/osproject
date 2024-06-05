#pragma once

#include <vector>
#include <print>
#include "schedulers.hpp"
#include "process.hpp"

namespace sch {
    struct SchedulingData {
        std::vector<Process> waiting;
        std::vector<Process> current{};
        std::vector<Process> finished{};
        unsigned time;
    };
    void setup_data(SchedulingData &data);
    void update_data(SchedulingData &data, unsigned time);
    bool is_simulation_done(const SchedulingData &data);

    template<Scheduler T, typename = void>
    class Simulator {};

    template<Scheduler T>
    class Simulator<T, std::enable_if_t<!std::is_empty_v<T>>> {
        T t;
    public:
        void setup(SchedulingData &data){
            setup_data(data);
            t.reset();
        }
        void simulate(SchedulingData &data){
           update_data(data, data.time++);
            t.tick(data.current);

        }
    };
    template<Scheduler T>
    class Simulator<T, std::enable_if_t<std::is_empty_v<T>>> {
    public:
        void setup(SchedulingData &data){
            setup_data(data);
        }
        void simulate(SchedulingData &data){
            update_data(data, data.time++);
            T::tick(data.current);
        }
    };
}