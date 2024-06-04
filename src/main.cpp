#include <print>
#include <iostream>
#include <functional>
#include "simulator.hpp"
#include "generator.hpp"
template<sym::Scheduler... Sch>
auto select_function() ->std::function<void(sym::SchedulingData)> {
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
auto main() -> int {
    std::print("WELCOME\n");
    auto data = sym::SchedulingData(sym::generate_data(10));
    auto func = select_function<sym::Rr,sym::Fcfs,sym::Sjf,sym::Lcfs>();
    func(data);
    func(data);
    return 0;
}
