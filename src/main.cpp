
#include "schduling/simulator.hpp"
#include "schduling/generator.hpp"
#include "input.hpp"


auto main() -> int {
    std::print("WELCOME\n");
    auto data = sym::SchedulingData(sym::generate_data(get_val("ENTER NUMBER OF PROCESSES", 10), make_cfg()));
    //print data
    for (auto &p: data.waiting) {
        std::println("Process: {} Arrival: {} Burst: {}", p.id, p.arrival_time, p.burst_time);
    }
    auto sim = select_sim<sym::Fcfs, sym::Sjf, sym::Lcfs, sym::Rr>();
    std::visit([](auto &&arg) {
        arg.setup();
    }, sim);
    while (!sym::is_simulation_done(data)) {
        std::visit([&](auto &&arg) {
            arg.simulate(data);
        }, sim);
    }
    return 0;
}
