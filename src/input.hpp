#pragma once
#include "schduling/simulator.hpp"
#include "schduling/generator.hpp"
#include <print>
#include <iostream>
#include <functional>
template<sym::Scheduler... Sch>
auto select_function() {
    unsigned number=0;
    std::print("SELECT FUNCTION\n");
    ([&](){std::println("{}: {}",number++,Sch::name);}(), ...);
    unsigned input = 0;
    std::cin>>input;
    while(std::cin.fail()||input>=number){
        std::print("Choose valid option between 0 and {}\n",number-1);
        std::cin>>input;
    }
    number=0;
    auto val = sym::simulate<sym::Rr>;
    ([&](){if(input == number++){val = sym::simulate<Sch>;}}(),...);
    return val;
}

auto get_val(const char *massage, unsigned  def) -> unsigned;

auto make_cfg() -> sym::GenConfig;
