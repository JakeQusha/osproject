//
// Created by jacek on 6/5/24.
//
#include <print>
#include <algorithm>
#include <numeric>
#include "page_algorithms.hpp"

void page::Fifo::tick(page::PagingData &pd) {
    if (pd.pages.empty()) {
        return;
    }
    if (std::find(pd.frames.begin(), pd.frames.end(), pd.pages.back()) != pd.frames.end()) {
        return;
    }
    pd.page_faults++;
    if (pd.frames.size() < pd.frames_capacity) {
        pd.frames.push_back(pd.pages.back());
        return;
    }
    pd.frames[current_frame] = pd.pages.back();
    current_frame = (current_frame + 1) % pd.frames_capacity;
}

void page::Fifo::reset([[maybe_unused]]const page::PagingData &pd) {
    current_frame = 0;
}

void page::Lfu::tick(page::PagingData &pd) {
    if (pd.pages.empty()) {
        return;
    }
#ifdef DEBUG
    //print state
    std::print("\nFrames: ");
    for(auto &f: pd.frames){
        std::print("{} ", f);
    }
    std::print(" Freq: ");
    for(auto &f: pd.frames){
        std::print("{} ", frequency[f]);
    }
#endif
    frequency[pd.pages.back()]++;
    if (std::find(pd.frames.begin(), pd.frames.end(), pd.pages.back()) != pd.frames.end()) {
        return;
    }
    pd.page_faults++;
    if (pd.frames.size() < pd.frames_capacity) {
        pd.frames.push_back(pd.pages.back());
        return;
    }
    *std::min_element(pd.frames.begin(), pd.frames.end(), [&](auto a, auto b) {
        return frequency[a] < frequency[b];
    }) = pd.pages.back();
}

void page::Lfu::reset([[maybe_unused]]const page::PagingData &pd) {
    frequency.resize(pd.max_page + 1,0);
}

void page::Lru::tick(page::PagingData &pd) {
    if (pd.pages.empty()) {
        return;
    }
#ifdef DEBUG
    //print state
    std::print("\nFrames: ");
    for(auto &f: pd.frames){
        std::print("{} ", f);
    }
    std::print(" Last used: ");
    for(auto &f: last_used){
        std::print("{} ", f);
    }
#endif
    for(auto &f: last_used){
        f++;
    }
    auto pos = std::find(pd.frames.begin(), pd.frames.end(), pd.pages.back());
    if ( pos != pd.frames.end()) {
        last_used.at(std::distance(pd.frames.begin(), pos))=0;
        return;
    }
    pd.page_faults++;
    if (pd.frames.size() < pd.frames_capacity) {
        pd.frames.push_back(pd.pages.back());
        last_used.at(std::distance(pd.frames.begin(), pd.frames.end()-1))=0;
        return;
    }
    auto it = std::max_element(last_used.begin(), last_used.end());
    *it = 0;
    pd.frames.at(std::distance(last_used.begin(), it)) = pd.pages.back();
}


void page::Lru::reset([[maybe_unused]]const page::PagingData &pd) {
    last_used.resize(pd.frames_capacity,0);
}
