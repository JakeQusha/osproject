
#include <fstream>
#include "scheduling/simulator.hpp"
#include "generator.hpp"
#include "input.hpp"
#include "paging/fakemain.hpp"


auto main() -> int {
    std::print("WELCOME\n");
    if(get_bool("Paging instead of scheduling?", false)){
        return fake_main();
    }
    auto org_data = sch::SchedulingData(sch::generate_data(get_val("ENTER NUMBER OF PROCESSES", 10), sch::make_cfg()));
    //print data
    for (auto &p: org_data.waiting) {
        std::println("Process: {} Arrival: {} Burst: {}", p.id, p.arrival_time, p.burst_time);
    }
    reset:
    auto data = sch::SchedulingData(org_data);
    auto sim = select_sim<sch::Fcfs, sch::Sjf, sch::Lcfs, sch::Rr, sch::SjfPreemptive>();
    std::visit([&](auto &&arg) {
        arg.setup(data);
    }, sim);
    while (!sch::is_simulation_done(data)) {
        std::visit([&](auto &&arg) {
            arg.simulate(data);
        }, sim);
    }
    //print finished
    for (auto &p: data.finished) {
        std::println("Process: {} Arrival: {} Burst: {} Completion: {} Turnaround: {} Waiting: {}", p.id,
                     p.arrival_time, p.burst_time, p.completion_time, p.turnaround_time, p.waiting_time);
    }
    //print average
    std::println("Average turnaround time: {}", sch::average_turnaround(data.finished));
    std::println("Average waiting time: {}", sch::average_waiting(data.finished));
    //output to file as table
    std::ofstream file("output.txt");

    file << "Process Arrival Burst Completion Turnaround Waiting\n";
    for (auto &p: data.finished) {
        file<<p.id<<" "<<p.arrival_time<<" "<<p.burst_time<<" "<<p.completion_time<<" "<<p.turnaround_time<<" "<<p.waiting_time<<"\n";
    }
    file << "Average turnaround time: " << sch::average_turnaround(data.finished) << "\n";
    file << "Average waiting time: " << sch::average_waiting(data.finished) << "\n";
    if(!get_bool("Again?", true)){
        return 0;
    }
    goto reset;
}
