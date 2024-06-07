#include <print>
#include <ranges>
#include <iostream>
#include "../input.hpp"
#include "schedulers.hpp"

void sch::Fcfs::tick(std::span<Process> awaiting) {
    if(awaiting.empty()){
        return;
    }
    awaiting.front().remaining_time--;
    if(!awaiting.front().has_started){
        awaiting.front().has_started=1;
    }
    for(int i =1;i<awaiting.size();i++){
        awaiting.at(i).waiting_time++;
    }
}

void sch::Rr::tick(std::span<Process> awaiting) {
    if(awaiting.empty()){
        return;
    }
    for(auto &p : awaiting){
        p.waiting_time++;
    }
    awaiting.at(current_job).remaining_time--;
    if(!awaiting.at(current_job).has_started){
        awaiting.at(current_job).has_started=1;
    }
    awaiting.at(current_job).waiting_time--;
    time++;
    if(awaiting.at(current_job).remaining_time==0){
        time=0;
        if(current_job+1>=awaiting.size()){
            current_job=0;
        }
    }
    if(time>=quantum){
        current_job++;
        if(current_job>=awaiting.size()){
            current_job=0;
        }
        time=0;
    }
}

void sch::Rr::reset() {

    time = 0;
    current_job =0;
    //susy fix
    std::string a;
    std::getline(std::cin, a);
    //
    quantum = get_val("Enter quantum",4);
}

void sch::Lcfs::tick(std::span<Process> awaiting) {
    if(awaiting.empty()){
        return;
    }
    awaiting.back().remaining_time--;
    if(!awaiting.back().has_started){
        awaiting.back().has_started=1;
    }
    for(int i =0;i<awaiting.size()-1;i++){
        awaiting.at(i).waiting_time++;
    }
}

void sch::Sjf::tick(std::span<Process> awaiting) {
    if(awaiting.empty()){
        return;
    }
    if(current_job!=-1){
        for(auto &p : awaiting){
            p.waiting_time++;
        }
        awaiting.at(current_job).remaining_time--;
        if(!awaiting.at(current_job).has_started){
            awaiting.at(current_job).has_started=1;
        }
        awaiting.at(current_job).waiting_time--;
        if(awaiting.at(current_job).remaining_time==0){
            current_job=-1;
        }
        return;
    }
    std::pair<unsigned ,unsigned > min = {0,awaiting.front().remaining_time};
    for(unsigned i : std::views::iota(0u,awaiting.size())){
        awaiting.at(i).waiting_time++;
        if(min.second>awaiting.at(i).remaining_time){
            min = {i,awaiting.at(i).remaining_time};
        }
    }
    awaiting.at(min.first).waiting_time--;
    awaiting.at(min.first).remaining_time--;
    if(awaiting.at(min.first).remaining_time==0){
        return;
    }
    current_job = min.first;
}

void sch::Sjf::reset() {
    current_job=-1;
}

void sch::SjfPreemptive::tick(std::span<Process> awaiting) {
    if(awaiting.empty()){
        return;
    }
    std::pair<unsigned ,unsigned > min = {0,awaiting.front().remaining_time};
    for(unsigned i : std::views::iota(0u,awaiting.size())){
        awaiting.at(i).waiting_time++;
        if(min.second>awaiting.at(i).remaining_time){
            min = {i,awaiting.at(i).remaining_time};
        }
    }
    awaiting.at(min.first).waiting_time--;
    awaiting.at(min.first).remaining_time--;
    if(!awaiting.at(min.first).has_started){
        awaiting.at(min.first).has_started=1;
    }
}
