#include "simulator.hpp"
#include "../input.hpp"

void page::setup_data(PagingData &data) {
    data.page_faults=0;
    data.frames.clear();
    data.frames_capacity=get_val("ENTER NUMBER OF FRAMES", 3);
}