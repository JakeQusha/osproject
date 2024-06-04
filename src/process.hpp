#pragma once

namespace sym {
    struct Process {
        unsigned arrival_time;
        unsigned burst_time;
        unsigned remaining_time;
        unsigned completion_time;
        unsigned turnaround_time;
        unsigned waiting_time;
    };
} //namespace sym