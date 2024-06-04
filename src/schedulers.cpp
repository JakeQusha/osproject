#include <print>
#include "schedulers.hpp"

void sym::Fcfs::tick(std::span<Process> awaiting, std::span<Process> finished) {
    std::print("huj");
}

void sym::Rr::tick(std::span<Process> awaiting, std::span<Process> finished) {
    std::print("Rr {}", time++);
}

void sym::Lcfs::tick(std::span<Process> awaiting, std::span<Process> finished) {

}

void sym::Sjf::tick(std::span<Process> awaiting, std::span<Process> finished) {

}
