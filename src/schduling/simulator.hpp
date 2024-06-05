#pragma once

#include <vector>
#include <print>
#include "schedulers.hpp"
#include "process.hpp"

namespace sym {
    struct SchedulingData {
        std::vector<Process> waiting;
        std::vector<Process> current{};
        std::vector<Process> finished{};

        void update(unsigned time);
    };

    bool is_simulation_done(const SchedulingData &data);

    template<Scheduler T, typename = void>
    class Simulator {};

    template<Scheduler T>
    class Simulator<T, std::enable_if_t<!std::is_empty_v<T>>> {
        T t;
    public:
        void setup(){
            t.reset();
        }
        void simulate(SchedulingData &data){
            t.tick(data.current, data.finished);
        }
    };
    template<Scheduler T>
    class Simulator<T, std::enable_if_t<std::is_empty_v<T>>> {
    public:
        void setup(){
            std::print("setup");
        }
        void simulate(SchedulingData &data){
            T::tick(data.current, data.finished);
        }
    };

//    template<sym::Scheduler T>
//    void simulate(SchedulingData &data) {
//        if constexpr (std::is_empty_v<T>) {
//            T::tick(data.current, data.finished);
//        } else {
//            static T t;
//            t.tick(data.current, data.finished);
//        }
//    }
}