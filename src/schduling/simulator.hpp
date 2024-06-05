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
        unsigned time;
    };
    static void setup_data(SchedulingData &data){
        data.time=0;
        for (auto &process : data.waiting) {
            process.remaining_time=process.burst_time;
            process.turnaround_time=0;
            process.waiting_time=0;
            process.completion_time=0;
        }
        std::sort(data.waiting.begin(), data.waiting.end(), [](const Process &a, const Process &b){
            return a.arrival_time < b.arrival_time;
        });
    }
    static void update_data(SchedulingData &data, unsigned time){
        for (int i = 0; i < data.current.size(); ++i) {
            if(data.current[i].remaining_time == 0){
                data.current[i].completion_time = time;
                data.current[i].turnaround_time = data.current[i].completion_time - data.current[i].arrival_time;
                data.finished.push_back(data.current[i]);
                data.current.erase(data.current.begin() + i);
                i--;
            }
        }
        int i = 0;
        for(auto &process : data.waiting){
            if(process.arrival_time >= time){
                break;
            }
            data.current.push_back(process);
            i++;
        }
        data.waiting.erase(data.waiting.begin(), data.waiting.begin() + i);
    }
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