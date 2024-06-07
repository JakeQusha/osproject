
#include <fstream>
#include "scheduling/simulator.hpp"
#include "generator.hpp"
#include "input.hpp"
#include "paging/paging_main.hpp"

auto main() -> int {
    std::print("WELCOME\n");
    //select scheduling or paging
    if (!get_bool("Scheduling/Paging Algorithms", 'S', 'P', true)) {
        return paging_main();
    }
    //generate data
    auto org_data = sch::SchedulingData(sch::generate_data(get_val("ENTER NUMBER OF PROCESSES", 10), sch::make_cfg()));
    //print data
    for (auto &p: org_data.waiting) {
        std::println("Process: {} Arrival: {} Burst: {}", p.id, p.arrival_time, p.burst_time);
    }
    reset:
    //copy data for current simulation
    auto data = sch::SchedulingData(org_data);
    //select simulation
    auto sim = sch::select_sim<sch::Fcfs, sch::Sjf, sch::SjfPreemptive, sch::Lcfs, sch::Rr>();
    //prepare simulation
    std::visit([&](auto &&arg) {
        arg.setup(data);
    }, sim);
    //simulate
    while (!sch::is_simulation_done(data)) {
        std::visit([&](auto &&arg) {
            arg.simulate(data);
        }, sim);
    }
    //sort finished
    std::sort(data.finished.begin(), data.finished.end(), [](const sch::Process &a, const sch::Process &b) {
        return a.id < b.id;
    });
    //print finished
    for (auto &p: data.finished) {
#ifdef DEBUG
        std::cout<<p.id<<"\t"<<p.arrival_time<<"\t"<<p.burst_time<<"\t"<<p.completion_time<<"\t"<<p.turnaround_time<<"\t"<<p.waiting_time<<"\t"<<p.response_time<<"\n";
#endif
#ifndef DEBUG
        std::println("Process: {} Arrival: {} Burst: {} Completion: {} Turnaround: {} Waiting: {}, Response: {}", p.id,
                     p.arrival_time, p.burst_time, p.completion_time, p.turnaround_time, p.waiting_time,
                     p.response_time);
#endif
    }
    //print average
    std::println("Average turnaround time: {}", sch::average_turnaround(data.finished));
    std::println("Average waiting time: {}", sch::average_waiting(data.finished));
    std::println("Average response time: {}", sch::average_response(data.finished));
    //output to file as table
    std::ofstream file;
    file.open("output.txt");
    file << "Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\tResponse\n";
    for (auto &p: data.finished) {
        file << p.id << "\t" << p.arrival_time << "\t" << p.burst_time << "\t" << p.completion_time << "\t"
             << p.turnaround_time << "\t" << p.waiting_time << "\t" << p.response_time << "\n";
    }
    file << "Average turnaround time:\t" << sch::average_turnaround(data.finished) << "\n";
    file << "Average waiting time:\t" << sch::average_waiting(data.finished) << "\n";
    file << "Average response time:\t" << sch::average_response(data.finished) << "\n";
    if (!get_bool("Again?", true)) {
        return 0;
    }
    goto reset;
}
