#pragma once
#include <random>
#include "simulator.hpp"
#include "process.hpp"
namespace sym{
    struct GenConfig{
        unsigned min_arrival_t;
        unsigned max_arrival_t;
        unsigned typical_arrival;
        unsigned arrival_deviation;
        unsigned min_burst_t;
        unsigned max_burst_t;
        unsigned typical_time;
        unsigned time_deviation;
    };
    auto generate_data(unsigned amount)->std::vector<Process>{
        std::vector<Process> val;
        //TODO
        return val;
    }
//    auto generate_data(unsigned amount,GenConfig gc,const std::function<unsigned(unsigned,unsigned)> &arrival_rand_func,const std::function<unsigned(unsigned,unsigned)> &time_rand_func)->std::vector<Process>{
//        std::vector<Process> val;
//        //TODO
//        return val;
//    }
//    auto Random(unsigned min,unsigned max)->unsigned {
//        static std::random_device rd;
//        std::uniform_int_distribution distribution(min,max);
//        return distribution(rd);
//    }
//    auto Typical(unsigned typical,unsigned deviation)->unsigned {
//
//    }
//    auto Constant(unsigned val,unsigned)->unsigned {
//
//    }
}