#include "simulator.hpp"


bool sym::is_simulation_done(const sym::SchedulingData& data) {
    if(data.waiting.empty() && data.current.empty()){
        return true;
    }
    return false;
}
