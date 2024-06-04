#pragma once

#include "process.hpp"
#include <span>

namespace sym {
    template<typename T>
    concept Scheduler = requires(std::span<Process> awaiting, std::span<Process> finished){
        { T::name } -> std::convertible_to<const char *>;
        { T::tick(awaiting, finished) };
        { std::is_empty_v<T> };
    } || requires(T t, std::span<Process> awaiting, std::span<Process> finished){
        { T::name } -> std::convertible_to<const char *>;
        { t.tick(awaiting, finished) };
    };

    struct Fcfs {
        static constexpr auto name = "First Come First Serve";

        static void tick(std::span<Process> awaiting, std::span<Process> finished);
    };
    struct Lcfs {
        static constexpr auto name = "Last Come First Serve";

        static void tick(std::span<Process> awaiting, std::span<Process> finished);
    };
    struct Sjf {
        static constexpr auto name = "Shortest job first";

        static void tick(std::span<Process> awaiting, std::span<Process> finished);
    };
    struct Rr {
        static constexpr auto name = "Round Robin";
        int time;
        void tick(std::span<Process> awaiting, std::span<Process> finished);
    };
}//namespace sym