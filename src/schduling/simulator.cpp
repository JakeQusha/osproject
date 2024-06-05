#include "simulator.hpp"

void sym::SchedulingData::update(unsigned time) {

}

bool sym::is_simulation_done(const sym::SchedulingData& data) {
    if(data.waiting.empty() && data.current.empty()){
        return true;
    }
    return false;
}
