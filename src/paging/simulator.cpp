#include "simulator.hpp"
#include "../input.hpp"

void page::setup_data(PagingData &data) {
    data.page_faults = 0;
    data.frames.clear();
    //susy fix
    std::string tmp_fix;
    getline(std::cin, tmp_fix);
    //
    data.frames_capacity = get_val("ENTER NUMBER OF FRAMES", 3);
    std::reverse(data.pages.begin(), data.pages.end());
    data.max_page = *std::max_element(data.pages.begin(), data.pages.end());
}


bool page::is_simulation_done(const page::PagingData &data) {
    return data.pages.empty();
}
