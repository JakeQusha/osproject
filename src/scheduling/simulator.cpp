#include "simulator.hpp"


bool sch::is_simulation_done(const sch::SchedulingData& data) {
    if(data.waiting.empty() && data.current.empty()){
        return true;
    }
    return false;
}

void sch::setup_data(sch::SchedulingData &data) {
    data.time=0;
    std::sort(data.waiting.begin(), data.waiting.end(), [](const Process &a, const Process &b){
        return a.arrival_time < b.arrival_time;
    });
    int i=0;
    for (auto &process : data.waiting) {
        process.id=i++;
        process.remaining_time=process.burst_time;
        process.turnaround_time=0;
        process.waiting_time=0;
        process.completion_time=0;
    }
}

void sch::update_data(sch::SchedulingData &data, unsigned int time) {
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
