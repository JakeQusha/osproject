#include <print>
#include "schedulers.hpp"

void sym::Fcfs::tick(std::span<Process> awaiting) {
    if(awaiting.empty()){
        return;
    }
    awaiting.front().remaining_time--;
    for(int i =1;i<awaiting.size();i++){
        awaiting[i].waiting_time++;
    }
}

void sym::Rr::tick(std::span<Process> awaiting) {
    std::print("Rr {}", time++);
}

void sym::Rr::reset() {
    time = 0;
    std::print("{}\n", time);
}

void sym::Lcfs::tick(std::span<Process> awaiting) {
    if(awaiting.empty()){
        return;
    }
    awaiting.back().remaining_time--;
    for(int i =0;i<awaiting.size()-1;i++){
        awaiting[i].waiting_time++;
    }
}

void sym::Sjf::tick(std::span<Process> awaiting) {

}
