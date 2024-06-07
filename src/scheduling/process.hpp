#pragma once

namespace sch {
    struct Process {
        unsigned id;
        unsigned arrival_time;
        unsigned burst_time;
        unsigned remaining_time;
        unsigned completion_time;
        unsigned turnaround_time;
        unsigned waiting_time;
        unsigned response_time;
        uint8_t has_started;
    };

    inline auto average_turnaround(std::span<Process> processes) -> double {
        double sum = 0;
        for (auto &p: processes) {
            sum += p.turnaround_time;
        }
        return sum / (double) processes.size();
    }

    inline auto average_waiting(std::span<Process> processes) -> double {
        double sum = 0;
        for (auto &p: processes) {
            sum += p.waiting_time;
        }
        return sum / (double) processes.size();
    }

    inline auto average_response(std::span<Process> processes) -> double {
        double sum = 0;
        for (auto &p: processes) {
            sum += p.response_time;
        }
        return sum / (double) processes.size();
    }
} //namespace sch