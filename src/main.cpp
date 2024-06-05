
#include "simulator.hpp"
#include "generator.hpp"
#include "input.hpp"


auto main() -> int {
    std::print("WELCOME\n");
    auto data = sym::SchedulingData(sym::generate_data(10,make_cfg()));
    //print data (waiting)
    for(auto &p : data.waiting){
        std::println("Process: {} Arrival: {} Burst: {}",p.id,p.arrival_time,p.burst_time);
    }
    auto func = select_function<sym::Rr,sym::Fcfs,sym::Sjf,sym::Lcfs>();
    func(data);
    func(data);
    return 0;
}
