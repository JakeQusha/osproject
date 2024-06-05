#pragma once

#include "process.hpp"
#include <span>

namespace sch {
    template<typename T>
    concept Scheduler = requires(std::span<Process> awaiting){
        { T::name } -> std::convertible_to<const char *>;
        { T::tick(awaiting) };
        { std::is_empty_v<T> };
    } || requires(T t, std::span<Process> awaiting){
        { T::name } -> std::convertible_to<const char *>;
        { t.tick(awaiting) };
        {t.reset()};
    };

    struct Fcfs {
        static constexpr auto name = "First Come First Serve";

        static void tick(std::span<Process> awaiting);
    };
    struct Lcfs {
        static constexpr auto name = "Last Come First Serve Preemptive";

        static void tick(std::span<Process> awaiting);
    };
    struct Sjf {
        static constexpr auto name = "Shortest job first Non-Preemptive";
        int current_job;
        void tick(std::span<Process> awaiting);
        void reset();
    };
    struct SjfPreemptive {
        static constexpr auto name = "Shortest job first Preemptive";

        static void tick(std::span<Process> awaiting);
    };
    struct Rr {
        static constexpr auto name = "Round Robin";
        int time;
        unsigned quantum;
        unsigned current_job;
        void tick(std::span<Process> awaiting);
        void reset();
    };
}//namespace sch